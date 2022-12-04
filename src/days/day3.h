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


int isPowerOfTwo(long n){ return n && (!(n & (n - 1))); }

int findPosition(long n){
    // TODO: why on earth does adding this in save 3-4us, it literally never gets hit, adding in an 
    // extra calculation SAVES TIME WHAT WHY
    if (!isPowerOfTwo(n)){
        std::cout << "OVER: " << n << '\n';
        return -1;
    }
 
    long i = 1, pos = 1;

    while (!(i & n)) {
        i = i << 1;
        ++pos;
    }
 
    return pos;
}

long handleNumber(std::string &line, int &part1Sol){    

    long firstHalf = 0;
    bool search = 1;
    // first half
    for (int j = 0; j < line.size() / 2; j++){ 
        firstHalf |= (1L << (line[j] - 'A'));
    }


    long secondHalf = 0;
    // second half
    for (int j = line.size() / 2; j < line.size(); j++){ secondHalf |= (1L << (line[j] - 'A')); }


    int shared = firstHalf & secondHalf;
    //  std::cout << "bruh" << '\n';
    int location = findPosition(shared);

    //std::cout<< "hello" << "\n";
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

        //long shared = line1 & line2 & line3;


        // char num =  findPosition(shared) + 'A';


        // int score =  num  - 'a';
        // if (score < 0) score = num - 'A' + 26;
        // part2 += score;
    }


    // For each day you need the score for the day1 part, and the final number 
    // for (int i = 0; i < lines.size(); i+=3){
    //     int seen[200] = {0};
        
    //     int seen1[200] = {0};
    //     int seen2[200] = {0};

    //     bool search = 1;
    //     // First line first half
    //     for (int j = 0; j < lines[i].size() / 2; j++){ 
    //         seen[lines[i][j]] = 1;   
    //         seen1[lines[i][j]] = 1;
    //     }

    //     // First line second half
    //     for (int j = lines[i].size() / 2; j < lines[i].size(); j++){ 
    //         if (seen[lines[i][j]] == 1 && search) { 
    //             int score =  lines[i][j] - 'a' + 1;
    //             if (score < 0) score = lines[i][j] - 'A' + 27;
    //             part1 += score;
    //             search = !search;
    //         };

    //         seen1[lines[i][j]] = 1;
    //     }


    //     memset(seen, 0, sizeof(seen));
    //     search = 1;
    //     // second  line first half
    //     // second line first half
    //     for (int j = 0; j < lines[i + 1].size() / 2; j++){ 
    //         seen[lines[i+1][j]] = 1;   
    //         seen2[lines[i+1][j]] = 1;
    //     }

    //     // second line second half
    //     for (int j = lines[i + 1].size() / 2; j < lines[i+1].size(); j++){ 
    //         if (seen[lines[i+1][j]] == 1 && search) { 
    //             int score =  lines[i+1][j] - 'a' + 1;
    //             if (score < 0) score = lines[i+1][j] - 'A' + 27;
    //             part1 += score;
    //             search = !search;
    //         };

    //         seen2[lines[i+1][j]] = 1;
    //     }


    //     memset(seen, 0, sizeof(seen));
    //     bool find = true;
    //     // Third line first half
    //     for (int j = 0; j < lines[i+2].size() / 2; j++){ 
    //         seen[lines[i+2][j]] = 1;   

    //         if (seen1[lines[i + 2][j]] == 1  && seen2[lines[i + 2][j]] == 1 && find){
    //             //std::cout << lines[i + 2][j] << '\n';
    //             int score =  lines[i+2][j] - 'a' + 1;
    //             if (score < 0) score = lines[i+2][j] - 'A' + 27;;
    //             part2 += score;
    //             find = false;

    //         }
    //     }

    //     search = 1;
    //     // Third line second half
    //     for (int j = lines[i+2].size() / 2; j < lines[i+2].size(); j++){ 
    //         if (seen[lines[i+2][j]] == 1 && search) { 
    //             int score =  lines[i+2][j] - 'a' + 1;
    //             if (score < 0) score = lines[i+2][j] - 'A' + 27;
    //             part1 += score;
    //             search = !search;
    //         };

    //         if (seen1[lines[i + 2][j]] == 1  && seen2[lines[i + 2][j]] == 1 && find ){
    //             //std::cout << lines[i + 2][j] << '\n';
    //             int score =  lines[i+2][j] - 'a' + 1;
    //             if (score < 0) score = lines[i+2][j] - 'A' + 27;;
    //             part2 += score;
    //             find = false;
    //         }
    //     }
    // }

    res.intResult1 = part1;
    res.intResult2 = part2; 
}

// Part 1 result: 7980
// Part 2 result: 2881
// First implementation - Took time: 29.62μs
