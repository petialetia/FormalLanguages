#include <MinimalDFA.hpp>

int main()
{
    auto nfa = NFA({'a', 'b', 'c'});

    auto start = nfa.AddStartState();
    auto first = nfa.AddState();
    auto second = nfa.AddState();
    auto third = nfa.AddState();
    auto fouth = nfa.AddState(true);
    auto fifth = nfa.AddState();
    auto sixth = nfa.AddState(true);

    nfa.AddTransition({{start, first}, "a"});
    nfa.AddTransition({{start, fifth}, "a"});
    nfa.AddTransition({{start, second}, "b"});
    nfa.AddTransition({{start, third}, "b"});
    nfa.AddTransition({{third, second}, "c"});
    nfa.AddTransition({{fifth, second}, "b"});
    nfa.AddTransition({{second, fifth}, "a"});
    nfa.AddTransition({{first, third}, "b"});
    nfa.AddTransition({{third, first}, "a"});
    nfa.AddTransition({{first, fouth}, "c"});
    nfa.AddTransition({{fifth, sixth}, "c"});
    nfa.AddTransition({{second, sixth}, "c"});
    nfa.AddTransition({{third, fouth}, "c"});

    ChangeToDFA(nfa);

    SaveInDOA(nfa);

    return 0;
}