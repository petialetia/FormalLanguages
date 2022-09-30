#include <gtest/gtest.h>

#include <NFA.hpp>

TEST(Transition, Comparing) {
  Transition first_transition({{1, 1}, "abcd"});
  Transition second_transition({{2, 1}, "abcd"});
  Transition third_transition({{1, 2}, "abcd"});
  Transition fouth_transition({{1, 1}, "aboba"});

  EXPECT_TRUE(first_transition == first_transition);
  EXPECT_TRUE(second_transition == second_transition);
  EXPECT_TRUE(third_transition == third_transition);
  EXPECT_TRUE(fouth_transition == fouth_transition);

  EXPECT_FALSE(first_transition == second_transition);
  EXPECT_FALSE(first_transition == third_transition);
  EXPECT_FALSE(first_transition == fouth_transition);
  EXPECT_FALSE(second_transition == third_transition);
  EXPECT_FALSE(second_transition == fouth_transition);
  EXPECT_FALSE(third_transition == fouth_transition);
}

TEST(NFA, StateDeletion) {
  NFA nfa({'a', 'b'});

  auto start_state_id = nfa.AddStartState(true);
  auto second_state_id = nfa.AddState(true);

  nfa.AddTransition({{start_state_id, second_state_id}, "a"});

  nfa.DeleteState(start_state_id);

  EXPECT_FALSE(nfa.IsValid());
  EXPECT_EQ(nfa.GetStatesId().size(), 1);
  EXPECT_FALSE(nfa.IsState(start_state_id));
  EXPECT_EQ(nfa.GetFinalStatesId().size(), 1);
  EXPECT_EQ(std::max(nfa.GetTransitions().size(), std::size_t(1)), 1);

  if (nfa.GetTransitions().size() == 1) {
    EXPECT_EQ(std::max(nfa.GetTransitions().at(second_state_id).size(),
                       std::size_t(1)),
              1);

    if (nfa.GetTransitions().at(second_state_id).size() == 1) {
      EXPECT_EQ(
          nfa.GetTransitions().at(second_state_id).at(second_state_id).size(),
          0);
    }
  }
}