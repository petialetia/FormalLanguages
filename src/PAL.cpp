#include <PAL.hpp>

NFA ReadNFA(std::string file_name)
{
    std::ifstream pal_file(file_name);

    std::ostringstream sstr;
    sstr << pal_file.rdbuf();

    std::string pal_file_content = sstr.str();

    auto lines = Split(pal_file_content, "\n");

    auto string_alphabet = Split(*lines.cbegin(), " ");

    std::unordered_set<char> char_alphabet;

    for (const auto& string : string_alphabet)
    {
        char_alphabet.insert(string[0]);
    }

    NFA nfa(char_alphabet);

    auto states = Split(*std::next(lines.cbegin(), 1), " ");

    assert(states.size() > 0);

    std::unordered_map<std::string, StateId> state_identifiers;

    if (IsStateFinal(*states.cbegin()))
    {
        auto name = *states.cbegin();
        name.pop_back();
        state_identifiers[name] = nfa.AddStartState(true);
    }
    else
    {
        state_identifiers[*states.cbegin()] = nfa.AddStartState();
    }

    for (auto state_iterator = std::next(states.cbegin(), 1); 
         state_iterator != states.cend(); ++state_iterator)
    {
        if (IsStateFinal(*state_iterator))
        {
            auto name = *state_iterator;
            name.pop_back();
            state_identifiers[name] = nfa.AddState(true);
        }
        else
        {
            state_identifiers[*state_iterator] = nfa.AddState();
        }
    }

    for (auto transitions_string_iterator = std::next(lines.cbegin(), 2);
         transitions_string_iterator != lines.cend(); ++transitions_string_iterator)
    {
        auto tokens = Split(*transitions_string_iterator, " ");

        nfa.AddTransition({{state_identifiers.at(tokens[0]), state_identifiers.at(tokens[1])}, 
                           tokens[2]});
    }

    return nfa;
}

std::vector<std::string> Split(std::string string, std::string separators)
{
    std::vector<std::string> tokens;
    boost::split(tokens, string, boost::is_any_of(separators));

    return tokens;
}

bool IsStateFinal(const std::string& state_string)
{
    return state_string.back() == '!';
}