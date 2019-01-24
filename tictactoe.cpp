//
//  tictactoe.cpp
//  tictactoe
//
//  Created by Semin Park on 23/01/2019.
//  Copyright © 2019 Semin Park. All rights reserved.
//

#include "tictactoe.hpp"

#include "xtensor/xview.hpp"
#include "xtensor/xio.hpp"

TicTacToe::TicTacToe() : size(3)
{
    // pass
}


State TicTacToe::reset() const
{
    State state = xt::zeros<int>({2,size,size});
    return state;
}

std::tuple<State, Reward, Done> TicTacToe::step(const State& state, const Action& action) const
{
    State next_state = state;
    
    int player, i, j;
    std::tie(player, i, j) = action;
    
    // throw if the given action is not valid
    auto actions = possible_actions(next_state, player);
    if (std::find(actions.begin(), actions.end(), action) == actions.end())
        throw std::exception();
    
    next_state(player, i, j) = 1;
    
    int status = check_win(next_state, player);
    
    Done done = false;
    if (status < 2)
        done = true;
    
    Reward reward = xt::zeros<int>({2});
    
    if (status == 1) {
        // Won
        if (player == 0)
            reward = Reward({1,-1});
        else
            reward = Reward({-1,1});
    }
    return std::tie(next_state, reward, done);
}

std::vector<Action> TicTacToe::possible_actions(const State& state, const int& player) const
{
    std::vector<Action> actions;
    auto matrix = xt::sum(state, {0});
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix(i,j) == 0)
                actions.push_back(std::tie(player, i, j));
        }
    }
    
    return actions;
}

int TicTacToe::check_win(const State& state, const int& player) const
{
    // 0: Draw, 1: Won, 2: Continue
    // No need for lost, as the current player can't lose
    
    int criteria = 3;
    
    xt::xtensor<int, 2> plane = xt::view(state, player);
    
    
    // horizontal
    if (xt::argwhere(xt::sum(plane, {1}) >= criteria).size() > 0)
        return 1;
    
    // vertical
    if (xt::argwhere(xt::sum(plane, {0}) >= criteria).size() > 0)
        return 1;
    
    // main diagonal
    if (plane(0,0) + plane(1,1) + plane(2,2) == criteria)
        return 1;
    
    // other diagonal
    if (plane(0,2) + plane(1,1) + plane(2,0) == criteria)
        return 1;
    
    // check if draw
    if (xt::argwhere(xt::sum(state, {0}) <= 0).size() == 0)
        return 0;
    
    return 2;
}


void TicTacToe::print(const State& state) const
{
    xt::xtensor<int, 2> board = xt::view(state, 0) + 2 * xt::view(state, 1);
    
    std::cout << "   ";
    for (char c : "ABC") std::cout << c << ' ';
    std::cout << std::endl;
    
    char mark;
    for (int i = 0; i < size; i++) {
        
        std::cout << std::setw(2) << i << ' ';
        for (int j = 0; j < size; j++) {
            
            mark = '.';
            if (board(i, j) == 1) {
                mark = 'O';
            } else if (board(i, j) == 2) {
                mark = 'X';
            }
            std::cout << mark << ' ';
            
        }
        std::cout << std::endl;
        
    }
}
