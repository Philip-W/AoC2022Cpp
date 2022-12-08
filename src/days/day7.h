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
    
    ~Directory(){
        for (Directory* d : dirs){
            delete d;
        }
    }

    int getSize() {
        int total = this->size;
        for (Directory* dir: dirs){
            total += dir->getSize();
        }

        return total;
    }

    Directory* moveDir(std::string_view s) {
        for (Directory* dir: dirs){
            if (s.compare(dir->name) == 0){ 
                return dir; 
            }
        }
        std::cout << "EROR DIR NOT FOUND"<<  '\n';
        return nullptr;
    }

    void addDirectory(std::string_view &name){
        Directory* d = new Directory();
        d->name = name.substr(4);
        d->parent = this;
        dirs.push_back(d);
    }

    void addFile(int size){ 
        this->size += size;
    }

    int dirSizesBelow100k(){
        int res = 0;
        for (auto d : dirs){
            res += d->dirSizesBelow100k();
        }

        if (this->getSize() < 100000) res += this->getSize();
        return res;
    }

    int getBestDeletionTarget(int target){
        if (dirs.empty()) return this->getSize();

        int res = this->getSize();

        for (auto d : dirs){
            int nextbest = d->getBestDeletionTarget(target);
            bool isUseful =  target < nextbest;
            if (isUseful && (nextbest < res)){ 
                res = nextbest;
            }
        }

        return res;
    }

    std::vector<int> getSizes(){
        std::vector<int>  res;
        res.push_back(this->getSize());
        for (auto d : dirs){    
            std::vector<int> children = (d->getSizes());
            res.insert(res.end(), children.begin(), children.end());
        }
        return res;
    }

};


void day7(std::vector<std::string> &lines, result &res) {
    Directory* base = new Directory();
    base->name = "/";
    Directory* current = base;

    for(int i = 1; i < lines.size(); i++){
        std::string_view line = std::string_view(lines[i]);

        // is command
        if (line[0] == '$' && line[5] == '.'){ current = current->parent; continue;}
        if (line[0] == '$' && line[2] == 'l') continue;
        if (line[0] == '$') {current = current->moveDir(line.substr(5)); continue; }

        if (line[0] == 'd'){ 
            //std::cout << "is dir " << line.substr(4) <<  '\n';
            current->addDirectory(line);
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
            current->addFile(space);
        }
    }

    res.intResult1 = base->dirSizesBelow100k();
    int target =  30000000 - (70000000 - base->getSize());
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