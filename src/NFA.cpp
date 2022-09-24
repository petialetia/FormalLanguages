#include <NFA.hpp>

bool NFA::IsValid() const
{
    return start_state_.has_value();
}

StateId NFA::AddStartState(bool is_final)
{
    start_state_ = next_state_id_;

    return AddState(is_final);
}

StateId NFA::AddState(bool is_final)
{
    auto new_state_id = next_state_id_;

    states_id_.insert(new_state_id);

    is_state_final_[new_state_id] = is_final;

    EvaluateNextStateId();

    return new_state_id;
}

void NFA::AddTransition(StateId start, StateId destination, std::string string)
{
    transitions_[start][destination].insert(string);
}

const std::unordered_set<StateId>& NFA::GetStatesId() const
{
    return states_id_;
}

StateId NFA::GetStartStateId() const
{
    assert(start_state_.has_value());

    return start_state_.value();
}

std::unordered_set<StateId> NFA::GetFinalStatesId() const
{
    std::unordered_set<StateId> final_states;

    for (const auto& [state_id, is_final] : is_state_final_)
    {
        if (is_final)
        {
            final_states.insert(state_id);
        }
    }

    return final_states;
}

const std::unordered_map<StateId, std::unordered_map<StateId, std::unordered_set<std::string>>>& NFA::GetTransitions() const
{
    return transitions_;
}

void NFA::EvaluateNextStateId()
{
    ++next_state_id_;

    assert(next_state_id_ != 0); //Overflow catching
}