#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>


void day2(std::vector<std::string> &lines, result &res) {
    
    int x = 0;
    int y = 0;

    int aim = 0;
    int part2x = 0;
    long depth = 0;

    for (int i = 0; i < lines.size(); i++){

        x += (lines[i].back() - '0') & ~(-(lines[i][0] != 'f')); 
        depth += (aim * (lines[i].back() - '0')) & ~(-(lines[i][0] != 'f'));
        part2x += (lines[i].back() - '0') & ~(-(lines[i][0] != 'f'));

        y += (lines[i].back() - '0') & ~(-(lines[i][0] != 'd')); 
        aim += (lines[i].back() - '0')  & ~(-(lines[i][0] != 'd')); 

        y-= (lines[i].back() - '0') & ~(-(lines[i][0] != 'u')); 
        aim -= (lines[i].back() - '0') & ~(-(lines[i][0] != 'u')); 
    }
    res.intResult1 = x * y;
    res.longResult2 = depth * part2x;
}


void day2Bytes(std::string s, result &res){
    int x = 0;
    int y = 0;

    int aim = 0;
    int part2x = 0;
    long depth = 0;

    int move;

    for (int i=0; i < s.size();i ){
        move = i + ((8 & -(s[i] == 'f')) | (3 & -(s[i] == 'u')) | (5 & -(s[i] == 'd')));

        x += (s[move] - '0') & -(s[i] == 'f');
        depth += (aim * (s[move] - '0')) & -(s[i] == 'f');
        part2x += (s[move] - '0') & -(s[i] == 'f');

        y += (s[move] - '0') & -(s[i] == 'd'); 
        aim += (s[move] - '0')  & -(s[i] == 'd');

        y-= (s[move] - '0') & -(s[i] == 'u');
        aim -= (s[move] - '0') & -(s[i] == 'u');
        i = move + 2;
    }

    res.intResult1 = x * y;
    res.longResult2 = depth * part2x;
}