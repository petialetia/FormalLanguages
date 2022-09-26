#include <DOA.hpp>

void SaveInDOA(const NFA& nfa, std::string file_name)
{
    if (!nfa.IsValid())
    {
        return;
    }

    std::ofstream doa_file;
    doa_file.open(file_name);

    doa_file << "DOA: v1\n";

    doa_file << "Start: " << nfa.GetStartStateId() << "\n";

    WriteAcceptance(nfa, doa_file);

    doa_file << "--BEGIN--\n";

    WriteStates(nfa, doa_file);

    doa_file << "--END--";

    doa_file.close();
}

void WriteAcceptance(const NFA& nfa, std::ofstream& doa_file)
{
    doa_file << "Acceptance: ";

    auto final_states_id = nfa.GetFinalStatesId();

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

void WriteStates(const NFA& nfa, std::ofstream& doa_file)
{
    for (const auto& state_id : nfa.GetStatesId())
    {
        doa_file << "State: " << state_id << "\n";

        if (!nfa.GetTransitions().contains(state_id))
            continue;

        for (const auto& [destination_id, strings] : nfa.GetTransitions().at(state_id))
        {
            for (const auto& string: strings)
            {
                doa_file << "\t-> " << (string != EPSILON ? string : "EPS") << " " << destination_id << "\n";
            }
        }
    } 
}