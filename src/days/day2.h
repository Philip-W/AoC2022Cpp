#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>


int part1PreComputeScores[] = { 4, 8, 3,   // They rock
                                1, 5, 9,   // They Paper
                                7, 2, 6 }; // They Scissor
                                
int part2PreComputeScores[] = { 3, 1, 2,   // We lose
                                4, 5, 6,   // We Draw
                                8, 9, 7 }; // We win

void day2(std::vector<std::string> &lines, result &res) {
    res.intResult1 = 0;
    res.intResult2 = 0;
    for (int i = 0; i < lines.size(); i++){
        res.intResult1  += part1PreComputeScores[(lines[i][0] - 'A') * 3 + ( lines[i][2] - 23 - 'A')];
        res.intResult2 += part2PreComputeScores[( lines[i][2] - 23 - 'A') * 3 + (lines[i][0] - 'A')];
    }
}

// Part 1 result: 15632
// Part 2 result: 14416