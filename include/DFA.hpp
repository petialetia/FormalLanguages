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

#endif /* DFA_HPP */
