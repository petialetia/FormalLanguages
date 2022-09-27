#include <MinimalDFA.hpp>

int main()
{
    auto nfa = NFA({'a', 'b'});

    auto start = nfa.AddStartState();

    auto second = nfa.AddState();

    auto third = nfa.AddState(true);

    auto fouth = nfa.AddState();

    auto fifth = nfa.AddState();

    nfa.AddTransition({{start, second}, "a"});

    nfa.AddTransition({{start, third}, "a"});

    nfa.AddTransition({{second, third}, "b"});

    nfa.AddTransition({{start, fouth}, "a"});

    nfa.AddTransition({{fouth, fifth}, "b"});

    nfa.AddTransition({{fifth, third}, "b"});

    ChangeToDFA(nfa);

    SaveInDOA(nfa);

    return 0;
}