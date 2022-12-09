#include <iostream>
#include <fstream>
#include <string>   
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <list>
#include <unordered_set>

#include "../Utils/numbers.h"


struct Directory {
    std::string_view name;
    std::vector<Directory*> dirs;
    int size;
    Directory *parent; 
    int totalSize;

    ~Directory(){
        for (int i =0; i < dirs.size(); i++){
            delete dirs[i];
        }
    }

    int getSize() {
        int total = this->size;
        for (int i =0; i < dirs.size(); i++){
            total += dirs[i]->getSize();
        }
        this->totalSize = total;
        return total;
    }

    inline Directory* moveDir(std::string_view &s) {
        auto goal = s.substr(5);
        //for (Directory* dir: dirs){
        for (int i =0; i < dirs.size(); i++){

            if (goal.compare(dirs[i]->name) == 0){ 
                return dirs[i]; 
            }
        }
        std::cout << "EROR DIR NOT FOUND"<<  '\n';
        return nullptr;
    }

    inline void addDirectory(std::string_view &name){
        Directory* d = new Directory();
        d->name = name.substr(4);
        d->parent = this;
        dirs.push_back(d);
    }

    void addFile(int size){ 
        this->size += size;
        //Directory* p = this->parent;
        //while (p != nullptr) { p->totalSize += size; p = p->parent; }
    }

    int dirSizesBelow100k(){
        int res = this->totalSize & -(this->totalSize < 100000);
        for (int i =0; i < dirs.size(); i++){
            res += dirs[i]->dirSizesBelow100k();
        }

        //if (this->totalSize < 100000) res += this->totalSize;
        return res;
    }

    int getBestDeletionTarget(int target){
        int res = this->totalSize;

        for (int i =0; i < dirs.size(); i++){
            int nextbest = dirs[i]->getBestDeletionTarget(target);
            if (target < nextbest && (nextbest < res)){ 
                res = nextbest;
            }
        }

        return res;
    }
};


void day7(std::vector<std::string> &lines, result &res) {
    Directory* base = new Directory();
    base->name = "/";
    Directory* current = base;

    std::string_view line;
    for(int i = 1; i < lines.size(); i++){
        line = std::string_view(lines[i]);

        // is command
        if (line[0] == '$') { 
            if (line[5] == '.'){ current = current->parent; continue;}
            if (line[2] == 'l') continue;

            for (int i =0; i < current->dirs.size(); i++){
                if (line.substr(5).compare(current->dirs[i]->name) == 0){ 
                    current = current->dirs[i]; 
                    break;
                }
            }

            continue;
        }

        if (line[0] == 'd'){ 
            //std::cout << "is dir " << line.substr(4) <<  '\n';
            //current->addDirectory(line);

            Directory* d = new Directory();
            d->name = line.substr(4);
            d->parent = current;
            current->dirs.push_back(d);
            continue;
        }  
        else {
            // must be a file
            int space = 0;
            int j =0;
            while (line[j] != ' '){
                space *= 10;
                space += line[j] - '0';
                j++;
            }
            current->size += space;
        }
    }

    base->getSize();
    res.intResult1 = base->dirSizesBelow100k();
    int target =  30000000 - (70000000 - base->totalSize);
    res.intResult2 = base->getBestDeletionTarget(target);

    delete base;
}


// void day7(std::vector<std::string> &lines, result &res) {
//     std::vector<std::string> currentPaths = {"/"};
//     std::unordered_map<std::string_view, int> dirSizes;

//     for (int i =1; i < lines.size(); i++){
//         std::string_view line = lines[i];
//         //std::cout << line << '\n';
//         if (line[0] == '$'){
//             // is command
//             if (line.compare("$ cd ..") == 0){ 
//                 currentPaths.pop_back();
//                 continue;
//             }

//             if (line.rfind("$ ls", 0) == 0) continue;
//             else {
//                 // is Cd
//                 currentPaths.push_back(currentPaths.back() + std::string(line.substr(5)));
//             }
//             continue;
//         }
//         if (line.rfind("dir ", 0) == 0){ 
//             //std::cout << "is dir " << line.substr(4) <<  '\n';
//             dirSizes[line.substr(4)] = 0;
//             continue;
//         }  
//         else {
//             // must be a file
//             int space = line.find(' ');
//             int size = parseIntUntil(line, space);
//             for (int j =0; j< currentPaths.size(); j++){
//                 dirSizes[currentPaths[j]] += size;
//             }
//         }
//     }

//     res.intResult1 = 0;
//     res.intResult2 = 100000000;
//     int target =  30000000 - (70000000 - dirSizes["/"]);
//     std::cout << target << "\n";
//     for (auto kv : dirSizes){
//         if (kv.second < 100000) res.intResult1 += kv.second;
//         if (kv.second > target && kv.second < res.intResult2) res.intResult2 = kv.second;
//     }
// }

// Running day 7: 
//          Part 1 result: 1582412
//          Part 2 result: 3696336
//          Took time: 314.88μs
// Best time using tree: 116us