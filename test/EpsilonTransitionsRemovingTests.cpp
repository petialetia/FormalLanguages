#include <gtest/gtest.h>

#include <EpsilonTransitionsRemoving.hpp>

#include <initializer_list>

TEST(GetEpsilonTransitions, Correctness)
{
    NFA nfa(std::initializer_list<char>{});

    auto start_state_id = nfa.AddStartState();
    auto second_state_id = nfa.AddState();

    nfa.AddTransition({{start_state_id, second_state_id}, EPSILON});
    nfa.AddTransition({{second_state_id, start_state_id}, EPSILON});

    nfa.AddTransition({{start_state_id, start_state_id}, EPSILON});

    auto epsilon_transitions = GetEpsilonTransitions(nfa);

    EXPECT_EQ(epsilon_transitions.size(), 3);
    EXPECT_TRUE(epsilon_transitions.contains({start_state_id, second_state_id}));
    EXPECT_TRUE(epsilon_transitions.contains({second_state_id, start_state_id}));
    EXPECT_TRUE(epsilon_transitions.contains({start_state_id, start_state_id}));
    EXPECT_FALSE(epsilon_transitions.contains({second_state_id, second_state_id}));
}

TEST(MakeEpsilonTransitiveClosure, Correctness1)
{
    NFA nfa(std::initializer_list<char>{});

    auto start_state_id = nfa.AddStartState();
    auto second_state_id = nfa.AddState();

    nfa.AddTransition({{start_state_id, second_state_id}, EPSILON});
    nfa.AddTransition({{second_state_id, start_state_id}, EPSILON});

    nfa.AddTransition({{start_state_id, start_state_id}, EPSILON});

    EpsilonTransitiveClosureNFA(nfa);

    auto transitions = nfa.GetTransitions();

    auto start_state_transitions_iterator = transitions.find(start_state_id);
    EXPECT_FALSE(start_state_transitions_iterator == transitions.end());

    auto second_state_transitions_iterator = transitions.find(second_state_id);
    EXPECT_FALSE(second_state_transitions_iterator == transitions.end());

    auto start_to_start_transitions_iterator = (*start_state_transitions_iterator).second.find(start_state_id);
    EXPECT_FALSE(start_to_start_transitions_iterator == (*start_state_transitions_iterator).second.end());

    auto start_to_second_transitions_iterator = (*start_state_transitions_iterator).second.find(second_state_id);
    EXPECT_FALSE(start_to_second_transitions_iterator == (*start_state_transitions_iterator).second.end());

    auto second_to_start_transitions_iterator = (*second_state_transitions_iterator).second.find(start_state_id);
    EXPECT_FALSE(second_to_start_transitions_iterator == (*second_state_transitions_iterator).second.end());

    auto second_to_second_transitions_iterator = (*second_state_transitions_iterator).second.find(second_state_id);
    EXPECT_FALSE(second_to_second_transitions_iterator == (*second_state_transitions_iterator).second.end());

    EXPECT_TRUE((*start_to_start_transitions_iterator).second.contains(EPSILON));
    EXPECT_TRUE((*start_to_second_transitions_iterator).second.contains(EPSILON));
    EXPECT_TRUE((*second_to_start_transitions_iterator).second.contains(EPSILON));
    EXPECT_TRUE((*second_to_second_transitions_iterator).second.contains(EPSILON));
}

TEST(MakeEpsilonTransitiveClosure, Correctness2)
{
    NFA nfa(std::initializer_list<char>{});

    auto start_state_id = nfa.AddStartState();
    auto second_state_id = nfa.AddState();
    auto third_state_id = nfa.AddState();

    nfa.AddTransition({{start_state_id, second_state_id}, EPSILON});
    nfa.AddTransition({{second_state_id, start_state_id}, EPSILON});

    nfa.AddTransition({{start_state_id, third_state_id}, EPSILON});

    EpsilonTransitiveClosureNFA(nfa);

    auto transitions = nfa.GetTransitions();

    EXPECT_TRUE(transitions.at(start_state_id).at(start_state_id).contains(EPSILON));
    EXPECT_TRUE(transitions.at(start_state_id).at(second_state_id).contains(EPSILON));
    EXPECT_TRUE(transitions.at(second_state_id).at(start_state_id).contains(EPSILON));
    EXPECT_TRUE(transitions.at(second_state_id).at(second_state_id).contains(EPSILON));
    EXPECT_TRUE(transitions.at(start_state_id).at(third_state_id).contains(EPSILON));
    EXPECT_TRUE(transitions.at(second_state_id).at(third_state_id).contains(EPSILON));

    EXPECT_FALSE(transitions.contains(third_state_id));
}

