#ifndef CDFA_HPP
#define CDFA_HPP

#include <boost/container_hash/hash.hpp>

#include "EpsilonTransitionsRemoving.hpp"
#include "NFA.hpp"
#include "SingleLetterTransitions.hpp"

template <typename StoredT>
struct UnorderedSetHash {
  std::size_t operator()(const std::unordered_set<StoredT>& set) const {
    std::size_t seed = 0;

    for (auto iterator = set.cbegin(); iterator != set.cend(); iterator++) {
      seed ^= boost::hash_value(*iterator);
    }

    return seed;
  }
};

using CompositStatesInfo =
    std::unordered_map<StateId, std::unordered_set<StateId>>;
using CompositDestinationsInfo =
    std::unordered_map<std::unordered_set<StateId>, StateId,
                       UnorderedSetHash<StateId>>;
using TransitionTable =
    std::unordered_map<StateId,
                       std::unordered_map<char, std::unordered_set<StateId>>>;

void ChangeToCDFA(NFA& nfa);

TransitionTable ProcessNormalStates(
    NFA& nfa, CompositStatesInfo& new_states_info,
    CompositDestinationsInfo& new_destinations_info,
    std::unordered_set<StateId>& final_states, StateId sink_id);

StateId AddCompositState(NFA& nfa, const std::unordered_set<StateId>& states,
                         const std::unordered_set<StateId>& final_states,
                         CompositStatesInfo& composit_states_info,
                         CompositDestinationsInfo& composit_destinations_info);

void ProcessCompositStates(NFA& nfa, CompositStatesInfo& new_states_info,
                           CompositDestinationsInfo& new_destinations_info,
                           std::unordered_set<StateId>& final_states,
                           StateId sink_id, TransitionTable& transitions_table);

#endif /* CDFA_HPP */
