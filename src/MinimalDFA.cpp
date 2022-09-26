#include <MinimalDFA.hpp>

int main()
{
    auto nfa = NFA({'a', 'b'});

    auto start = nfa.AddStartState();

    auto second = nfa.AddState();

    auto third = nfa.AddState(true);

    nfa.AddTransition({{start, second}, "a"});

    nfa.AddTransition({{start, third}, "a"});

    nfa.AddTransition({{second, third}, "b"});

    ChangeToDFA(nfa);

    SaveInDOA(nfa);

    return 0;
}