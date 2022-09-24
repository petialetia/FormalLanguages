#include <NFA.hpp>

bool NFA::IsValid()
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

    states_.insert(new_state_id);

    is_states_final_[new_state_id] = is_final;

    EvaluateNextStateId();

    return new_state_id;
}

void NFA::AddTransition(StateId start, StateId finish, std::string string)
{
    if (!transitions_[start][finish].has_value())
    {
        transitions_[start][finish] = std::unordered_set<std::string>();
    }

    transitions_[start][finish].value().insert(string);
}

void NFA::EvaluateNextStateId()
{
    ++next_state_id_;

    assert(next_state_id_ != 0); //Overflow catching
}