#pragma once

#include "Socket.h"
#include <algorithm>
#include <cassert>
#include <cstring>
#include <ios>
#include <iostream>
#include <limits>
#include <streambuf>

#ifndef _WIN32
#include <sys/ioctl.h>
#endif

namespace Network
{

template<typename T>
class UserManagableBuffer
{
    bool userManaged_ = false;
    T *buffer_ = nullptr;
    std::streamsize bufferSize_ = 0;

public:
    UserManagableBuffer() = default;
    UserManagableBuffer(std::streamsize size)
        : buffer_{ new T[size] }, bufferSize_{ size }
    {
    }
    UserManagableBuffer(const UserManagableBuffer &) = delete;
    UserManagableBuffer &operator=(const UserManagableBuffer &) = delete;
    UserManagableBuffer(UserManagableBuffer &&another) noexcept
        : userManaged_{ std::exchange(another.userManaged_, false) },
          buffer_{ std::exchange(another.buffer_, nullptr) },
          bufferSize_{ std::exchange(another.bufferSize_, 0) }
    {
    }
    UserManagableBuffer &operator=(UserManagableBuffer &&another) noexcept
    {
        if (!userManaged_)
        {
            delete[] buffer_;
        }

        userManaged_ = std::exchange(another.userManaged_, false);
        buffer_ = std::exchange(another.buffer_, nullptr);
        bufferSize_ = std::exchange(another.bufferSize_, 0);
        return *this;
    }
    ~UserManagableBuffer()
    {
        if (!userManaged_)
        {
            delete[] buffer_;
        }
    }

    auto begin() const noexcept { return buffer_; }
    auto end() const noexcept { return buffer_ + bufferSize_; }

    auto GetRawBuffer() const noexcept { return buffer_; }
    auto GetSize() const noexcept { return bufferSize_; }

    void SetBuffer(T *s, std::streamsize n)
    {
        auto oldBuffer = buffer_, needDelete = !userManaged_;
        if (s == nullptr)
        {
            // 如果buffer size不变，且之前也是自动管理的，就不要再重新分配了
            if (n == bufferSize_ && !userManaged_)
                return;
            buffer_ = n == 0 ? nullptr : new T[n];
            bufferSize_ = n;
            userManaged_ = false;
        }
        else
        {
            buffer_ = s;
            bufferSize_ = n;
            userManaged_ = true;
        }
        if (needDelete)
            delete[] oldBuffer;
    }
};

//自己实现的buf 继承自 std::basic_streambuf char特化后的类型 之所以用继承而不是模板， 是因为万一模板类型是两字节的，可能会被网络传输截断
class TCPBuf : public std::basic_streambuf<char>
{
    static_assert(sizeof(char_type) == 1);
    using Base = std::basic_streambuf<char>;
    static inline constexpr int_type s_EOF_ = traits_type::eof();
    static inline constexpr int_type s_NotEOF_ = traits_type::not_eof(0);

public:
    TCPBuf() = default;
    TCPBuf(const TCPBuf &) = delete;
    TCPBuf(TCPBuf &&another) = default;
    ~TCPBuf() override { FlushBuffer_(); }

    // open函数负责设置缓冲区和关联socket
    TCPBuf *open(Socket &&socket, std::ios::openmode mode,
                 std::streamsize inSize, std::streamsize outSize)
    {
        UserManagableBuffer<char_type> inBuffer, outBuffer;
        if (mode & std::ios::in)
        {
            inBuffer.SetBuffer(nullptr, inSize);
        }

        if (mode & std::ios::out)
        {
            outBuffer.SetBuffer(nullptr, outSize);
        }

        // 分配了buffer之后，还要设置指针
        setg(inBuffer.begin(), inBuffer.end(), inBuffer.end());
        setp(outBuffer.begin(), outBuffer.end());

        socket_ = std::move(socket);
        //使用移动语义的原因是防止失败时，原来的socket还能保持有效
        inBuffer = std::move(inBuffer), outBuffer_ = std::move(outBuffer);
        return this;
    }

    bool is_open() const noexcept { return static_cast<bool>(socket_); }

    //close涉及dealloc buffer和关闭socket  是noexcept的
    TCPBuf *close() noexcept
    {
        FlushBuffer_();
        socket_.Close();
        inBuffer_.SetBuffer(nullptr, 0);
        outBuffer_.SetBuffer(nullptr, 0);
        setg(nullptr, nullptr, nullptr);
        setp(nullptr, nullptr);
        return this;
    }

