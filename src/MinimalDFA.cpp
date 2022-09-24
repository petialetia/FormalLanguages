#include <MinimalDFA.hpp>

#include <iostream>

int main()
{
    auto nfa = NFA();

    nfa.AddStartState();

    std::cout << nfa.IsValid() << std::endl;

    return 0;
}