TEST(AddFinalStates, Correctness1)
{
    NFA nfa(std::initializer_list<char>{});

    auto start_state_id = nfa.AddStartState();
    auto second_state_id = nfa.AddState();
    auto third_state_id = nfa.AddState(true);

    nfa.AddTransition({{start_state_id, second_state_id}, EPSILON});
    nfa.AddTransition({{second_state_id, third_state_id}, EPSILON});

    AddFinalStates(nfa);

    auto final_states = nfa.GetFinalStatesId();

    EXPECT_EQ(final_states.size(), 3);
    EXPECT_TRUE(final_states.contains(start_state_id));
    EXPECT_TRUE(final_states.contains(second_state_id));
    EXPECT_TRUE(final_states.contains(third_state_id));
}

TEST(AddFinalStates, Correctness2)
{
    NFA nfa(std::initializer_list<char>{});

    auto start_state_id = nfa.AddStartState(true);
    auto second_state_id = nfa.AddState();
    auto third_state_id = nfa.AddState();

    nfa.AddTransition({{second_state_id, start_state_id}, EPSILON});
    nfa.AddTransition({{third_state_id, second_state_id}, EPSILON});

    AddFinalStates(nfa);

    auto final_states = nfa.GetFinalStatesId();

    EXPECT_EQ(final_states.size(), 3);
    EXPECT_TRUE(final_states.contains(start_state_id));
    EXPECT_TRUE(final_states.contains(second_state_id));
    EXPECT_TRUE(final_states.contains(third_state_id));
}

TEST(AddTransitions, Correctness1)
{
    NFA nfa({'a', 'b', 'c'});

    auto start_state_id = nfa.AddStartState();
    auto second_state_id = nfa.AddState();
    auto third_state_id = nfa.AddState();
    auto fouth_state_id = nfa.AddState();

    nfa.AddTransition({{start_state_id, second_state_id}, EPSILON});
    nfa.AddTransition({{second_state_id, third_state_id}, EPSILON});
    nfa.AddTransition({{start_state_id, third_state_id}, EPSILON});
    nfa.AddTransition({{third_state_id, fouth_state_id}, "abc"});

    AddTransitions(nfa);

    auto transitions = nfa.GetTransitions();

    EXPECT_TRUE(transitions.at(start_state_id).contains(fouth_state_id));
    EXPECT_TRUE(transitions.at(start_state_id).at(fouth_state_id).contains("abc"));

    EXPECT_TRUE(transitions.at(second_state_id).contains(fouth_state_id));
    EXPECT_TRUE(transitions.at(second_state_id).at(fouth_state_id).contains("abc"));
}

TEST(AddTransitions, Correctness2)
{
    NFA nfa({'a', 'b', 'c'});

    auto start_state_id = nfa.AddStartState();
    auto second_state_id = nfa.AddState();
    auto third_state_id = nfa.AddState();
    auto fouth_state_id = nfa.AddState();

    nfa.AddTransition({{start_state_id, second_state_id}, EPSILON});
    nfa.AddTransition({{second_state_id, third_state_id}, EPSILON});
    nfa.AddTransition({{third_state_id, fouth_state_id}, "abc"});

    AddTransitions(nfa);

    auto transitions = nfa.GetTransitions();

    EXPECT_TRUE(transitions.at(start_state_id).contains(fouth_state_id));
    EXPECT_TRUE(transitions.at(start_state_id).at(fouth_state_id).contains("abc"));

    EXPECT_TRUE(transitions.at(second_state_id).contains(fouth_state_id));
    EXPECT_TRUE(transitions.at(second_state_id).at(fouth_state_id).contains("abc"));
}

