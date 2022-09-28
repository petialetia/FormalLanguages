#include <DOA.hpp>
#include <NFA.hpp>
#include <MinimalDFA.hpp>

int main()
{
    auto nfa = NFA({'a', 'b'});

    auto start = nfa.AddStartState();
    auto first = nfa.AddState();
    auto second = nfa.AddState();
    auto third = nfa.AddState(true);
    auto fouth = nfa.AddState(true);
    auto fifth = nfa.AddState(true);

    nfa.AddTransition({{start, start}, "a"});
    nfa.AddTransition({{start, first}, "b"});
    nfa.AddTransition({{first, second}, "a"});
    nfa.AddTransition({{first, first}, "b"});
    nfa.AddTransition({{second, start}, "a"});
    nfa.AddTransition({{second, third}, "b"});
    nfa.AddTransition({{third, fouth}, "a"});
    nfa.AddTransition({{third, third}, "b"});
    nfa.AddTransition({{fouth, fifth}, "a"});
    nfa.AddTransition({{fouth, third}, "b"});
    nfa.AddTransition({{fifth, fifth}, "a"});
    nfa.AddTransition({{fifth, third}, "b"});

    SaveInDOA(nfa, "Start.doa");

    ChangeToMinimalDFA(nfa);

    SaveInDOA(nfa, "Changed.doa");

    return 0;
}