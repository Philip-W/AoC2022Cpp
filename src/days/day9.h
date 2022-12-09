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

    std::vector<std::vector<std::bitset<200000>>> seenPart1 = { 
        {std::bitset<200000>(), std::bitset<200000>()},
        {std::bitset<200000>(), std::bitset<200000>()}
    };

    std::vector<std::vector<std::bitset<200000>>> seenPart2 = { 
        {std::bitset<200000>(), std::bitset<200000>()},
        {std::bitset<200000>(), std::bitset<200000>()}
    };

    char direction;
    int amount;

    for (int i = 0; i < lines.size(); i++){
        direction = lines[i][0];
        amount = lines[i][2] - '0';
        if (lines[i].size() == 4) amount = (amount* 10) + (lines[i][3] -'0');

        for (int j = 0; j < amount; j++){

            head.y += (direction == 'U') | -(direction == 'D');
            head.x += (direction == 'R') | -(direction == 'L'); 
    
            for (int k = 1; k < knots.size(); k++){

                Position* lead = knots[k-1];
                Position* follow = knots[k];
                //bool shouldContinue = (lead->y == follow->y ) | (lead->x == follow->x);

                follow->x += (lead->y == follow->y && (lead->x - follow->x) ==  2 );  // is 2 x units right
                follow->x -= (lead->y == follow->y && (lead->x - follow->x) == -2 );  // is 2 x units left
                follow->y += (lead->x == follow->x && (lead->y - follow->y) ==  2 );  // is 2 y units above
                follow->y -= (lead->x == follow->x && (lead->y - follow->y) == -2 );  // is 2 y units below

                //if (shouldContinue) continue;

                // else is diagonal 
                int manhatten_distance = std::abs(lead->x - follow->x) + std::abs(lead->y - follow->y);
                if (manhatten_distance >= 3){
                    if (lead->x > follow->x) follow->x++;
                    else follow->x--;
                    if (lead->y > follow->y) follow->y++;
                    else  follow->y--;
                }
            }

            count1 += !seenPart1[(knots[1]->y >=0)][(knots[1]->x > 0)][std::abs(knots[1]->y) * 1000 + std::abs(knots[1]->x)];
            count2 += !seenPart2[(knots[9]->y >=0)][(knots[9]->x > 0)][std::abs(knots[9]->y) * 1000 + std::abs(knots[9]->x)];
            seenPart1[(knots[1]->y >=0)][(knots[1]->x > 0)][std::abs(knots[1]->y) * 1000 + std::abs(knots[1]->x)] = true; 
            seenPart2[(knots[9]->y >=0)][(knots[9]->x > 0)][std::abs(knots[9]->y) * 1000 + std::abs(knots[9]->x)] = true; 
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
//  Best time so far 511.20us



