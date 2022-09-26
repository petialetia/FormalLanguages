#include <DFA.hpp>

void ChangeToDFA(NFA& nfa)
{
    RemoveEpsilonTransitions(nfa);
    MakeTransitionsSingleLetter(nfa);

    auto sink_id = nfa.AddState(false);

    for (const auto& symbol : nfa.GetAlphabet())
    {
        nfa.AddTransition({{sink_id, sink_id}, std::string(1, symbol)});
    }

    auto final_states = nfa.GetFinalStatesId();
    std::unordered_map<StateId, std::unordered_map<char, std::unordered_set<StateId>>> transitions_table;
    std::unordered_map<StateId, std::unordered_set<StateId>> new_states_info;
    std::unordered_map<std::unordered_set<StateId>, StateId, UnorderedSetHash<StateId>> new_destinations_info;

    for (const auto& current_state_id : nfa.GetStatesId())
    {
        if (current_state_id == sink_id)
            continue;

        if (new_states_info.contains(current_state_id))
            continue;

        for (const auto& [other_state_id, strings] : nfa.GetTransitions().at(current_state_id))
        {
            for (const auto& string: strings)
            {
                transitions_table[current_state_id][string[0]].insert(other_state_id);
            }
        }

        for (const auto& symbol : nfa.GetAlphabet())
        {
            const auto& destinations = transitions_table[current_state_id][symbol];

            if (destinations.size() == 0)
            {
                nfa.AddTransition({{current_state_id, sink_id}, symbol});
                continue;
            }

            if (destinations.size() > 1)
            {
                if (!new_destinations_info.contains(destinations))
                {
                    StateId new_state_id = 0;

                    for(const auto& destination : destinations)
                    {
                        if (final_states.contains(destination))
                        {
                            new_state_id = nfa.AddState(true);
                            final_states.insert(new_state_id);
                            goto NEW_STATE_IS_ADDED; //in python it would be for-else construction
                        }
                    }

                    new_state_id = nfa.AddState(false);

                NEW_STATE_IS_ADDED:
                
                    new_states_info[new_state_id] = destinations;
                    new_destinations_info[destinations] = new_state_id;
                }

                auto destination_state_id = new_destinations_info[destinations];

                nfa.AddTransition({{current_state_id, destination_state_id}, symbol});

                for (const auto& destination: destinations)
                {
                    nfa.RemoveTransition({{current_state_id, destination}, symbol});
                }
            }
        }
    }

    DeleteUnreachableStates(nfa);
}