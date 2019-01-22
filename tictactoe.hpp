//
//  tictactoe.hpp
//  tictactoe
//
//  Created by Semin Park on 23/01/2019.
//  Copyright © 2019 Semin Park. All rights reserved.
//

#ifndef tictactoe_hpp
#define tictactoe_hpp

#include <tuple>

#include "xtensor/xtensor.hpp"

using State = xt::xtensor<int, 3>;
using Reward = xt::xtensor<float, 1>;
using Done = bool;
using Action = std::tuple<int,int>;
using Player = int;

class TicTacToe {
    int size;
    
    
public:
    TicTacToe();
    
    State reset();
    
    std::tuple<State, Reward, Done> step(State state,
                                         const Action& action,
                                         const Player& player);
    
    std::vector<Action> possible_actions(const State& state);
    
    int check_win(const State& state, const Player& player);
    
    void print(const State& state);
    
};

#endif /* tictactoe_hpp */
