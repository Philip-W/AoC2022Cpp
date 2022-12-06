#include <iostream>
#include <fstream>
#include <string>   
#include <vector>
#include <cmath>
#include <algorithm>


inline int findWindowStart(std::string &s, int size){
    uint32_t seenNum = 0;

    int i = 0;
    int j = 0;
    while(j < i + size){
        if ((seenNum & (1 << s[j] - 'a'))){
            i++;
            j = i;
            seenNum = 0;
        }
        seenNum |= (1 << s[j] - 'a'); 
        j++;
    }

    return (i + size);
}

void day6(std::vector<std::string> &lines, result &res) {
    res.intResult1 = findWindowStart(lines[0], 4);
    res.intResult2 = findWindowStart(lines[0], 14);
}

// Running day 6: 
//          Part 1 result: 1542
//          Part 2 result: 3153
//          Took time: 126.48μs
// Best so far: 28.34μs