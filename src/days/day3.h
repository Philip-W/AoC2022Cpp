#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>


long handleNumber(std::string &line, int &part1Sol){    
    long seen = 0;


    bool search = 1;
    // First line first half
    for (int j = 0; j < line.size() / 2; j++){ 
        seen |= 1 << line[j] - 'A';
        // seen1[lines[i][j]] = 1;
    }

    long result = 1;
    // First line second half
    for (int j = line.size() / 2; j < line.size(); j++){ 
        bool bitSet =  search & seen & ( 1 << (line[j] - 'A'));
        if (bitSet) { 
            int score =  line[j] - 'a' + 1;
            if (score < 0) score = line[j] - 'A' + 27;
            part1Sol += score;
            search = !search;
        };

        result |= 1 << line[j] - 'A';
    }


}

void day3(std::vector<std::string> &lines, result &res) {
    res.intResult1 = 0;
    res.intResult2 = 0;

    int total2 = 0;
    int part1 = 0;
    int part2 = 0;

    // For each day you need the score for the day1 part, and the final number 
    for (int i = 0; i < lines.size(); i+=3){
        int seen[200] = {0};
        
        int seen1[200] = {0};
        int seen2[200] = {0};

        bool search = 1;
        // First line first half
        for (int j = 0; j < lines[i].size() / 2; j++){ 
            seen[lines[i][j]] = 1;   
            seen1[lines[i][j]] = 1;
        }

        // First line second half
        for (int j = lines[i].size() / 2; j < lines[i].size(); j++){ 
            if (seen[lines[i][j]] == 1 && search) { 
                int score =  lines[i][j] - 'a' + 1;
                if (score < 0) score = lines[i][j] - 'A' + 27;
                part1 += score;
                search = !search;
            };

            seen1[lines[i][j]] = 1;
        }


        memset(seen, 0, sizeof(seen));
        search = 1;
        // second  line first half
        // second line first half
        for (int j = 0; j < lines[i + 1].size() / 2; j++){ 
            seen[lines[i+1][j]] = 1;   
            seen2[lines[i+1][j]] = 1;
        }

        // second line second half
        for (int j = lines[i + 1].size() / 2; j < lines[i+1].size(); j++){ 
            if (seen[lines[i+1][j]] == 1 && search) { 
                int score =  lines[i+1][j] - 'a' + 1;
                if (score < 0) score = lines[i+1][j] - 'A' + 27;
                part1 += score;
                search = !search;
            };

            seen2[lines[i+1][j]] = 1;
        }


        memset(seen, 0, sizeof(seen));
        bool find = true;
        // Third line first half
        for (int j = 0; j < lines[i+2].size() / 2; j++){ 
            seen[lines[i+2][j]] = 1;   

            if (seen1[lines[i + 2][j]] == 1  && seen2[lines[i + 2][j]] == 1 && find){
                //std::cout << lines[i + 2][j] << '\n';
                int score =  lines[i+2][j] - 'a' + 1;
                if (score < 0) score = lines[i+2][j] - 'A' + 27;;
                part2 += score;
                find = false;

            }
        }

        search = 1;
        // Third line second half
        for (int j = lines[i+2].size() / 2; j < lines[i+2].size(); j++){ 
            if (seen[lines[i+2][j]] == 1 && search) { 
                int score =  lines[i+2][j] - 'a' + 1;
                if (score < 0) score = lines[i+2][j] - 'A' + 27;
                part1 += score;
                search = !search;
            };

            if (seen1[lines[i + 2][j]] == 1  && seen2[lines[i + 2][j]] == 1 && find ){
                //std::cout << lines[i + 2][j] << '\n';
                int score =  lines[i+2][j] - 'a' + 1;
                if (score < 0) score = lines[i+2][j] - 'A' + 27;;
                part2 += score;
                find = false;
            }
        }
    }

    res.intResult1 = part1;
    res.intResult2 = part2; 
}

// Part 1 result: 7980
// Part 2 result: 2881
// First implementation - Took time: 29.62μs
