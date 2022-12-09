#include <iostream>
#include <fstream>
#include <string>   
#include <vector>
#include <cmath>
#include <algorithm>


struct Position {
    int x = 0; 
    int y = 0;
};


void day9(std::vector<std::string> &lines, result &res){

    Position head;
    Position t1, t2, t3, t4, t5, t6, t7, t8, t9;
    std::vector<Position*> knots = {&head, &t1, &t2, &t3, &t4, &t5, &t6, &t7, &t8, &t9 };

    int count1 = 0;
    int count2 = 0;

    const int xOffset = 500;
    const int yOffset = 500;
    const int xSize = 500;
    const int ySize = 500;

    const size_t mapSize = (xSize + xOffset) * (ySize+ yOffset);

    std::bitset<mapSize> seen1;
    std::bitset<mapSize> seen2;

    char direction;
    int amount;

    for (int i = 0; i < lines.size(); i++){
        direction = lines[i][0];
        amount = lines[i][2] - '0';
        if (lines[i].size() == 4) amount = (amount* 10) + (lines[i][3] -'0');

        for (int j = 0; j < amount; j++){

            head.y += (direction == 'U') | -(direction == 'D');
            head.x += (direction == 'R') | -(direction == 'L'); 
    
            for (int k = 1; k < 10; k++){

                Position* lead = knots[k-1];
                Position* follow = knots[k];

                if (std::abs(lead->x - follow->x) > 1){
                    if (lead->x - follow->x > 0) follow->x++; else follow->x--;
                    if (lead->y != follow->y){
                        if (lead->y - follow->y > 0) follow->y++; else follow->y--;
                        continue;
                    }
                }

                if (std::abs(lead->y - follow->y) > 1){
                    if (lead->y - follow->y > 0) follow->y++; else follow->y--;
                    if (lead->x != follow->x){
                        if (lead->x - follow->x > 0) follow->x++; else follow->x--;
                    }
                }
            }
            
            count1 += !seen1[((knots[1]->y + yOffset) * ySize) + (knots[1]->x + xOffset)];
            count2 += !seen2[((knots[9]->y + yOffset) * ySize) + (knots[9]->x + xOffset)];

            seen1[((knots[1]->y + yOffset) * ySize) + (knots[1]->x + xOffset)] = true;
            seen2[((knots[9]->y + yOffset) * ySize) + (knots[9]->x + xOffset)] = true;
        }

    }

    res.intResult1 = count1;
    res.intResult2 = count2;
}

// Running day 9: 
//          Part 1 result: 5902
//          Part 2 result: 2445
//          Took time: 7.15ms 
//  
//  Best time so far 275us
//


