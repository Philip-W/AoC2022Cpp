#include <iostream>
#include <fstream>
#include <string>   
#include <vector>
#include <cmath>
#include <algorithm>




void day10(std::vector<std::string> &lines, result &res){

    int cycle =0;
    int X = 1;

    int ticksRemaining = 0;
    int line = 0;
    int addX = 0;

    int total =0;
    char row[40]{'.'};
    memset(row, '.', sizeof(row));

    int drawingPosition =0;
    std::string resultString = "\n  ";
    while (cycle <= 240){
        if (ticksRemaining == 0) X += addX;

        if (cycle == 20 || cycle == 60 || cycle == 100 || cycle == 140 || cycle == 180 || cycle == 220){
            total += (cycle * X);
        }

        if (drawingPosition == 40 ){

            drawingPosition = 0;
            for (int i =0; i < 40; i++){
                resultString +=  row[i];
            } 
            resultString += "\n  ";
            memset(row, '.', sizeof(row));
        }

        if (drawingPosition == (X -1) || drawingPosition == X || drawingPosition == X+1){
            row[drawingPosition] = '#'; 
        }

        if (ticksRemaining == 0){
            
            // Read next instruction
            if (lines[line][0] == 'a'){
                int action =0;
                if (lines[line][5] == '-'){
                    // Negative
                    action += lines[line][6] - '0';
                    if (lines[line].size() == 8) {
                        action *= 10; 
                        action += lines[line][7] - '0';
                    }
                    action *= -1;
                } else {
                    action += lines[line][5] - '0';
                    if (lines[line].size() == 7) {
                        action *= 10; 
                        action += lines[line][6] -'0';
                    }
                }
                //add x
                ticksRemaining = 2;
                addX = action;
            } else {
                ticksRemaining = 1;
                addX = 0;
            }
            line++;
        }
        ticksRemaining--;
        cycle++;
        drawingPosition++;
    }

    res.intResult1 = total;
    res.stringResult2 = resultString;
}



// ####..##..#.....##..#..#.#....###...##..
// #....#..#.#....#..#.#..#.#....#..#.#..#.
// ###..#..#.#....#....#..#.#....#..#.#....
// #....####.#....#.##.#..#.#....###..#.##.
// #....#..#.#....#..#.#..#.#....#....#..#.
// ####.#..#.####..###..##..####.#.....###.
// 18240