    // overflow -> 溢出的时候调用
    // sync -> flush调用
    // xsputn -> bulk write
private:
    // 返回未写入的大小
    std::streamsize SendAsMuchAsPossible_(const char *ptr, std::streamsize size)
    {
        assert(size <= std::numeric_limits<int>::max());
        // 尽可能多地发送数据
        while (size != 0)
        {
            int resultSize =
                ::send(socket_.GetHandle(), ptr, static_cast<int>(size), 0);
            if (resultSize <= 0)
            {
                break;
            }
            size -= resultSize, ptr += resultSize;
        }
        return size;
    }

    // 获取输出缓冲区剩余空间
    auto GetOutputRemainSize_() const noexcept { return epptr() - pptr(); }

    void MemcpyToOutputBuffer_(const char_type *ptr, std::streamsize size)
    {
        // 拷贝到pptr里，然后前进pptr
        std::memcpy(pptr(), ptr, size);
        pbump(size);
        return;
    }

protected:
    // 溢出空间时，写一个字节
    int_type overflow(int_type ch = s_EOF_) override
    {
        if (!socket_)
            return s_EOF_;

        if (traits_type::eq_int_type(ch, s_EOF_))
            return s_NotEOF_;
        // 如果没有输出buffer，直接发送
        if (outBuffer_.GetRawBuffer() == nullptr)
        {
            char_type realCh = ch;

            return ::send(socket_.GetHandle(), &realCh, sizeof(realCh), 0) ==
                           sizeof(realCh)
                       ? s_NotEOF_
                       : s_EOF_;
        }

        // 腾出空间，写字节
        FlushBuffer_();
        if (GetOutputRemainSize_() == 0)
        {
            return s_EOF_;
        }
        // 把字节写进去
        *this->pptr() = ch;
        this->pbump(1);
        return s_NotEOF_;
    }

    // 批量写入而不经过中间的buffer
    std::streamsize xsputn(const char_type *s, std::streamsize count) override
    {
        if (!socket_)
            return 0;
        // 如果要发送的内容小于buffer剩余空间，直接拷贝过去
        if (GetOutputRemainSize_() >= count)
        {
            MemcpyToOutputBuffer_(s, count);
            return count;
        }

        std::streamsize successSize = 0;
        if (FlushBuffer_())
        {
            auto failSize = SendAsMuchAsPossible_(s, count);
            // 全部发送完, 直接返回
            if (failSize == 0)
            {
                return count;
            }
            successSize = count - failSize;
            s += successSize, count = failSize;
        }
        // 若flushBuffer没有完全写入，则尽可能拷贝
        // 若未完全发送用户buffer，则把剩余部分拷贝过来
        auto largestSize = std::min(GetOutputRemainSize_(), count);
        MemcpyToOutputBuffer_(s, largestSize);
        return successSize + largestSize;
    }

    //覆写std::streambuf的sync函数  flush调用时会调用它
    int sync() override { return FlushBuffer_() ? 0 : -1; }

    bool FlushBuffer_()
    {
        // [pbase, pptr) 已经有内容，进行刷新（全部写出）
        auto begPtr = this->pbase();
        auto msgSize = this->pptr() - begPtr;
        // 为空就直接返回true
        if (msgSize == 0)
        {
            return true;
        }

        // 不是空就要刷新
        auto failSize = SendAsMuchAsPossible_(begPtr, msgSize);
        if (failSize == 0)
        {
            this->setp(outBuffer_.begin(), outBuffer_.end());
            return true;
        }
        // 还有未发送完的，调整指针，保证指针始终指向未发送的数据
        this->setp(this->pptr() - failSize, this->epptr());
        // 前进pptr到未发送数据的末尾
        this->pbump(static_cast<int>(failSize));
        return false;
    }

    // --------------- Input related -----------------
    std::streamsize showmanyc() override
    {
        unsigned long size = 0;

        // Unknown length
#ifdef _WIN32
        if (::ioctlsocket(socket_.GetHandle(), FIONREAD, &size) == SOCKET_ERROR)
            return 0;
#else
        if (::ioctl(socket_.GetHandle(), FIONREAD, &size) < 0)
            return 0;
#endif
        static constexpr auto limit =
            std::numeric_limits<std::streamsize>::max();
        if constexpr (std::numeric_limits<decltype(size)>::max() <= limit)
        {
            return size == 0 ? -1 : static_cast<std::streamsize>(size);
        }
        else
        {
            // This is safe though conversion may happen, since limit >= 0 and
            // size >= 0.
            auto ret = std::min(static_cast<std::streamsize>(size), limit);
            return ret == 0 ? -1 : ret;
        }
    }

private:
    Socket socket_;
    //tcp是双端的，因此in和out都需要buffer
    UserManagableBuffer<char_type> inBuffer_;
    UserManagableBuffer<char_type> outBuffer_;
};

} // namespace Network