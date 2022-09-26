#include <gtest/gtest.h>

#include <DFA.hpp>

TEST(ChangeToDFA, AlreadyDFA1)
{
    NFA nfa({'a', 'b'});

    auto start_state = nfa.AddStartState();

    nfa.AddTransition({{start_state, start_state}, "a"});
    nfa.AddTransition({{start_state, start_state}, "b"});

    ChangeToDFA(nfa);

    EXPECT_TRUE(nfa.IsValid());

    auto new_start_state = nfa.GetStartStateId();

    EXPECT_EQ(nfa.GetStatesId().size(), 1);
    EXPECT_EQ(nfa.GetTransitions().at(new_start_state).at(new_start_state).size(), 2);
    EXPECT_TRUE(nfa.IsTransition({{new_start_state, new_start_state}, "a"}));
    EXPECT_TRUE(nfa.IsTransition({{new_start_state, new_start_state}, "b"}));
}

TEST(ChangeToDFA, AlreadyDFA2)
{
    NFA nfa({'a', 'b'});

    auto start_state = nfa.AddStartState();
    auto second_state = nfa.AddState(true);

    nfa.AddTransition({{start_state, second_state}, "a"});
    nfa.AddTransition({{start_state, second_state}, "b"});
    nfa.AddTransition({{second_state, start_state}, "a"});
    nfa.AddTransition({{second_state, start_state}, "b"});

    ChangeToDFA(nfa);

    EXPECT_TRUE(nfa.IsValid());

    auto new_start_state = nfa.GetStartStateId();

    EXPECT_EQ(nfa.GetStatesId().size(), 2);
    EXPECT_EQ(nfa[new_start_state][new_start_state].size(), 0);
}