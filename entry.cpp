#include <iostream>
#include <chrono>

#include "src/test.h"
#include "src/result.h"
#include "src/readFile.h"
#include "src/days/day1.h"
#include "src/days/day2.h"
#include "src/days/day3.h"
#include "src/days/day4.h"
#include "src/days/day5.h"
#include "src/days/day6.h"
#include "src/days/day7.h"
#include "src/days/day8.h"

using namespace std;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;
using std::chrono::nanoseconds;


typedef void (*dayFunction)(std::vector<std::string>&, result&);
dayFunction functptr[] = {
    &day1,
    // &day2,
    // &day3,
    // &day4,
    // &day5, 
    // &day6,
    // &day7,
    // &day8    
};


void log_result(result res, std::chrono::nanoseconds time){
    //std::cout << "Time: " time.count() << "ns\n";

    if (res.intResult1){
        cout << "\t Part 1 result: " << res.intResult1 << endl;
    }
    
    if (res.intResult2){
        cout << "\t Part 2 result: " << res.intResult2 << endl;
    }

    if (res.longResult1){
        cout << "\t Part 1 result: " << res.longResult1 << endl;
    }
    
    if (res.longResult2){
        cout << "\t Part 2 result: " << res.longResult2 << endl;
    }

    if (time.count() > 1000000){
        printf("\t Took time: %.2fms \n", time.count() / 1000000.0);
        return;
    }
    
    if (time.count() > 1000){
        printf("\t Took time: %.2fμs \n", time.count() / 1000.0);
        return;
    }

    cout << "\t Took time: " << time.count() << "ns" << endl;
}

#define countof(a) (sizeof(a) / sizeof(*(a)))

void runAllDays() {
    std::cout << "Running all present days: " << countof(functptr) << '\n';
    for (int i =0; i < countof(functptr); i++ ){
        std::cout << "Day " << i + 1 << ":" << '\n';
        result res;

        int day = i + 1;

        std::string fileName = "./inputs/day" + std::to_string(day) + ".txt";
        std::vector<std::string> input = getFileContent(fileName);

        auto fn = (*functptr[day - 1]);

        auto t1 = high_resolution_clock::now();
        fn(input, res); 
        auto t2 = high_resolution_clock::now();

        auto ms_int = duration_cast<nanoseconds>(t2 - t1);
        log_result(res, ms_int);
    }
}


int day;
bool all = false;
int runs = 1;
bool shouldTest = false;

void parseArgs(int argCount, char * argv[]) {

    for (int i =1; i < argCount; i++){
        std::string s(argv[i]);

        if (s == "--all") all = true;
        else if (s == "--test") shouldTest = true;
        else if (s == "-" || s == ".") {
            std::cout << "Running last day: " << countof(functptr) << '\n';
            day = countof(functptr);
        }
        else if (s.rfind("--day=", 0) == 0) day = std::stoi(s.substr(6));
        else if (s.rfind("--runs=", 0) == 0) runs = std::stoi(s.substr(7));
        else {
            std::cout << "Invalid arg: " << s << '\n';
            throw 1;
        }
    }
}


void runSingle(std::vector<std::string> &lines, dayFunction fn) {
    cout << "Running day " << day << ": \n";
    result dayResult;

    auto t1 = high_resolution_clock::now();
        fn(lines, dayResult); 
    auto t2 = high_resolution_clock::now();

    auto ms_int = (duration_cast<nanoseconds>(t2 - t1));
    log_result(dayResult, ms_int);
}


void runMultiple(int runs, std::vector<std::string> &lines, dayFunction fn) {
    cout << "Running day " << day << ", " << runs << " times" << ": \n";
    result dayResult;

    auto t1 = high_resolution_clock::now();
    for (int i = 0; i < runs; i++){ fn(lines, dayResult); }
    auto t2 = high_resolution_clock::now();

    auto ms_int = (duration_cast<nanoseconds>(t2 - t1)) / runs;

    log_result(dayResult, ms_int);
}


void debugFunc() {
    day = 1; // Change this as needed
    std::string fileName = "./inputs/day" + std::to_string(day) + ".txt";
    std::vector<std::string> input = getFileContent(fileName);
    auto fn = (*functptr[day - 1]);
    runSingle(input, fn);
}

void run(int argc, char * argv[]){
    if (argc == 1) { std::cout << "Not enough args" << '\n'; return; } 
    parseArgs(argc, argv);

    if (shouldTest){
        test();
        return;
    } else if (all) {
        runAllDays();
        return;
    } 

    std::string fileName = "./inputs/day" + std::to_string(day) + ".txt";
    std::vector<std::string> input = getFileContent(fileName);
    auto fn = (*functptr[day - 1]);

    if (runs == 1){
        runSingle(input, fn);
    } else {
        runMultiple(runs, input, fn);
    }
}


int main(int argc, char * argv[]) {

    run (argc, argv);
    // debugFunc();

    return 0;
}
