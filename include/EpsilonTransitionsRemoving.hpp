#ifndef EPSILON_TRANSITIONS_REMOVING_HPP
#define EPSILON_TRANSITIONS_REMOVING_HPP

#include "NFA.hpp"

void RemoveEpsilonTransitions(NFA& nfa);
void DeleteEpsilonOneStepCycles(NFA& nfa);

void EpsilonTransitiveClosureNFA(NFA& nfa);
std::unordered_set<Edge, EdgeHash> GetEpsilonTransitions(const NFA& nfa);
void MakeEpsilonTransitiveClosure(NFA& nfa, std::unordered_set<Edge, EdgeHash> epsilon_transitions);

void AddFinalStates(NFA& nfa);
void AddTransitions(NFA& nfa);
void DeleteEpsilonTransitions(NFA& nfa);
void DeleteUnreachableStates(NFA& nfa);

#endif /* EPSILON_TRANSITIONS_REMOVING_HPP */
