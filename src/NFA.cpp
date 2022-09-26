#include <NFA.hpp>

Edge::Edge(StateId start, StateId destination) : start_(start), destination_(destination)
{
}

bool Edge::operator==(const Edge& other) const
{
    return start_ == other.start_ && destination_ == other.destination_;
}

std::size_t EdgeHash::operator() (const Edge& edge) const
{
    std::size_t seed = 0;
    boost::hash_combine(seed, edge.start_);
    boost::hash_combine(seed, edge.destination_);

    return seed;   
}

Transition::Transition(Edge edge, std::string string) : edge_(edge), string_(string)
{
}

Transition::Transition(Edge edge, char symbol) : edge_(edge), string_(1, symbol)
{
}

bool Transition::operator==(const Transition& other) const
{
    return edge_ == other.edge_ && string_ == other.string_;
}

std::size_t TransitionHash::operator() (const Transition& transition) const
{
    std::size_t seed = 0;
    boost::hash_combine(seed, transition.edge_.start_);
    boost::hash_combine(seed, transition.edge_.destination_);
    boost::hash_combine(seed, std::hash<decltype(transition.edge_.destination_)>()(transition.edge_.destination_));

    return seed;   
}

NFA::NFA(Alphabet alphabet) : alphabet_(alphabet)
{
}

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

void NFA::AddTransition(Transition transition)
{
    for (const auto& symbol : transition.string_)
    {
        assert(alphabet_.contains(symbol));
    }

    transitions_[transition.edge_.start_][transition.edge_.destination_].insert(transition.string_);
}

bool NFA::IsTransition(const Transition& transition) const
{
    if (!transitions_.contains(transition.edge_.start_))
        return false;


    if (!transitions_.at(transition.edge_.start_).contains(transition.edge_.destination_))
        return false;


    return transitions_.at(transition.edge_.start_).at(transition.edge_.destination_).contains(transition.string_);
}

const std::set<StateId>& NFA::GetStatesId() const
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

void NFA::DeleteState(StateId state_id)
{
    transitions_.erase(state_id);

    for (auto& [other_state_id, transitions_from_state] : transitions_)
    {
        transitions_from_state.erase(state_id);
    }

    states_id_.erase(state_id);

    is_state_final_.erase(state_id);

    if (start_state_.has_value())
    {
        if (start_state_.value() == state_id)
            start_state_ = std::nullopt;
    }
}

const TransitionsStorage& NFA::GetTransitions() const
{
    return transitions_;
}

void NFA::RemoveTransition(Transition transition)
{
    if (transitions_.contains(transition.edge_.start_) && 
        transitions_[transition.edge_.start_].contains(transition.edge_.destination_) &&
        transitions_[transition.edge_.start_][transition.edge_.destination_].contains(transition.string_))
    {
        transitions_[transition.edge_.start_][transition.edge_.destination_].erase(transition.string_);
    }
}

std::unordered_map<StateId, std::unordered_set<std::string>>& NFA::operator[](StateId id)
{
    return transitions_[id];
}

void NFA::MakeStateFinal(StateId state)
{
    is_state_final_[state] = true;
}

const Alphabet& NFA::GetAlphabet()
{
    return alphabet_;
}

void NFA::EvaluateNextStateId()
{
    ++next_state_id_;

    assert(next_state_id_ != 0); //Overflow catching
}