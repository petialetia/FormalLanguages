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

    nfa.AddTransition({{start, first}, "a"});
    nfa.AddTransition({{start, second}, "b"});
    nfa.AddTransition({{first, second}, "b"});
    nfa.AddTransition({{second, first}, "b"});
    nfa.AddTransition({{first, third}, "a"});
    nfa.AddTransition({{second, third}, "a"});

    ChangeToMinimalDFA(nfa);

    SaveInDOA(nfa);

    return 0;
}