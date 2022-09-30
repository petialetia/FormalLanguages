#ifndef MINIMAL_CDFA_HPP
#define MINIMAL_CDFA_HPP

#include "CDFA.hpp"
#include "EpsilonTransitionsRemoving.hpp"
#include "NFA.hpp"
#include "SingleLetterTransitions.hpp"

using ClassId = size_t;

using StateClassInfos = std::unordered_map<StateId, ClassId>;

struct StateAndNeighboursClasses {
  ClassId class_id_;
  std::vector<ClassId> neighbours_classes_;

  bool operator==(const StateAndNeighboursClasses& other) const;
};

struct StateAndNeighboursClassesHash {
  std::size_t operator()(const StateAndNeighboursClasses& classes) const;
};

size_t GetNumOfClasses(const StateClassInfos& class_infos);

void ChangeToMinimalCDFA(NFA& nfa);

StateClassInfos GetStartClasses(const NFA& nfa);

StateClassInfos GetNextStageClasses(
    const NFA& nfa, const StateClassInfos& current_stage_classes);

void MergeStates(NFA& nfa, StateId base_state, StateId state_to_attach);

#endif /* MINIMAL_CDFA_HPP */