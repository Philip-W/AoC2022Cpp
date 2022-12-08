#include <iostream>
#include <fstream>
#include <string>   
#include <vector>
#include <cmath>
#include <algorithm>



void markSeen(int startX, int startY, int xChange, int yChange, std::vector<std::vector<bool>> &markers, std::vector<std::string> &map){
    int currentX =startX;
    int currentY =startY;
    int highestSoFar = -1;
    while (0 <= currentY && currentY <= map.size() - 1 && 0 <=currentX && currentX <= map[0].size() - 1){
        if (map[currentY][currentX] > highestSoFar){
            markers[currentY][currentX] = true;
            highestSoFar = map[currentY][currentX];
        }

        currentX += xChange;
        currentY += yChange;


//        if (highestSoFar)
    }
}

int part1(std::vector<std::string> &lines ){
    //bool seen[][]= new bool[lines.size()][lines[0].size()]{};
    std::vector<std::vector<bool>> seen;
    for (int i=0; i < lines.size(); i++){
        seen.push_back(std::vector<bool>(lines[0].size()));
    }
        // top to bootom sweep
    for (int i =0;i < lines[0].size(); i++){
        markSeen(i, 0, 0, 1, seen, lines);
    }

    // bottom to top sweep
    for (int i =0;i < lines[0].size(); i++){
        markSeen(i, lines.size() - 1, 0, -1, seen, lines);
    }

    // left to right downward sweep
    for (int i =0;i < lines[0].size(); i++){
        markSeen(0, i, 1, 0, seen, lines);
    }

    //  right to left downward sweep
    for (int i = 0;i < lines[0].size(); i++){
        markSeen(lines[0].size() -1, i, -1, 0, seen, lines);
    }

    int count = 0;
    for (int i = 0; i < lines.size(); i++){
        for (int j= 0; j < lines[0].size(); j++){
            count += seen[i][j];
        }
    }
    return count;
}



int scoreForTreeInDirection(int x, int y, int xChange, int yChange, std::vector<std::string> &map){
    int currentX =x + xChange;
    int currentY = y + yChange;
    int canSeeInDirection = 0;
    int thisHeight = map[y][x];

    while (0 <= currentY && currentY <= map.size() - 1 && 0 <=currentX && currentX <= map[0].size() - 1){
        if (map[currentY][currentX] >= thisHeight){
            canSeeInDirection++;
            break;
        }
        canSeeInDirection += 1;
        currentX += xChange;
        currentY += yChange;
    }


    return canSeeInDirection;   
}
void day8(std::vector<std::string> &lines, result &res) {
    //bool seen[][]= new bool[lines.size()][lines[0].size()]{};

    res.intResult1 = part1(lines);
    int highestScore = -1;

    for (int i =0; i < lines.size(); i++){
        for (int j =0; j < lines[0].size(); j++){
            // int upScore = scoreForTreeInDirection(j, i, 0, -1, lines);
            // int downScore = scoreForTreeInDirection(j, i, 0, 1, lines);
            // int leftScore = scoreForTreeInDirection(j, i, -1, 0, lines);
            // int rightScore = scoreForTreeInDirection(j, i, 1, 0, lines);

            highestScore = std::max(highestScore, scoreForTreeInDirection(j, i, 0, -1, lines) * 
                             scoreForTreeInDirection(j, i, 0, 1, lines) * 
                             scoreForTreeInDirection(j, i, -1, 0, lines) *  scoreForTreeInDirection(j, i, 1, 0, lines));

        }
    }

    res.intResult2 = highestScore; 
}


// Running day 8: 
//          Part 1 result: 1695
//          Part 2 result: 287040
//          Took time: 661.30μs 