TEST(DeleteEpsilonTransitions, Correctness)
{
    NFA nfa({'a', 'b', 'c'});

    auto start_state_id = nfa.AddStartState();
    auto second_state_id = nfa.AddState();
    auto third_state_id = nfa.AddState();

    nfa.AddTransition({{start_state_id, second_state_id}, EPSILON});
    nfa.AddTransition({{start_state_id, third_state_id}, EPSILON});
    nfa.AddTransition({{second_state_id, second_state_id}, EPSILON});
    nfa.AddTransition({{second_state_id, third_state_id}, "abc"});

    DeleteEpsilonTransitions(nfa);

    EXPECT_FALSE(nfa.IsTransition({{start_state_id, second_state_id}, EPSILON}));
    EXPECT_FALSE(nfa.IsTransition({{start_state_id, third_state_id}, EPSILON}));
    EXPECT_FALSE(nfa.IsTransition({{second_state_id, second_state_id}, EPSILON}));
    EXPECT_TRUE(nfa.IsTransition({{second_state_id, third_state_id}, "abc"}));
}

TEST(DeleteUnreachableStates, Correctness)
{
    NFA nfa({'a', 'b', 'c', 'd'});

    auto start_state_id = nfa.AddStartState();
    auto second_state_id = nfa.AddState();
    auto third_state_id = nfa.AddState();
    auto fouth_state_id = nfa.AddState();

    nfa.AddTransition({{start_state_id, second_state_id}, "b"});
    nfa.AddTransition({{second_state_id, start_state_id}, "d"});
    nfa.AddTransition({{second_state_id, second_state_id}, "c"});
    nfa.AddTransition({{third_state_id, start_state_id}, "a"});

    DeleteUnreachableStates(nfa);

    auto states = nfa.GetStatesId();

    EXPECT_EQ(states.size(), 2);
    EXPECT_TRUE(states.contains(start_state_id));
    EXPECT_TRUE(states.contains(second_state_id));
    EXPECT_FALSE(states.contains(third_state_id));
    EXPECT_FALSE(states.contains(fouth_state_id));
}

TEST(RemoveEpsilonTransitions, Correctness1)
{
    NFA nfa(std::initializer_list<char>{});

    auto start_state_id = nfa.AddStartState();
    auto second_state_id = nfa.AddState();
    auto third_state_id = nfa.AddState();
    auto fouth_state_id = nfa.AddState(true);

    nfa.AddTransition({{start_state_id, second_state_id}, EPSILON});
    nfa.AddTransition({{start_state_id, third_state_id}, EPSILON});
    nfa.AddTransition({{second_state_id, third_state_id}, EPSILON});
    nfa.AddTransition({{third_state_id, second_state_id}, EPSILON});
    nfa.AddTransition({{second_state_id, fouth_state_id}, EPSILON});
    nfa.AddTransition({{third_state_id, fouth_state_id}, EPSILON});

    RemoveEpsilonTransitions(nfa);

    EXPECT_TRUE(nfa.IsValid());

    EXPECT_EQ(nfa.GetStatesId().size(), 1);

    auto new_start_state_id = nfa.GetStartStateId();

    EXPECT_EQ(nfa.GetFinalStatesId().size(), 1);
    EXPECT_TRUE(nfa.GetFinalStatesId().contains(new_start_state_id));

    EXPECT_EQ(nfa.GetTransitions().size(), 1);
    EXPECT_EQ(std::max(nfa[new_start_state_id].size(), std::size_t(1)), 1);
}

TEST(RemoveEpsilonTransitions, Correctness2)
{
    NFA nfa({'a', 'b'});

    auto start_state_id = nfa.AddStartState();
    auto second_state_id = nfa.AddState(true);
    auto third_state_id = nfa.AddState(true);
    auto fouth_state_id = nfa.AddState(true);

    nfa.AddTransition({{start_state_id, second_state_id}, EPSILON});
    nfa.AddTransition({{second_state_id, third_state_id}, "a"});
    nfa.AddTransition({{fouth_state_id, second_state_id}, "b"});

    RemoveEpsilonTransitions(nfa);

    EXPECT_TRUE(nfa.IsValid());

    EXPECT_EQ(nfa.GetStatesId().size(), 2);

    auto new_start_state_id = nfa.GetStartStateId();

    EXPECT_EQ(nfa.GetFinalStatesId().size(), 2);

    EXPECT_EQ(nfa.GetTransitions().size(), 2);

    EXPECT_EQ(std::max(nfa[new_start_state_id].size(), std::size_t(2)), 2);
}