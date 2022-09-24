#ifndef NFA_HPP
#define NFA_HPP

#include <unordered_map>
#include <unordered_set>
#include <optional>
#include <string>
#include <fstream>

#include <assert.h>

using StateId = size_t;

const std::string EPSILON = "";

class NFA
{
  public:
    NFA() = default;

    bool IsValid() const;

    StateId AddStartState(bool is_final = false);

    StateId AddState(bool is_final = false);

    void AddTransition(StateId start, StateId destination, std::string string);

    const std::unordered_set<StateId>& GetStatesId() const;

    StateId GetStartStateId() const;

    std::unordered_set<StateId> GetFinalStatesId() const;

    const std::unordered_map<StateId, std::unordered_map<StateId, std::unordered_set<std::string>>>& GetTransitions() const;

  private:
    void EvaluateNextStateId();

  private:
    StateId next_state_id_ = 0;

    std::unordered_set<StateId> states_id_;

    std::unordered_map<StateId, std::unordered_map<StateId, std::unordered_set<std::string>>> transitions_;

    std::optional<StateId> start_state_ = std::nullopt;

    std::unordered_map<StateId, bool> is_state_final_;
};

#endif /* NFA_HPP */