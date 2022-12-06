#include <iostream>
#include <fstream>
#include <string>   
#include <vector>
#include <cmath>
#include <algorithm>



inline int bitsSet(uint32_t i) {
     i = i - ((i >> 1) & 0x55555555);        
     i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
     i = (i + (i >> 4)) & 0x0F0F0F0F;
     return (i * 0x01010101) >> 24;
}

int findWindowStart(std::string &s, int size){
    uint32_t seenNum = 0;
    for (int i = 0; i < s.size() - size; i++){
        for (int j = i; j < i + size; j++){ seenNum |= (1 << s[j]- 'a'); }

        if (bitsSet(seenNum) == size)return  (i + size);

        seenNum = 0;
    }
}

void day6(std::vector<std::string> &lines, result &res) {

    res.intResult1 = findWindowStart(lines[0], 4);
    res.intResult2 = findWindowStart(lines[0], 14);
}

// Running day 6: 
//          Part 1 result: 1542
//          Part 2 result: 3153
//          Took time: 126.48μs