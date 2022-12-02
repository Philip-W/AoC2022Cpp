#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

//int part2PreComputeScores[] = {3, 1, 2, 1, 2, 3, 2, 3, 1};

void day2(std::vector<std::string> &lines, result &res) {
    
    int score = 0;
    int part2Score = 0;


    for (int i = 0; i < lines.size(); i++){
        char them = lines[i][0];
        char us = lines[i][2] - 23;

        int winValue = (them - us);
        int r = 0;
        if (winValue == 0) r = 3; // Draw
        if (winValue == 1 || winValue == -2) r = 0; //loss
        if (winValue == -1 || winValue == 2) r = 6; //win


        int choiceValue = (us - 'A' + 1);

        //winValue *= 3;
        //std::cout << them << " " << us << " " << winValue << " " << r << " "  << choiceValue << '\n';
        score += (r + choiceValue);
        int part2 = 0;

    
        if (us == 'A'){
            if (them == 'A') part2 += 3;
            if (them == 'B') part2 += 1;
            if (them == 'C') part2 += 2;
        } 
        if (us == 'B'){
            part2 += 3;
            if (them == 'A') part2 += 1;
            if (them == 'B') part2 += 2;
            if (them == 'C') part2 += 3;
        }
         if (us == 'C'){
            part2 += 6;
            if (them == 'A') part2 += 2;
            if (them == 'B') part2 += 3;
            if (them == 'C') part2 += 1;
        }

        part2Score += part2;
        

    }

    res.intResult1 = score;
    res.intResult2 = part2Score;
}
// A = 65 X = 88
// A A -> 0
// C C -> 0 
// B B -> 0


// C B -> 1 ( S v P - loss)
// B A -> 1  (P v R - loss)

// if 0 draw/3
// if 1  loss/0
// if (-1 ) win 6
// if (-2 ) loss
//if (2) win 

// A B -> -1 ( R v P win)
// A C -> -2 ( R v C loss)

// B C -> -1 (P v S - win )
// C A -> 2 (S v R) win 



// if 0 -> 3


// A for Rock, B for Paper, and C for Scissors.


////////////// Part 2
// X is lose, Y Draw, Z win

// A is lose, B is Draw, C is Win
// if you get A and they have:
//  A -> C (3)
//  B -> A (1)
//  C -> B (2)  
// So when lose your score will be 

// if you get C and they have
// A -> B (2)
// B -> C (3)
// C -> A (1)