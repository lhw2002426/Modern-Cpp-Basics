#ifndef ANIMAL_INTERFACE_IMPL_HPP
#define ANIMAL_INTERFACE_IMPL_HPP

#include "animal.hpp"

template<typename T>
AnimalInterface::AnimalInterface(const T &object) : hiddenObject_{object}
{
    walkProxy_ = [](std::any &object) {
        std::any_cast<T&>(object).Walk();
    };
    talkProxy_ = [](std::any &object, int times) -> std::string {
        return std::any_cast<T&>(object).Talk(times);
    };
}

#endif // ANIMAL_INTERFACE_IMPL_HPP