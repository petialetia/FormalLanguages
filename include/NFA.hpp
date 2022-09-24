#ifndef N_F_A_HPP
#define N_F_A_HPP

#include <unordered_map>
#include <unordered_set>
#include <optional>
#include <string>

#include <assert.h>

using StateId = size_t;

const std::string EPSILON = "";

class NFA
{
  public:
    NFA() = default;

    bool IsValid();

    StateId AddStartState(bool is_final = false);

    StateId AddState(bool is_final = false);

    void AddTransition(StateId start, StateId finish, std::string string);

  private:
    void EvaluateNextStateId();

  private:
    StateId next_state_id_ = 0;

    std::unordered_set<StateId> states_;

    std::unordered_map<StateId, std::unordered_map<StateId, std::optional<std::unordered_set<std::string>>>> transitions_;

    std::optional<StateId> start_state_ = std::nullopt;

    std::unordered_map<StateId, bool> is_states_final_;
};

#endif /* N_F_A_HPP */