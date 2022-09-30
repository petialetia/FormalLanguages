#include <gtest/gtest.h>

#include <CDFA.hpp>

TEST(ChangeToCDFA, AlreadyCDFA1)
{
    NFA nfa({'a', 'b'});

    auto start_state = nfa.AddStartState();

    nfa.AddTransition({{start_state, start_state}, "a"});
    nfa.AddTransition({{start_state, start_state}, "b"});

    ChangeToCDFA(nfa);

    EXPECT_TRUE(nfa.IsValid());

    auto new_start_state = nfa.GetStartStateId();

    EXPECT_EQ(nfa.GetStatesId().size(), 1);
    EXPECT_EQ(nfa.GetTransitions().at(new_start_state).at(new_start_state).size(), 2);
    EXPECT_TRUE(nfa.IsTransition({{new_start_state, new_start_state}, "a"}));
    EXPECT_TRUE(nfa.IsTransition({{new_start_state, new_start_state}, "b"}));
}

TEST(ChangeToCDFA, AlreadyCDFA2)
{
    NFA nfa({'a', 'b'});

    auto start_state = nfa.AddStartState();
    auto second_state = nfa.AddState(true);

    nfa.AddTransition({{start_state, second_state}, "a"});
    nfa.AddTransition({{start_state, second_state}, "b"});
    nfa.AddTransition({{second_state, start_state}, "a"});
    nfa.AddTransition({{second_state, start_state}, "b"});

    ChangeToCDFA(nfa);

    EXPECT_TRUE(nfa.IsValid());

    auto new_start_state = nfa.GetStartStateId();

    EXPECT_EQ(nfa.GetStatesId().size(), 2);
    EXPECT_EQ(nfa[new_start_state][new_start_state].size(), 0);
}

TEST(ChangeToCDFA, Complicated1)
{
    auto nfa = NFA({'a', 'b'});

    auto start = nfa.AddStartState();
    auto second = nfa.AddState();
    auto third = nfa.AddState(true);
    auto fouth = nfa.AddState();
    auto fifth = nfa.AddState();

    nfa.AddTransition({{start, second}, "a"});
    nfa.AddTransition({{start, third}, "a"});
    nfa.AddTransition({{second, third}, "b"});
    nfa.AddTransition({{start, fouth}, "a"});
    nfa.AddTransition({{fouth, fifth}, "b"});
    nfa.AddTransition({{fifth, third}, "b"});

    ChangeToCDFA(nfa);

    EXPECT_TRUE(nfa.IsValid());
}

TEST(ChangeToCDFA, Complicated2)
{
    auto nfa = NFA({'a', 'b', 'c'});

    auto start = nfa.AddStartState();
    auto first = nfa.AddState();
    auto second = nfa.AddState();
    auto third = nfa.AddState();
    auto fouth = nfa.AddState(true);
    auto fifth = nfa.AddState();
    auto sixth = nfa.AddState(true);

    nfa.AddTransition({{start, first}, "a"});
    nfa.AddTransition({{start, fifth}, "a"});
    nfa.AddTransition({{start, second}, "b"});
    nfa.AddTransition({{start, third}, "b"});
    nfa.AddTransition({{third, second}, "c"});
    nfa.AddTransition({{fifth, second}, "b"});
    nfa.AddTransition({{second, fifth}, "a"});
    nfa.AddTransition({{first, third}, "b"});
    nfa.AddTransition({{third, first}, "a"});
    nfa.AddTransition({{first, fouth}, "c"});
    nfa.AddTransition({{fifth, sixth}, "c"});
    nfa.AddTransition({{second, sixth}, "c"});
    nfa.AddTransition({{third, fouth}, "c"});

    ChangeToCDFA(nfa);

    EXPECT_TRUE(nfa.IsValid());
}