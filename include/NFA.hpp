#ifndef NFA_HPP
#define NFA_HPP

#include <unordered_map>
#include <unordered_set>
#include <optional>
#include <string>
#include <fstream>

#include <assert.h>

#include <boost/functional/hash.hpp>

using StateId = size_t;
using TransitionsStorage = std::unordered_map<StateId, std::unordered_map<StateId, std::unordered_set<std::string>>>;

const std::string EPSILON = "";

struct Edge
{
    StateId start_;
    StateId destination_;

    Edge(StateId start, StateId destination);

    bool operator==(const Edge& other) const;
};

struct EdgeHash
{
    std::size_t operator() (const Edge& edge) const;
};

struct Transition
{
    Edge edge_;
    std::string string_;

    Transition(Edge edge, std::string string);
    Transition(Edge edge, char symbol);

    bool operator==(const Transition& other) const;
};

struct TransitionHash
{
    std::size_t operator() (const Transition& edge) const;
};

using Alphabet = std::set<char>;

class NFA
{
  public:
    NFA() = delete;

    NFA(Alphabet alphabet);

    bool IsValid() const;

    StateId AddStartState(bool is_final = false);

    StateId AddState(bool is_final = false);

    void AddTransition(Transition transition);

    bool IsTransition(const Transition& transition) const;

    const std::set<StateId>& GetStatesId() const;

    StateId GetStartStateId() const;

    std::unordered_set<StateId> GetFinalStatesId() const;

    void DeleteState(StateId state_id);

    const TransitionsStorage& GetTransitions() const;

    void RemoveTransition(Transition transition);

    std::unordered_map<StateId, std::unordered_set<std::string>>& operator[](StateId id);

    void MakeStateFinal(StateId state);

    const Alphabet& GetAlphabet();

  private:
    void EvaluateNextStateId();

  private:
    StateId next_state_id_ = 0;

    std::set<StateId> states_id_;

    TransitionsStorage transitions_;

    std::optional<StateId> start_state_ = std::nullopt;

    std::unordered_map<StateId, bool> is_state_final_;

    const Alphabet alphabet_;
};

#endif /* NFA_HPP */