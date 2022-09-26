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
    std::unordered_map<StateId, std::unordered_map<char, std::set<StateId>>> transition_table;
    std::unordered_map<StateId, std::set<StateId>> new_states_info;
    std::unordered_set<std::unordered_set<StateId>, boost::hash<std::unordered_set<StateId>>> new_states_combinations;

    for (const auto& state_id : nfa.GetStatesId())
    {
        if (state_id == sink_id)
            continue;

        
        for (const auto& [other_state_id, strings] : transitions_[state_id])
        {
            for (const auto& string: strings)
            {
                transition_table[state_id][string[0]].insert(other_state_id);
            }
        }

        for (const auto& [symbol, destinations] : transition_table[state_id])
        {
            if (destinations.size() == 0)
            {
                nfa.AddTransition({{state_id, sink_id}, symbol});
                continue;
            }


            if (destinations.size() > 1)
            {
                StateId new_state_id = 0;

                for(const auto& destination : destinations)
                {
                    if (final_states.contains(destination))
                    {
                        auto new_state_id = nfa.AddState(true);
                        final_states.insert(new_state_id);
                        goto NEW_STATE_IS_ADDED;
                    }
                }
                
                new_state_id = nfa.AddState(false);

            NEW_STATE_IS_ADDED:

                new_states_info[new_state_id] = destinations;

                nfa.AddTransition({{state_id, new_state_id}, symbol});
            }
        }
    }
}