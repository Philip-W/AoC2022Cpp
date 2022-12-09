#include <iostream>
#include <chrono>

#include <boost/algorithm/string.hpp>
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
#include "src/days/day9.h"

using namespace std;

// TODO this is probably bad
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;
using std::chrono::nanoseconds;

#define countof(a) (sizeof(a) / sizeof(*(a)))

typedef void (*dayFunction)(std::vector<std::string>&, result&);

dayFunction functptr[] = {
    &day1,
    &day2,
    &day3,
    &day4,
    &day5, 
    &day6,
    &day7,
    &day8,
    &day9
};


void log_result(result res, float time){
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

    if (res.stringResult1 != ""){
        cout << "\t Part 1 result: " << res.stringResult1 << endl;
    }
    
    if (res.stringResult2 != ""){
        cout << "\t Part 2 result: " << res.stringResult2 << endl;
    }

    if (time < 0) return;
    if (time > 1000000){
        printf("\t Took time: %.2fms \n", time/ 1000000.0);
        return;
    }
    
    if (time > 1000){
        printf("\t Took time: %.2fμs \n", time / 1000.0);
        return;
    }

    cout << "\t Took time: " << time << "ns" << endl;
}

void runAllDays() {
    std::cout << "Running all present days: " << countof(functptr) << '\n';
    std::chrono::nanoseconds total;
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
        log_result(res, ms_int.count());
        total += ms_int;
    }

    printf("\n \nTotal time for all days: %.2fμs | %.2fms   \n", total.count() / 1000.0,  total.count() / 1000000.0);
}


int day;
bool all = false;
int runs = 1;
bool shouldTest = false;

void parseArgs(int argCount, char * argv[]) {

    if (argCount == 1) { 
        std::cout << "No args present, running latest day" << '\n'; 
        //auto end = std::chrono::system_clock::now();
        //std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        //std::string s = std::ctime(&end_time);

        // vector<string> strs;
        // boost::split(strs,s, boost::is_any_of(" "));
        // for (int i=0; i < strs.size(); i++){
        //     std::cout << strs[i] << " ";
        // }

        //std::cout << " \n day: " << strs[2] << '/n';
        day = countof(functptr);
        return;
    }

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
            throw 1; // TODO, probably doesn't even work
        }
    }
}
 
void runSingle(std::vector<std::string> lines, dayFunction fn) {
    cout << "Running day " << day << ": \n";
    result dayResult;

    auto t1 = high_resolution_clock::now();
    fn(lines, dayResult); 
    auto t2 = high_resolution_clock::now();

    auto ms_int = (duration_cast<nanoseconds>(t2 - t1));
    log_result(dayResult, ms_int.count());
}


void runMultiple(int runs, std::vector<std::string> &lines, dayFunction fn) {
    cout << "Running day " << day << ", " << runs << " times" << ": \n";
    std::vector<std::chrono::nanoseconds> times;
    result dayResult;

    for (int i = 0; i < runs; i++){
        auto t1 = high_resolution_clock::now();
        fn(lines, dayResult);
        auto t2 = high_resolution_clock::now();
        times.push_back(duration_cast<nanoseconds>(t2 - t1));
    }


    std::chrono::nanoseconds total;
    for (auto t : times){
        total += t;
    }
    auto mean = total / runs;

    std::sort(times.begin(), times.end());
    auto quarterPercentile = times[times.size()/ 4].count() /1000.0;
    auto threeQuarterPercentile = times[times.size() * 3/ 4].count() / 1000.0;
    auto median = times[times.size()/ 2].count() / 1000.0;

    log_result(dayResult, -1);
    
    // Is microsecond
    if (median > 1 && median < 1000){
        std::string color = "\033[1;32m";
        printf("\nPercentiles (25, 50, 75): %s [%.2fμs. %.2fμs, %.2fμs] \033[0m\nMean time: %s %.2fμs \033[0m\n", color.c_str(), quarterPercentile, median, threeQuarterPercentile,color.c_str(), mean.count() / 1000.0);
        printf("\nBest/worst %s [%.2fμs, %.2fμs] \033[0m\n", color.c_str(), times.front().count() / 1000.0, times.back().count() / 1000.0);
        return;
    }

    if (median > 1000 ){
        median /= 1000.0;
        quarterPercentile /= 1000.0;
        threeQuarterPercentile /= 1000.0;
        mean /= 1000.0;
    
        std::string color = "\033[1;31m";
        printf("\nPercentiles (25, 50, 75): %s [%.2fms. %.2fms, %.2fms] \033[0m\nMean time: %s %.2fms \033[0m\n", color.c_str(), quarterPercentile, median, threeQuarterPercentile,color.c_str(), mean.count() / 1000.0);
        return;
    }
}


void debugFunc() {
    day = 9; // Change this as needed
    std::string fileName = "./inputs/day" + std::to_string(day) + ".txt";
    std::vector<std::string> input = getFileContent(fileName);
    auto fn = (*functptr[day - 1]);
    runSingle(input, fn);
}

void run(int argc, char * argv[]){
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
    //debugFunc();

    return 0;
}
