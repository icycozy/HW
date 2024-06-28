#include <functional>
#include <stack>

class Defer
{
private:
    std::stack<std::function<void()>> func;

public:
    Defer(std::function<void()> f);
    ~Defer();
    void operator()(std::function<void()> f)
    {
        func.push(f);
    }
};

Defer::Defer(std::function<void()> f)
{
    func.push(f);
}
Defer::~Defer()
{
    while (!func.empty())
    {
        func.top()();
        func.pop();
    }
}