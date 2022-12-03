#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>


int part1PreComputeScores[] = { 4, 8, 3,   // They rock
                                1, 5, 9,   // They Paper
                                7, 2, 6 }; // They Scissor

int p1[3][3] = {
    {4, 8, 3},
    {1, 5, 9},
    {7, 2, 6}
};

int p2[3][3] = {
    {3, 1, 2},
    {4, 5, 6}, 
    {8, 9, 7}
};
                                
int part2PreComputeScores[] = { 3, 1, 2,   // We lose
                                4, 5, 6,   // We Draw
                                8, 9, 7 }; // We win

void day2(std::vector<std::string> &lines, result &res) {
    res.intResult1 = 0;
    res.intResult2 = 0;

    int a, b;
    for (int i = 0; i < lines.size(); i++){
        a = (lines[i][0] - 'A');
        b = (lines[i][2] - 23 - 'A');

        // res.intResult1 += part1PreComputeScores[(lines[i][0] - 'A') * 3 + ( lines[i][2] - 23 - 'A')];
        // res.intResult2 += part2PreComputeScores[( lines[i][2] - 23 - 'A') * 3 + (lines[i][0] - 'A')];

        res.intResult1 += p1[a][b];
        res.intResult2 += p2[b][a];
    }
}

// Part 1 result: 15632
// Part 2 result: 14416