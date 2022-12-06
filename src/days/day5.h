#include <iostream>
#include <fstream>
#include <string>   
#include <vector>
#include <cmath>
#include <unordered_map>


void reverseStack(std::stack<char> &stack){
    std::vector<char> v;

    while (!stack.empty()){
        v.push_back(stack.top());
        stack.pop();
    }

    for (char c: v){
        stack.push(c);
    }
}

void day5(std::vector<std::string> &lines, result &res) {
    int numOfbuckets = (lines[0].size() + 1) / 4;

    std::vector<std::stack<char> > buckets(numOfbuckets);
    std::vector<std::stack<char> > buckets2(numOfbuckets);

    for (int i =0; i < numOfbuckets; i++){
        std::stack<char> s;
        buckets.push_back(s);
        buckets2.push_back(s);
    }

    int line = 0;
    while (lines[line][1] != '1'){
        int pos = 0;

        while (pos*4 < lines[0].size()){
            if (lines[line][1 + (pos * 4)] != ' '){
                // Found value
                buckets[pos].push(lines[line][1 + (pos * 4)]);
                buckets2[pos].push(lines[line][1 + (pos * 4)]);
            }
            pos++;
        }

        line++;
    }

    for (int i = 0; i < buckets.size(); i++){
        reverseStack(buckets[i]);
        reverseStack(buckets2[i]);
    }

    line+= 2;

    int move =0;
    int from = 0;
    int to = 0;

    for (line; line < lines.size(); line++){
        //std::cout << lines[line] << '\n'
        if (lines[line][7] == 'f'){
            // Number to move is single digit
            move = lines[line][5] - '0';
            from = lines[line][12] - '0' - 1;
            to = lines[line][17] - '0' -1;
        } else {
            move = (lines[line][5] - '0') * 10 + ((lines[line][6] - '0'));
            from = lines[line][13] - '0' - 1;
            to = lines[line][18] - '0'-1;
        }

        std::vector<char> part2;
        for (int i =0; i < move; i++){
            buckets[to].push(buckets[from].top());
            part2.push_back(buckets2[from].top());
            buckets[from].pop();
            buckets2[from].pop();
        }

        //std::reverse(part2.begin(), part2.end());
        for (int i =0; i < move; i++){
            buckets2[to].push(part2[i]);
        }
    }

    std::string res1;
    std::string res2;

    for (int i = 0; i < numOfbuckets; i++){
        res1 += buckets[i].top();
        res2 += buckets2[i].top();
    }

    res.stringResult1 = res1;
    res.stringResult2 = res2;


}



// First pass:
// Running day 5, 5000 times: 
//          Part 1 result: QNHWJVJZW
//          Part 2 result: BPCZJLFJW
//          Took time: 170.05μs 