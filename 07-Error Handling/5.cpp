class A
{
public:
    void AddAttribute(...);
private:
    // Invariants: names.size() == scores.size();
    std::vector<std::string> names;
    std::vector<int> scores;
};

// 不是strong exception guarantee，因为在push_back name成功后，push_back score失败会导致对象处于不一致状态
void A::AddAttribute(const std::string& name, int score)
{
    names.push_back("Student: " + name); // strong exception guarantee.
    scores.push_back(score); // strong exception gurantee.
    return;
}