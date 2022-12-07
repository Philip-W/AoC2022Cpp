
#pragma once

// TODO: handle negatives
inline int parseInt(std::string &s) {
    int result = 0;
    for (char const &c: s) {
        result *= 10;
        result += c - '0';
    }
    return result;
}


// TODO: handle negatives
inline int parseIntUntil(std::string &s, int until) {
    int result = 0;

    for (int i =0; i < until; i++){
        result *= 10;
        result += s[i] - '0';
    }
    return result;
}
