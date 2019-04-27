//
//  tictactoe.hpp
//  tictactoe
//
//  Created by Semin Park on 23/01/2019.
//  Copyright © 2019 Semin Park. All rights reserved.
//

#ifndef tictactoe_hpp
#define tictactoe_hpp

#include <array>
#include <string>
#include <tuple>

#include <torch/torch.h>

#include "types.hpp"

class TicTacToe {
public:
#ifdef _LINUX
    using shape_type = long;
#else
    using shape_type = long long;
#endif // _LINUX
    
    using state_type = State;
    using reward_type = Reward;

    using id_type = ID;
    using board_type = Board;
    using action_type = Action;
    
private:
    enum { DRAW, WIN, CONTINUE };

    int size{3}; // width and height
    int c_in{3};
    int c_out{1};
    int turn = 2; // index for turn
    int num_players = 2;

    std::array<shape_type, 3> board_shape {c_in, size, size}; // one for each player + one for indicating turn
    std::array<shape_type, 3> action_shape {c_out, size, size};

public:
    static TicTacToe& get() {
        static TicTacToe unique;
        return unique;
    }
    
    // Publically available functions
    State reset() const;
    
    std::tuple<State, Reward, bool> step(const State& state, const Action& action) const;
    
    std::vector<Action> possible_actions(const State& board, const int& player) const;

    State fast_forward(State state, std::vector<Action> actions);

    // getters
    int get_size() const;
    
    int get_num_players() const;

    ID get_id(const State& state) const;
    
    Board get_board(const State& state) const;
    
    int get_player(const State& state) const;

    auto get_board_shape() const
        -> decltype(TicTacToe::board_shape);
    
    auto get_action_shape() const
        -> decltype(TicTacToe::action_shape);

    int get_state_channels() const;

    int get_action_channels() const;

    int get_board_size() const;

    State copy(const State& other) const;
    
    void print(const State& state) const;

    static std::string action_string(const Action& action); // for debugging
private:
    // private methods
    int check_win(const Board& board, const int& player) const;
    
    // Constructor private
    TicTacToe();
};

#endif /* tictactoe_hpp */
