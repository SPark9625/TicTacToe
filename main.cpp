//
//  main.cpp
//  tictactoe
//
//  Created by Semin Park on 23/01/2019.
//  Copyright © 2019 Semin Park. All rights reserved.
//

#include <iostream>
#include <string>

#include "tictactoe.hpp"

Action get_action(int turn, int player)
{
    char mark = 'O';
    if (player == 1)
        mark = 'X';
    std::cout << std::endl << "Turn " << turn << " (Player " << mark << "): ";
    std::string str;
    getline(std::cin, str);
    
    char a = str[0];
    char b = str[2];
    
    int i = int(a - '0');
    int j = int(b - '0');
    
    std::cout << "Action: " << i << ',' << j << std::endl;
    
    return {0,i,j};
}

int main(int argc, const char * argv[]) {
    
    TicTacToe& env = TicTacToe::get();
    
    State state;
    Reward reward = torch::from_blob((float[]){7,7}, {2});
    bool done = false;
    
    state = env.reset();
    int player = env.get_player(state);
    
    std::cout << "Begin" << std::endl;
    env.print(state);
    
    int turn = 1;
    while (!done) {
        Action action = get_action(turn, player);
        try {
            std::tie(state, reward, done) = env.step(state, action);
        } catch (std::exception& e) {
            std::cout << "Wrong action. Try again." << std::endl;
            std::cout << "Error: " << e.what() << std::endl;
            continue;
        }
        
        player = env.get_player(state);
        turn++;
        
        if (done)
            std::cout << "Game finished. Reward: " << reward[0].item<float>() << ',' << reward[1].item<float>() << std::endl;
        env.print(state);
        
    }
    
    return 0;
}
