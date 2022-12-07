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
    std::string name;
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

    Directory* moveDir(std::string s) {
        for (Directory* dir: dirs){
            if (s.compare(dir->name) == 0){ 
                return dir; 
            }
        }
        std::cout << "EROR DIR NOT FOUND"<<  '\n';
        return nullptr;
    }

    void addDirectory(std::string &name){
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
        std::string line = lines[i];
        //std::cout << line << '\n';
        if (line[0] == '$'){
            // is command
            if (line.compare("$ cd ..") == 0){ current = current->parent; continue;}

            if (line.rfind("$ ls", 0) == 0) continue;
            else {
                current = current->moveDir(line.substr(5)); 
            }
            continue;
        }
        if (line.rfind("dir ", 0) == 0){ 
            //std::cout << "is dir " << line.substr(4) <<  '\n';
            current->addDirectory(line);
            continue;
        }  
        else {
            // must be a file
            int space = line.find(' ');
            current->addFile(parseIntUntil(line, space));
        }
    }

    res.intResult1 = base->dirSizesBelow100k();
    int target =  30000000 - (70000000 - base->getSize());
    res.intResult2 = base->getBestDeletionTarget(target);

    delete base;
}

// Running day 7: 
//          Part 1 result: 1582412
//          Part 2 result: 3696336
//          Took time: 314.88μs
// Best time using tree: 116us