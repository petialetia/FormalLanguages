#include <EpsilonTransitionsRemoving.hpp>

void RemoveEpsilonTransitions(NFA& nfa)
{
    DeleteEpsilonOneStepCycles(nfa);
    EpsilonTransitiveClosureNFA(nfa);
    DeleteEpsilonOneStepCycles(nfa);
    AddFinalStates(nfa);
    AddTransitions(nfa);
    DeleteEpsilonTransitions(nfa);
    DeleteUnreachableStates(nfa);
}

void DeleteEpsilonOneStepCycles(NFA& nfa)
{
    for (const auto& state_id : nfa.GetStatesId())
    {
        nfa[state_id][state_id].erase(EPSILON);
    }
}

void EpsilonTransitiveClosureNFA(NFA& nfa)
{
    MakeEpsilonTransitiveClosure(nfa, GetEpsilonTransitions(nfa));
}

std::unordered_set<Edge, EdgeHash> GetEpsilonTransitions(const NFA& nfa)
{
    std::unordered_set<Edge, EdgeHash> epsilon_transitions;

    const auto transitions = nfa.GetTransitions();

    for (const auto& [start_state_id, transitions_from_start_state] : transitions)
    {
        for(const auto& [destination_state_id, strings] : transitions_from_start_state)
        {
            if (strings.contains(EPSILON))
            {
                epsilon_transitions.insert({start_state_id, destination_state_id});
            }
        }
    }

    return epsilon_transitions;
}

void MakeEpsilonTransitiveClosure(NFA& nfa, std::unordered_set<Edge, EdgeHash> epsilon_transitions)
{
START_OVER:

    for (auto first_edge_iterator = epsilon_transitions.cbegin();
         first_edge_iterator != epsilon_transitions.cend(); ++first_edge_iterator)
    {

        for (auto second_edge_iterator = epsilon_transitions.cbegin();
             second_edge_iterator != epsilon_transitions.cend(); ++second_edge_iterator)
        {
            if (((*first_edge_iterator).destination_ == (*second_edge_iterator).start_) &&
                (!epsilon_transitions.contains({(*first_edge_iterator).start_, (*second_edge_iterator).destination_})))
            {
                Edge new_transition_edge = {(*first_edge_iterator).start_, (*second_edge_iterator).destination_};
                nfa.AddTransition({new_transition_edge, EPSILON});
                epsilon_transitions.insert(new_transition_edge);
                goto START_OVER; //We have new transition, plus iterators invalidated, 
                                 //so we need to start from the begining
            }
        }
    }
}

void AddFinalStates(NFA& nfa)
{
    auto final_states = nfa.GetFinalStatesId();

    auto transitions = nfa.GetTransitions();

START_OVER:

    for (const auto state_id : nfa.GetStatesId())
    {
        if (final_states.contains(state_id))
            continue;

        for (const auto& [one_step_reachable_state, strings] : transitions.at(state_id))
        {
            if (final_states.contains(one_step_reachable_state) && strings.contains(EPSILON))
            {
                final_states.insert(state_id);
                nfa.MakeStateFinal(state_id);
                goto START_OVER; //New final state can make another state final, 
                                 //but we could check it before, so we need to start over
            }
        }
    }
}

void AddTransitions(NFA& nfa)
{
    auto epsilon_transitions = GetEpsilonTransitions(nfa);
    
START_OVER:

    for (auto epsilon_edge_iterator = epsilon_transitions.cbegin();
         epsilon_edge_iterator != epsilon_transitions.cend(); ++epsilon_edge_iterator)
    {
        bool is_start_over_needed = false;

        for (const auto& [one_step_reachable_state, strings] : nfa[(*epsilon_edge_iterator).destination_])
        {
            for (const auto& string : strings)
            {
                Transition new_transition = {{(*epsilon_edge_iterator).start_, one_step_reachable_state}, string};
                if (!nfa.IsTransition(new_transition))
                {
                    nfa.AddTransition(new_transition);
                    is_start_over_needed = true; //we added new transition, 
                                                 //that means we could add another transition,
                                                 //but we could process needed epsilon edge already

                }
            }
        }

        if (is_start_over_needed)
            goto START_OVER;
    }
}

void DeleteEpsilonTransitions(NFA& nfa)
{
    for (const auto first_state_id : nfa.GetStatesId())
    {
        for (const auto second_state_id : nfa.GetStatesId())
        {
            nfa[first_state_id][second_state_id].erase(EPSILON);
        }
    }
}

void DeleteUnreachableStates(NFA& nfa)
{
    assert(nfa.IsValid());

    std::unordered_set<StateId> reachable_states;
    reachable_states.insert(nfa.GetStartStateId());

    std::deque<StateId> states_to_visit;
    states_to_visit.push_back(nfa.GetStartStateId());

    while (!states_to_visit.empty())
    {
        auto state_to_visit = states_to_visit.front();
        states_to_visit.pop_front();

        for (const auto& [reachable_state, strings] : nfa[state_to_visit])
        {
            if (!strings.empty())
            {
                if (!reachable_states.contains(reachable_state))
                {
                    reachable_states.insert(reachable_state);
                    states_to_visit.push_back(reachable_state);
                }
            }
        }
    }

    std::unordered_set<StateId> states = nfa.GetStatesId();

    for (auto state : states)
    {
        if(!reachable_states.contains(state))
            nfa.DeleteState(state);
    }
}