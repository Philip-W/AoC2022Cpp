#include <iostream>
#include <fstream>
#include <string>   
#include <vector>
#include <cmath>


struct parts {
    int start1;
    int end1;
    int start2; 
    int end2;
};

parts parseBit(std::string &line) {
    int nums[4] = {0};
    int currentPosition = 0;
    int currentNum = 0;

    for (int i =0; i < line.size(); i++){
        if (line[i] == '-' || line[i] ==','){
            // Time to move on
            nums[currentPosition] = currentNum;
            currentPosition++;
            currentNum=0;
        }
        else {
            currentNum *=10;
            currentNum += (line[i] - '0');
        }
    }

    return parts {nums[0], nums[1], nums[2], currentNum};
}


bool contains(parts part){
    //return (part.start1 <= part.start2 && part.end2 <= part.end1 ) ||  (part.start2 <= part.start1 && part.end1 <= part.end2);
    if (part.start1 <= part.start2 && part.end2 <= part.end1 ){ 
        //std::cout << part.start1 << " " << part.end1 << " " << part.start2 << " " << part.end2 << '\n';
        return true; 
        }
    if (part.start2 <= part.start1 && part.end1 <= part.end2) {
        //std::cout << part.start1 << " " << part.end1 << " " << part.start2 << " " << part.end2 << '\n';
        return true;
    }
    return false;
}


// [1, 4] [ 3, 7] end1 > start2
// [2, 4] [1, 3] // end2 > start1
// 85 85 36 86|1 0
bool containsAny(parts part){
    //return (part.start1 <= part.start2 && part.start2 <= part.end1) || (part.start1 <= part.end2 && part.end2 <= part.end1 );
    
    if (part.start1 <= part.start2 && part.start2 <= part.end1) {
        //std::cout << part.start1 << " " << part.end1 << " " << part.start2 << " " << part.end2 << '\n';
        return true;
    }
    if (part.start1 <= part.end2 && part.end2 <= part.end1 ){
        //std::cout << part.start1 << " " << part.end1 << " " << part.start2 << " " << part.end2 << '\n';
        return true;
    }
    return false;
}

void day4(std::vector<std::string> &lines, result &res) {
    int part1 =0;
    int part2 = 0;

    for (int i = 0; i < lines.size(); i++){
        parts p = parseBit(lines[i]);
        bool p1 =  contains(p);
        bool p2 =  containsAny(p);

        //std::cout << p.start1 << " " << p.end1 << " " << p.start2 << " " << p.end2 << "|" << p1 << " " << p2<<  '\n';

        part1 += p1;
        part2 += p2 | p1;
    }

    res.intResult1 = part1;
    res.intResult2 = part2;
}

// First run:
// Running day 4: 
//          Part 1 result: 464
//          Part 2 result: 770
//          Took time: 23.86μs