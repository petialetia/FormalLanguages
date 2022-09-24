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

    states_id_.insert(new_state_id);

    is_state_final_[new_state_id] = is_final;

    EvaluateNextStateId();

    return new_state_id;
}

void NFA::AddTransition(StateId start, StateId destination, std::string string)
{
    transitions_[start][destination].insert(string);
}

std::unordered_set<StateId> NFA::GetFinalStatesId()
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

void NFA::SaveInDOA(std::string file_name)
{
    if (!IsValid())
    {
        return;
    }

    std::ofstream doa_file;
    doa_file.open(file_name);

    doa_file << "DOA: v1\n";

    doa_file << "Start: " << start_state_.value() << "\n";

    WriteAcceptance(doa_file);

    doa_file << "--BEGIN--\n";

    WriteStates(doa_file);

    doa_file << "--END--\n";

    doa_file.close();
}

void NFA::EvaluateNextStateId()
{
    ++next_state_id_;

    assert(next_state_id_ != 0); //Overflow catching
}

void NFA::WriteAcceptance(std::ofstream& doa_file)
{
    doa_file << "Acceptance: ";

    auto final_states_id = GetFinalStatesId();

    auto final_state_id_iterator = final_states_id.cbegin();

    if (final_state_id_iterator != final_states_id.cend())
    {
        doa_file << *final_state_id_iterator;

        ++final_state_id_iterator;

        while (final_state_id_iterator != final_states_id.cend())
        {
            doa_file << " & " << *final_state_id_iterator;
            ++final_state_id_iterator;
        }
    }

    doa_file << "\n";
}

void NFA::WriteStates(std::ofstream& doa_file)
{
    for (const auto& state_id : states_id_)
    {
        doa_file << "State: " << state_id << "\n";

        for (const auto& [destination_id, strings] : transitions_[state_id])
        {
            for (const auto& string: strings)
            {
                doa_file << "\t-> " << (string != EPSILON ? string : "EPS") << " " << destination_id << "\n";
            }
        }
    }   
}