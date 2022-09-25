#include <gtest/gtest.h>

#include <SingleLetterTransitions.hpp>

#include <DOA.hpp>

TEST(MakeTransitionsSingleLetter, Correctness1)
{
    NFA nfa;

    auto start_state_id = nfa.AddStartState();
    auto second_state_id = nfa.AddState(true);

    nfa.AddTransition({{start_state_id, second_state_id}, "abcd"});

    MakeTransitionsSingleLetter(nfa);

    EXPECT_EQ(nfa.GetStatesId().size(), 5);
}