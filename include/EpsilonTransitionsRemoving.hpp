#ifndef EPSILON_TRANSITIONS_REMOVING_HPP
#define EPSILON_TRANSITIONS_REMOVING_HPP

#include "NFA.hpp"

void RemoveEpsilonTransitions(NFA& nfa);
void DeleteEpsilonOneStepCycles(NFA& nfa);
void EpsilonTransitiveClosureNFA(NFA& nfa);
void AddFinalStates(NFA& nfa);
void AddTransitions(NFA& nfa);
void DeleteEpsilonTransitions(NFA& nfa);
void DeleteUnreachableStates(NFA& nfa);

#endif /* EPSILON_TRANSITIONS_REMOVING_HPP */
