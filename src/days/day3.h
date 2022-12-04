#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>


const int scores[] = {
    27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
    51, 52, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    20, 21, 22, 23, 24, 25, 26, 0, 0, 0, 0, 0, 0,
};


inline long handleNumber(std::string &line, int &part1Sol){    

    long firstHalf = 0;
    bool search = 1;
    // first half
    for (int j = 0; j < line.size() / 2; j++){ 
        firstHalf |= (1L << (line[j] - 'A'));
    }
    long secondHalf = 0;
    // second half
    
    for (int j = line.size() / 2; j < line.size(); j++){ 
        //std::cout << (line[j]) << '\n';
        secondHalf |= (1L << (line[j] - 'A')); 
    }

    int location = __builtin_ctzl(firstHalf & secondHalf);

    part1Sol += scores[location];
    return (firstHalf | secondHalf);
}

void day3(std::vector<std::string> &lines, result &res) {
    res.intResult1 = 0;
    res.intResult2 = 0;

    int total2 = 0;
    int part1 = 0;
    int part2 = 0;

    long i = 0;
    for (int i = 0; i < lines.size(); i+=3){
        long line1 = handleNumber(lines[i], part1);
        long line2 = handleNumber(lines[i+1], part1);
        long line3 = handleNumber(lines[i+2], part1);

        long shared = line1 & line2 & line3;
        int location = __builtin_ctzl(shared);

        part2 += scores[location];
    }

    res.intResult1 = part1;
    res.intResult2 = part2; 
}

// Part 1 result: 7980
// Part 2 result: 2881
// First implementation - Took time: 29.62μs
