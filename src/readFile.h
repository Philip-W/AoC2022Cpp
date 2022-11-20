#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> getFileContent(std::string fileName){

    std::vector<std::string> vecOfStrs;
    // Open the File
    std::ifstream in(fileName.c_str());
    // Check if object is valid
    if(!in)
    {
        std::cerr << "Cannot open the File : "<<fileName<<std::endl;
        return vecOfStrs;
    }
    std::string str;
    // Read the next line from File untill it reaches the end.
    while (std::getline(in, str))
    {
        // Line contains string of length > 0 then save it in vector
        //if(str.size() > 0)
            vecOfStrs.push_back(str);
    }
    //Close The File
    in.close();
    return vecOfStrs;
}



std::string getFileAsString(const std::string& filename) {
    std::ifstream in(filename);
    std::string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    return contents;
}