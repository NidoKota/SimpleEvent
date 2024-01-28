#include <iostream>
#include <functional>
#include <vector>

#include "Event.hpp"

void TestA() 
{
    using namespace NidoKota;

    std::cout << "TestA" << std::endl;

    Event<int, int> ev;
    IReadOnlyEvent<int, int>& readOnlyEv = ev;

    int tmp = 5;
    auto& func = readOnlyEv.Subscribe([&](int i)
        {
            tmp += i;
            return tmp;
        });

    {
        std::cout << "resultA ";
        auto resultA = ev(5);
        if (resultA.size() > 0)
        {
            std::cout << resultA[0] << std::endl;
        }
        else std::cout << "size is zero" << std::endl;
    }

    readOnlyEv.Unsubscribe(func);

    {
        std::cout << "resultB ";
        auto resultB = ev(15);
        if (resultB.size() > 0)
        {
            std::cout << resultB[0] << std::endl;
        }
        else std::cout << "size is zero" << std::endl;
    }
}

void TestB()
{
    using namespace NidoKota;

    std::cout << "TestB" << std::endl;

    class ClassA
    {
    public:
        void FuncA() {
            std::cout << "FuncA called" << std::endl;
        }
    };

    Event<void, void> ev;
    IReadOnlyEvent<void, void>& readOnlyEv = ev;
    ClassA classA;

    readOnlyEv.Subscribe(std::bind(&ClassA::FuncA, &classA));

    ev();
}

void TestC()
{
    using namespace NidoKota;

    std::cout << "TestC" << std::endl;

    function<void(void)> funcA = []()
        {
            std::cout << "FuncA called" << std::endl;
        };

    Event<void, void> ev;
    IReadOnlyEvent<void, void>& readOnlyEv = ev;

    readOnlyEv.Subscribe(funcA);
    ev();

    readOnlyEv.Unsubscribe(funcA);
    ev();
}

int main()
{
    TestA();
    TestB();
    TestC();
    return EXIT_SUCCESS;
}
