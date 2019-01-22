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

Action get_action(int turn, Player player)
{
    std::cout << "Turn " << turn << " (Player " << player << "): ";
    std::string str;
    getline(std::cin, str);
    
    char a = str[0];
    char b = str[2];
    
    int i = int(a - '0');
    int j = int(b - '0');
    
    return {i,j};
}

int main(int argc, const char * argv[]) {
    
    TicTacToe env = TicTacToe();
    
    State state;
    Reward reward;
    Done done = false;
    Player player = 0;
    
    
    state = env.reset();
    
    std::cout << "Begin" << std::endl;
    env.print(state);
    
    int turn = 1;
    while (!done) {
        Action action = get_action(turn, player);
        try {
            std::tie(state, reward, done) = env.step(state, action, player);
        } catch (std::exception& e) {
            std::cout << "Wrong action. Try again." << std::endl;
            continue;
        }
        
        player = (player + 1) % 2;
        turn++;
        
        if (done)
            std::cout << "Game finished. Reward: " << reward(0) << ',' << reward(1) << std::endl;
        env.print(state);
        
    }
    
    return 0;
}
