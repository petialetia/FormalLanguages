#include <MinimalDFA.hpp>

#include <iostream>

int main()
{
    auto nfa = NFA();

    auto a = nfa.AddStartState(true);

    auto b = nfa.AddStartState(true);

    auto c = nfa.AddStartState();

    nfa.AddTransition(a, b, "test");

    nfa.AddTransition(b, b, EPSILON);

    nfa.AddTransition(c, b, "aboba");

    SaveInDOA(nfa);

    return 0;
}