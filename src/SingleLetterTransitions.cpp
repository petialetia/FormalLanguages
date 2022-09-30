#include <SingleLetterTransitions.hpp>
#include <iostream>

void MakeTransitionsSingleLetter(NFA& nfa) {
  std::unordered_set<Transition, TransitionHash> transitions_to_add;
  std::unordered_set<Transition, TransitionHash> transitions_to_remove;

  for (const auto& [start_state_id, transitions_from_start_state] :
       nfa.GetTransitions()) {
    for (const auto& [destination_state_id, strings] :
         transitions_from_start_state) {
      for (const auto& string : strings) {
        if (string.length() >= 2) {
          transitions_to_remove.insert(
              {{start_state_id, destination_state_id}, string});

          std::unordered_set<StateId> added_states;

          for (size_t i = 0; i < string.length() - 1; ++i) {
            auto new_state = nfa.AddState();
            added_states.insert(new_state);
          }

          auto added_states_iterator = added_states.cbegin();

          transitions_to_add.insert({{start_state_id, *added_states_iterator},
                                     std::string(1, string[0])});

          for (size_t i = 1; i < string.length() - 1;
               ++i, ++added_states_iterator) {
            transitions_to_add.insert(
                {{*added_states_iterator, *std::next(added_states_iterator, 1)},
                 std::string(1, string[i])});
          }

          assert(std::next(added_states_iterator, 1) == added_states.cend());

          transitions_to_add.insert(
              {{*added_states_iterator, destination_state_id},
               string[string.length() - 1]});
        }
      }
    }
  }

  for (const auto& transition_to_remove : transitions_to_remove) {
    nfa.RemoveTransition(transition_to_remove);
  }

  for (const auto& transition_to_add : transitions_to_add) {
    nfa.AddTransition(transition_to_add);
  }
}