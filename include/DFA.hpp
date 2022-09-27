#ifndef DFA_HPP
#define DFA_HPP

#include "NFA.hpp"
#include "EpsilonTransitionsRemoving.hpp"
#include "SingleLetterTransitions.hpp"

#include <boost/container_hash/hash.hpp>

template<typename StoredT>
struct UnorderedSetHash
{
    std::size_t operator() (const std::unordered_set<StoredT>& set) const
    {
        std::size_t seed = 0;

        for (auto iterator = set.cbegin(); iterator != set.cend(); iterator++)
        {
            boost::hash_combine(seed, boost::hash_value(*iterator));
        }

        return seed;
    }
};

void ChangeToDFA(NFA& nfa);

std::unordered_map<StateId, std::unordered_map<char, std::unordered_set<StateId>>> ProcessNormalStates(NFA& nfa, std::unordered_map<StateId, std::unordered_set<StateId>>& new_states_info,
                                                                                                       std::unordered_map<std::unordered_set<StateId>, StateId, UnorderedSetHash<StateId>>& new_destinations_info,
                                                                                                       std::unordered_set<StateId>& final_states, StateId sink_id);

StateId AddCompositState(NFA& nfa, const std::unordered_set<StateId>& states, const std::unordered_set<StateId>& final_states,
                         std::unordered_map<StateId, std::unordered_set<StateId>>& composit_states_info,
                         std::unordered_map<std::unordered_set<StateId>, StateId, UnorderedSetHash<StateId>>& composit_destinations_info);

void ProcessCompositStates(NFA& nfa, std::unordered_map<StateId, std::unordered_set<StateId>>& new_states_info,
                           std::unordered_map<std::unordered_set<StateId>, StateId, UnorderedSetHash<StateId>>& new_destinations_info,
                           std::unordered_set<StateId>& final_states, StateId sink_id,
                           std::unordered_map<StateId, std::unordered_map<char, std::unordered_set<StateId>>>& transitions_table);

#endif /* DFA_HPP */
