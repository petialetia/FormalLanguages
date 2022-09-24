#include <EpsilonTransitionsRemoving.hpp>

void RemoveEpsilonTransitions(NFA& nfa)
{
    DeleteEpsilonOneStepCycles(nfa);
    EpsilonTransitiveClosureNFA(nfa);
    AddFinalStates(nfa);
    AddTransitions(nfa);
    DeleteEpsilonTransitions(nfa);
    DeleteUnreachableStates(nfa);
}

void DeleteEpsilonOneStepCycles(NFA& nfa)
{
    for (const auto& state_id : nfa.GetStatesId())
    {
        nfa[state_id][state_id].erase(EPSILON);
    }
}

void EpsilonTransitiveClosureNFA(NFA& nfa)
{
    return;
}

void AddFinalStates(NFA& nfa)
{
    return;
}

void AddTransitions(NFA& nfa)
{
    return;
}

void DeleteEpsilonTransitions(NFA& nfa)
{
    return;
}

void DeleteUnreachableStates(NFA& nfa)
{
    return;
}