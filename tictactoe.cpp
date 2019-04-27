//
//  tictactoe.cpp
//  tictactoe
//
//  Created by Semin Park on 23/01/2019.
//  Copyright © 2019 Semin Park. All rights reserved.
//

#include "tictactoe.hpp"

TicTacToe::TicTacToe() { 
    // pass
}


State TicTacToe::reset() const
{
    Board board = torch::zeros({3,size,size}, torch::TensorOptions().dtype(torch::kUInt8));
    ID id {{-1,-1,-1}};
    return {id, board};
}

std::tuple<State, Reward, bool> TicTacToe::step(const State& state, const Action& action) const
{
    ID id = get_id(state);
    id.emplace_back(action);
    Board board = get_board(state).clone();
    
    State next_state{id, board};
    
    int player = get_player(state);
    int next_player = (player + 1) % 2;
    
    int _, i, j;
    std::tie(_, i, j) = action;
    
    // throw if the given action is not valid
    auto actions = possible_actions(state, player);
    if (std::find(actions.begin(), actions.end(), action) == actions.end())
        throw std::runtime_error("<TicTacToe::step> Action is not valid!");
    
    board[player][i][j] = 1;
    
    int status = check_win(board, player);
    bool finished = false;
    if (status != CONTINUE) {
        finished = true;
        next_player = 255;
    }
    board.slice(0,2,3) = next_player;
    
    Reward reward = torch::zeros({2});
    if (status == WIN) {
        if (player == 0) {
            float data[] = {1,-1};
            reward = torch::from_blob(data, {2});
        } else {
            float data[] = {-1,1};
            reward = torch::from_blob(data, {2});
        }
    }
    return {next_state, reward.clone(), finished};
}

std::vector<Action> TicTacToe::possible_actions(const State& state, const int& player) const
{
    const Board& board = get_board(state);
    std::vector<Action> actions;
    const auto matrix = board.slice(0,0,2).sum(0);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j].item<int>() == 0)
                actions.emplace_back(0, i, j);
        }
    }
    return actions;
}

int TicTacToe::check_win(const Board& board, const int& player) const
{
    // No LOSE status, because the current player can't lose.
    
    int criteria = 3;
    
    const auto& plane = board.slice(0, player, player + 1).squeeze();
    
    if ((plane.sum(1) >= criteria).sum().item<int>() > 0)
        return WIN;
    
    if ((plane.sum(0) >= criteria).sum().item<int>() > 0)
        return WIN;
    
    if (plane.trace().item<int>() == criteria)
        return WIN;
    
    if (plane.flip({1}).trace().item<int>() == criteria)
        return WIN;
    
    if ((board.slice(0,0,2).sum(0) <= 0).sum().item<int>() == 0)
        return DRAW;
    
    return CONTINUE;
}

State TicTacToe::fast_forward(State state, std::vector<Action> actions)
{
    Reward r; bool d;
    for (auto& action : actions) {
        std::tie(state, r, d) = step(state, action);
    }
    return state;
}

std::string TicTacToe::action_string(const Action& action)
{
    int _,i,j;
    std::tie(_,i,j) = action;
    return "(" + std::to_string(i) + "," + std::to_string(j) + ")";
}

int TicTacToe::get_num_players() const
{
    return num_players;
}

ID TicTacToe::get_id(const State& state) const
{
    return std::get<0>(state);
}

Board TicTacToe::get_board(const State& state) const
{
    return std::get<1>(state);
}

int TicTacToe::get_player(const State& state) const
{
    return std::get<1>(state)[2][0][0].item<int>();
}

auto TicTacToe::get_board_shape() const
    -> decltype(TicTacToe::board_shape)
{
    return board_shape;
}

auto TicTacToe::get_action_shape() const
    -> decltype(action_shape)
{
    return action_shape;
}

int TicTacToe::get_state_channels() const
{
    return c_in;
}

int TicTacToe::get_action_channels() const
{
    return c_out;
}

int TicTacToe::get_board_size() const
{
    return size;
}

State TicTacToe::copy(const State& other) const
{
    ID id = get_id(other);
    Board board = get_board(other).clone();
    return {id, board}; 
}

void TicTacToe::print(const State& state) const
{
    const auto& board_ = get_board(state);
    auto board = board_.slice(0,0,1) + 2 * board_.slice(0,1,2);
    
    std::cout << "   ";
    for (char c : "ABC") std::cout << c << ' ';
    std::cout << std::endl;
    
    char mark;
    for (int i = 0; i < size; i++) {
        
        std::cout << std::setw(2) << i << ' ';
        for (int j = 0; j < size; j++) {
            
            mark = '.';
            if (board[0][i][j].item<int>() == 1) {
                mark = 'O';
            } else if (board[0][i][j].item<int>() == 2) {
                mark = 'X';
            }
            std::cout << mark << ' ';
            
        }
        std::cout << std::endl;
        
    }
}