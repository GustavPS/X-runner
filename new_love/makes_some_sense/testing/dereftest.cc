#include <iostream>

class Base
{
    public:
        virtual void abc() = 0;
};

class Derived : public Base
{
    public:
        void abc() override { std::cout << "hej"; }
        auto def() { std::cout << "då"; }
        auto hej {1};
};


auto cool_func()
{
    Derived abc;
    return abc;
}

int main()
{
    cool_func();
}