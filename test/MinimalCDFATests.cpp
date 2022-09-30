#include <gtest/gtest.h>

#include <MinimalCDFA.hpp>
#include <optional>

TEST(ChangeToMinimalCDFA, Correctness) {
  auto nfa = NFA({'a', 'b'});

  auto start = nfa.AddStartState();
  auto first = nfa.AddState();
  auto second = nfa.AddState();
  auto third = nfa.AddState(true);

  nfa.AddTransition({{start, first}, "a"});
  nfa.AddTransition({{start, second}, "b"});
  nfa.AddTransition({{first, second}, "b"});
  nfa.AddTransition({{second, first}, "b"});
  nfa.AddTransition({{first, third}, "a"});
  nfa.AddTransition({{second, third}, "a"});

  ChangeToMinimalCDFA(nfa);

  EXPECT_TRUE(nfa.IsValid());
  EXPECT_EQ(nfa.GetFinalStatesId().size(), 1);

  auto new_start = nfa.GetStartStateId();

  std::optional<StateId> second_state = std::nullopt;

  for (const auto& [destination, strings] :
       nfa.GetTransitions().at(new_start)) {
    if (!strings.empty()) {
      EXPECT_EQ(strings.size(), 2);
      EXPECT_TRUE(strings.contains("a"));
      EXPECT_TRUE(strings.contains("b"));
      second_state = destination;
    }
  }

  EXPECT_TRUE(second_state.has_value());

  std::optional<StateId> final_state = std::nullopt;

  for (const auto& [destination, strings] :
       nfa.GetTransitions().at(second_state.value())) {
    if (destination == second_state) {
      EXPECT_EQ(strings.size(), 1);
      EXPECT_TRUE(strings.contains("b"));
    } else if (!strings.empty()) {
      EXPECT_EQ(strings.size(), 1);
      EXPECT_TRUE(strings.contains("a"));
      EXPECT_TRUE(nfa.GetFinalStatesId().contains(destination));
      final_state = destination;
    }
  }

  EXPECT_TRUE(final_state.has_value());

  std::optional<StateId> sink_state = std::nullopt;

  for (const auto& [destination, strings] :
       nfa.GetTransitions().at(final_state.value())) {
    if (!strings.empty()) {
      EXPECT_EQ(strings.size(), 2);
      EXPECT_TRUE(strings.contains("a"));
      EXPECT_TRUE(strings.contains("b"));
      sink_state = destination;
    }
  }

  EXPECT_TRUE(sink_state.has_value());

  for (const auto& [destination, strings] :
       nfa.GetTransitions().at(sink_state.value())) {
    if (!strings.empty()) {
      EXPECT_EQ(strings.size(), 2);
      EXPECT_TRUE(strings.contains("a"));
      EXPECT_TRUE(strings.contains("b"));
      EXPECT_EQ(sink_state.value(), destination);
    }
  }
}