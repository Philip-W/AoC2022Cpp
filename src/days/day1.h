#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>




// TODO: handle negatives
inline int parseInt(std::string &s) {
    int result = 0;
    for (char const &c: s) {
        result *= 10;
        result += c - '0';
    }
    return result;
}

void day1(std::vector<std::string> &lines, result &res) {

    int parsed[lines.size()];

    int p1 = 1;
    int p2 = 1; 
    int current;

    // __builtin_prefetch(&p1, 1, 3);
    // __builtin_prefetch(&p2, 1, 3);
    // __builtin_prefetch(&current, 1, 3);

    for (int i = 0; i < lines.size(); i++){
        //std::cout << i << std::endl;
        current = parseInt(lines[i]);
        parsed[i] = current;

        p1 += ((unsigned int) (1 - i) >> 31) & ( (unsigned int) (parsed[i - 1] - current) >> 31);
        p2 += ((unsigned int) (3 - i) >> 31) & ( (unsigned int) (parsed[i - 3] - current) >> 31);
        // if (i >= 1 && current > parsed[i -1]) p1++;
        // if (i >= 3 && current > parsed[i - 3]) p2++;
    }

    res.intResult1 = p1;
    res.intResult2 = p2;
}