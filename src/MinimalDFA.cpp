#include <MinimalDFA.hpp>

/*int main()
{
    auto nfa = NFA({'a', 'b'});

    auto start = nfa.AddStartState();
    auto first = nfa.AddState();
    auto second = nfa.AddState();
    auto third = nfa.AddState(true);

    nfa.AddTransition({{start, first}, "a"});
    nfa.AddTransition({{start, second}, "b"});
    nfa.AddTransition({{first, second}, "b"});
    nfa.AddTransition({{second, first}, "b"});
    nfa.AddTransition({{first, third}, "a"});
    nfa.AddTransition({{second, third}, "a"});

    ChangeToMinimalDFA(nfa);

    SaveInDOA(nfa);

    return 0;
}*/

bool StateAndNeighboursClasses::operator==(const StateAndNeighboursClasses& other) const
{
    return class_id_ == other.class_id_ &&
           neighbours_classes_ == other.neighbours_classes_;
}

std::size_t StateAndNeighboursClassesHash::operator() (const StateAndNeighboursClasses& classes) const
{
    std::size_t seed = 0;

    boost::hash_combine(seed, classes.class_id_);

    for (auto iterator = classes.neighbours_classes_.cbegin(); 
         iterator != classes.neighbours_classes_.cend(); iterator++)
    {
        boost::hash_combine(seed, boost::hash_value(*iterator));
    }

    return seed;
}

size_t GetNumOfClasses(const StateClassInfos& class_infos)
{
    std::unordered_set<ClassId> classes;

    for (const auto& [state_id, class_id] : class_infos)
    {
        classes.insert(class_id);
    }

    return classes.size();
}

void ChangeToMinimalDFA(NFA& nfa)
{
    ChangeToDFA(nfa);

    auto current_stage_classes = GetStartClasses(nfa);

    auto next_stage_classes = GetNextStageClasses(nfa, current_stage_classes);

    while(GetNumOfClasses(current_stage_classes) != GetNumOfClasses(next_stage_classes))
    {
        current_stage_classes = next_stage_classes;
        next_stage_classes = GetNextStageClasses(nfa, current_stage_classes); 
    }

    std::unordered_map<ClassId, StateId> class_to_state;

    for (const auto& [state_id, class_id] : current_stage_classes)
    {
        if (!class_to_state.contains(class_id))
        {
            class_to_state[class_id] = state_id;
        }
        else
        {
            MergeStates(nfa, class_to_state[class_id], state_id);
        }
    }
}

StateClassInfos GetStartClasses(const NFA& nfa)
{
    StateClassInfos start_classes;

    for (const auto& state : nfa.GetStatesId())
    {
        start_classes[state] = nfa.IsStateFinal(state) ? 1 : 0;
    }

    return start_classes;
}

StateClassInfos GetNextStageClasses(const NFA& nfa, const StateClassInfos& current_stage_classes)
{
    std::unordered_map<StateId, std::vector<ClassId>> transition_table;

    for (const auto& state : nfa.GetStatesId())
    {
        for (const auto& letter : nfa.GetAlphabet())
        {
            auto neighbour_state = GetDestinationsByString(nfa, state, letter);
            assert(neighbour_state.size() == 1);

            transition_table[state].push_back(current_stage_classes.at(*neighbour_state.cbegin()));
        }
    }

    StateClassInfos new_stage_classes;

    ClassId next_class_id = 0;

    std::unordered_map<StateAndNeighboursClasses, ClassId, StateAndNeighboursClassesHash> new_classes;

    for (const auto& state : nfa.GetStatesId())
    {
        StateAndNeighboursClasses nearest_classes = {.class_id_ = current_stage_classes.at(state),
                                                     .neighbours_classes_ = transition_table[state]};

        if (new_classes.contains(nearest_classes))
        {
            new_stage_classes[state] = new_classes[nearest_classes];
        }
        else
        {
            new_classes[nearest_classes] = next_class_id;
            new_stage_classes[state] = next_class_id;
            ++next_class_id;
        }
    }

    return new_stage_classes;
}

void MergeStates(NFA& nfa, StateId base_state, StateId state_to_attach)
{
    for (const auto& [state, transitions_from_state] : nfa.GetTransitions())
    {
        if (state == state_to_attach)
            continue;


        if (transitions_from_state.contains(state_to_attach) && 
            !transitions_from_state.at(state_to_attach).empty())
        {
            for (const auto& string : transitions_from_state.at(state_to_attach))
            {
                nfa.AddTransition({{state, base_state}, string});
            }
        }
    }

    nfa.DeleteState(state_to_attach);
}