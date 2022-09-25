#include <MinimalDFA.hpp>

int main()
{
    auto nfa = NFA();

    auto a = nfa.AddStartState(true);

    auto b = nfa.AddStartState(true);

    auto c = nfa.AddStartState();

    nfa.AddTransition({{a, b}, "test"});

    nfa.AddTransition({{b, b}, EPSILON});

    nfa.AddTransition({{c, b}, "aboba"});

    nfa.AddTransition({{b, a}, EPSILON});

    nfa.AddTransition({{a, c}, EPSILON});

    MakeTransitionsSingleLetter(nfa);

    SaveInDOA(nfa);

    return 0;
}