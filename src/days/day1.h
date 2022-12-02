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


void day1Branchless(std::vector<std::string> &lines, result &res) {

    int total = 0;
    int solveSpace[3] = {0};
    int smallest = 0;
    bool flag = false;

    for (int i = 0; i < lines.size(); i++){
        flag = lines[i] == "";
        total += parseInt(lines[i]);

        smallest = -(flag) & (solveSpace[0] > solveSpace[1]);
        smallest = (-(flag) ) & ((smallest & (solveSpace[smallest] <= solveSpace[2])) | (2 & -(solveSpace[smallest] > solveSpace[2])));


        solveSpace[smallest] = ((-(flag) ) & ((total & -(solveSpace[smallest] < total)) | (solveSpace[smallest] & -(solveSpace[smallest] >= total)))) | ((-(!flag)) & solveSpace[smallest] );

        total = total & -(lines[i] != "");
    }

    smallest = (solveSpace[0] > solveSpace[1]);
    smallest = ((smallest & (solveSpace[smallest] <= solveSpace[2])) | (2 & -(solveSpace[smallest] > solveSpace[2])));

    solveSpace[smallest] = (total & -(solveSpace[smallest] < total)) | (solveSpace[smallest] & -(solveSpace[smallest] >= total));


    int largest = (solveSpace[0] < solveSpace[1]);
    largest = (largest & (solveSpace[largest] >= solveSpace[2])) | (2 & -(solveSpace[largest] < solveSpace[2]));

    res.intResult1 = solveSpace[largest];
    res.intResult2 = solveSpace[0] + solveSpace[1] + solveSpace[2];
}


void day1Branched(std::vector<std::string> &lines, result &res) {

    int current;
    int total = 0;
    int solveSpace[3] = {0};
    int smallest = 0;

    for (int i = 0; i < lines.size(); i++){

        if (lines[i] == ""){
            smallest = (solveSpace[0] > solveSpace[1]);
            if (solveSpace[smallest] > solveSpace[2]) smallest = 2;

            // Equivalent to :
            // if (solveSpace[smallest] < total) solveSpace[smallest] = total;
            solveSpace[smallest] = (total & -(solveSpace[smallest] < total)) | (solveSpace[smallest] & -(solveSpace[smallest] >= total));

            total = 0;
            continue;
        }

        total += parseInt(lines[i]);
    }

    smallest = (solveSpace[0] > solveSpace[1]);
    if (solveSpace[smallest] > solveSpace[2]) smallest = 2;

    // Equivalent to : 
    // if (solveSpace[smallest] < total) solveSpace[smallest] = total
    solveSpace[smallest] = (total & -(solveSpace[smallest] < total)) | (solveSpace[smallest] & -(solveSpace[smallest] >= total));


    int largest = solveSpace[0];
    if (solveSpace[1] > largest) largest = solveSpace[1];
    if (solveSpace[2] > largest) largest = solveSpace[2];


    res.intResult1 = largest;
    res.intResult2 = solveSpace[0] + solveSpace[1] + solveSpace[2];
}


void day1(std::vector<std::string> &lines, result &res) {
    day1Branchless(lines, res);
}

// 66487
// 197301
