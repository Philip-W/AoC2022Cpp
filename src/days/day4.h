#include <iostream>
#include <fstream>
#include <string>   
#include <vector>
#include <cmath>


void day4(std::vector<std::string> &lines, result &res) {
    res.intResult1 = 0;
    res.intResult2 = 0;

    int nums[4] = {0};
    int currentPosition = 0;
    int currentNum = 0;

    for (int i = 0; i < lines.size(); i++){
        currentPosition = 0;
        currentNum = 0;

        for (int j =0; j < lines[i].size(); j++){
            if ( lines[i][j] == '-' ||  lines[i][j] ==','){
                // Time to move on
                nums[currentPosition] = currentNum;
                currentPosition++;
                currentNum=0;
            }
            else {
                currentNum *=10;
                currentNum += ( lines[i][j] - '0');
            }

        }
        res.intResult1 += (nums[0] <= nums[2] && currentNum <= nums[1] ) |  (nums[2] <= nums[0] && nums[1] <= currentNum);
        res.intResult2 += (nums[0] <= nums[2] && currentNum <= nums[1] ) |  (nums[2] <= nums[0] && nums[1] <= currentNum) | 
                 (nums[0] <= nums[2] && nums[2] <= nums[1]) | (nums[0] <= currentNum && currentNum <= nums[1] );
    }

}

// First run:
// Running day 4: 
//          Part 1 result: 464
//          Part 2 result: 770
//          Took time: 23.86μs