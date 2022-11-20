


int test() {
    char s = 0b1111;
    char x = 0b11;

    //(-((firstArray[5] & s1) != s1) | firstArray[5])
    std::cout << -((s & x) == x)  << '\n';

    return 1; 
}
