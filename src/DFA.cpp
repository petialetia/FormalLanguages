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

    std::unordered_map<StateId, std::unordered_set<StateId>> new_states_info;
    std::unordered_map<std::unordered_set<StateId>, StateId, UnorderedSetHash<StateId>> new_destinations_info;

    auto transitions_table = ProcessNormalStates(nfa, new_states_info, new_destinations_info, final_states, sink_id);

    ProcessCompositStates(nfa, new_states_info, new_destinations_info, final_states, sink_id, transitions_table);

    DeleteUnreachableStates(nfa);
}

std::unordered_map<StateId, std::unordered_map<char, std::unordered_set<StateId>>> ProcessNormalStates(NFA& nfa, std::unordered_map<StateId, std::unordered_set<StateId>>& new_states_info,
                                                                                                       std::unordered_map<std::unordered_set<StateId>, StateId, UnorderedSetHash<StateId>>& new_destinations_info,
                                                                                                       std::unordered_set<StateId>& final_states, StateId sink_id)
{
    std::unordered_map<StateId, std::unordered_map<char, std::unordered_set<StateId>>> transitions_table;

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
                    auto new_state_id = AddCompositState(nfa, destinations, final_states);

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

    return transitions_table;
}

StateId AddCompositState(NFA& nfa, const std::unordered_set<StateId>& states, const std::unordered_set<StateId>& final_states)
{
    for(const auto& state : states)
    {
        if (final_states.contains(state))
        {
            return nfa.AddState(true);
        }
    }

    return nfa.AddState(false);
}

void ProcessCompositStates(NFA& nfa, std::unordered_map<StateId, std::unordered_set<StateId>>& new_states_info,
                           std::unordered_map<std::unordered_set<StateId>, StateId, UnorderedSetHash<StateId>>& new_destinations_info,
                           std::unordered_set<StateId>& final_states, StateId sink_id,
                           std::unordered_map<StateId, std::unordered_map<char, std::unordered_set<StateId>>>& transitions_table)
{
    std::deque<StateId> queue_for_procession;

    for (const auto& [composit_state, old_states] : new_states_info)
    {
        queue_for_procession.push_back(composit_state);
    }

    while(!queue_for_procession.empty())
    {
        auto current_composit_state = queue_for_procession.front();
        queue_for_procession.pop_front();

        const auto& old_states = new_states_info[current_composit_state];

        for (const auto& symbol : nfa.GetAlphabet())
        {
            std::unordered_set<StateId> destinations_by_symbol;
            for (const auto& old_state : old_states)
            {
                destinations_by_symbol.insert(transitions_table[old_state][symbol].cbegin(), 
                                              transitions_table[old_state][symbol].cend());
            }


            if (destinations_by_symbol.size() == 0)
            {
                nfa.AddTransition({{current_composit_state, sink_id}, symbol});
                continue;
            }


            if (destinations_by_symbol.size() == 1)
            {
                nfa.AddTransition({{current_composit_state, *destinations_by_symbol.cbegin()}, symbol});
                continue;
            }


            if (destinations_by_symbol.size() > 2)
            {
                if (new_destinations_info.contains(destinations_by_symbol))
                {
                    nfa.AddTransition({{current_composit_state, new_destinations_info[destinations_by_symbol]}, symbol});
                }
                else
                {
                    auto new_state_id = AddCompositState(nfa, destinations_by_symbol, final_states);
                    queue_for_procession.push_back(new_state_id);
                    
                    nfa.AddTransition({{current_composit_state, new_state_id}, symbol});
                }
            }
        }
    }
}