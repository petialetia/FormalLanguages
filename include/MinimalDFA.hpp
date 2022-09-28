#ifndef MINIMAL_DFA_HPP
#define MINIMAL_DFA_HPP

#include "NFA.hpp"
#include "DOA.hpp"
#include "EpsilonTransitionsRemoving.hpp"
#include "SingleLetterTransitions.hpp"
#include "DFA.hpp"

using ClassId = size_t;

using StateClassInfos = std::unordered_map<StateId, ClassId>;

struct StateAndNeighboursClasses
{
    ClassId class_id_;
    std::vector<ClassId> neighbours_classes_;

    bool operator==(const StateAndNeighboursClasses& other) const;
};

struct StateAndNeighboursClassesHash
{
    std::size_t operator() (const StateAndNeighboursClasses& classes) const;
};

size_t GetNumOfClasses(const StateClassInfos& class_infos);

void ChangeToMinimalDFA(NFA& nfa);

StateClassInfos GetStartClasses(const NFA& nfa);

StateClassInfos GetNextStageClasses(const NFA& nfa, const StateClassInfos& current_stage_classes);

void MergeStates(NFA& nfa, StateId base_state, StateId state_to_attach);

#endif /* MINIMAL_DFA_HPP */