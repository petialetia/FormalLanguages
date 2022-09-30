#include <gtest/gtest.h>

#include <DOA.hpp>
#include <SingleLetterTransitions.hpp>

TEST(MakeTransitionsSingleLetter, Correctness1) {
  NFA nfa({'a', 'b', 'c', 'd'});

  auto start_state_id = nfa.AddStartState();
  auto second_state_id = nfa.AddState(true);

  nfa.AddTransition({{start_state_id, second_state_id}, "abcd"});

  MakeTransitionsSingleLetter(nfa);

  EXPECT_EQ(nfa.GetStatesId().size(), 5);
}