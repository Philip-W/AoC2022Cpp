#include <iostream>
#include <fstream>
#include <string>   
#include <vector>
#include <cmath>
#include <algorithm>



void markSeen(int startX, int startY, int xChange, int yChange, std::bitset<100*100> &markers, std::vector<std::string> &map){
    int currentX =startX;
    int currentY =startY;
    int highestSoFar = -1;
    while (0 <= currentY && currentY <= map.size() - 1 && 0 <=currentX && currentX <= map[0].size() - 1){
        if (map[currentY][currentX] > highestSoFar){
            markers[currentX * map.size() + currentY] = true;
            highestSoFar = map[currentY][currentX];
        }

        currentX += xChange;
        currentY += yChange;


        if (highestSoFar == '9') return;
    }
}

int part1(std::vector<std::string> &lines ){
    std::bitset<100*100> seen;

    // Look down top row
    for (int i =0;i < lines[0].size(); i++){
        int highestSoFar = -1;
        for (int j =0; j < lines.size(); j++){
            if (lines[j][i] > highestSoFar){
                seen[i * lines.size() + j] = true;
                highestSoFar = lines[j][i];
            }
            if (highestSoFar == '9') break;
        }
    }

    // Look up from the bottom rows
    for (int i =0;i < lines[0].size(); i++){
        int highestSoFar = -1;
        for (int j =lines.size() -1; j >=0; j--){
            if (lines[j][i] > highestSoFar){
                seen[i * lines.size() + j] = true;
                highestSoFar = lines[j][i];
            }
            if (highestSoFar == '9') break;
        }
    }

    // Look at the left side
    for (int i =0;i < lines[0].size(); i++){
        int highestSoFar = -1;
        for (int j = 0; j < lines[0].size(); j++){
            if (lines[i][j] > highestSoFar){
                seen[j * lines.size() + i] = true;
                highestSoFar = lines[i][j];
            }
            if (highestSoFar == '9') break;
        }        
    }

    //  Look at the right side
    for (int i = 0;i < lines[0].size(); i++){
        int highestSoFar = -1;
        for (int j = lines[0].size() - 1; j >=0; j--){
            if (lines[i][j] > highestSoFar){
                seen[j * lines.size() + i] = true;
                highestSoFar = lines[i][j];
            }
            if (highestSoFar == '9') break;
        }     

    }
    return seen.count();
}


//inline int part2(char (&lines)[100][100], int rows, int cols) {
inline int part2(std::vector<std::string> &lines, int rows, int cols) {
    int highestScore = -1;

    for (int i = 1; i < rows -1; i++){
        for (int j =1; j < cols -1; j++){

            int base = lines[i][j];
            int a = 0;
            int currentX = j + 1;
            int currentY = i + 1;

            // Go right
            while (currentX <= cols - 1){
                if (lines[i][currentX] < base) a++;
                else { a++; break;}
                currentX++;
            }

            int b = 0;
            currentX = j - 1;
            // Go left
            while (currentX >= 0) {
                if (lines[i][currentX] < base) b++;
                else { b++; break; }
                currentX--;
            }

            if (a * b * ((i -1 ) * (cols - i)) < highestScore){continue;}

            // Go down
            int c =0;            
            while(currentY <= rows- 1){
                if (lines[currentY][j] < base) c++;
                else { c++; break;}
                currentY++;
            }

            if (a * b * (c*i - c ) < highestScore){continue;}
            
            int d = 0;
            currentY = i - 1;
            // Go up
            while(currentY >= 0){
                if (lines[currentY][j] < base) d++;
                else { d++; break;}
                currentY--;
            }

            highestScore = std::max(highestScore, a*b*c*d);
        }
    }

    return highestScore; 
}

void day8(std::vector<std::string> &lines, result &res) {
    //bool seen[][]= new bool[lines.size()][lines[0].size()]{};

    //std::cout << sizeof(intmax_t) << '\n';

    //__int128 x = 1232134;
    //std::cout << sizeof(x) << '\n';

    res.intResult1 = part1(lines);
    res.intResult2 = part2(lines, lines.size(), lines[0].size());
}


// Running day 8: 
//          Part 1 result: 1695
//          Part 2 result: 287040
//          Took time: 661.30μs 