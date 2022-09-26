#ifndef DFA_HPP
#define DFA_HPP

#include "NFA.hpp"
#include "EpsilonTransitionsRemoving.hpp"
#include "SingleLetterTransitions.hpp"

#include <boost/container_hash/hash.hpp>

void ChangeToDFA(NFA& nfa);

#endif /* DFA_HPP */
