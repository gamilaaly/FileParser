#include<iostream>
#include<fstream>
#include <vector>
#include<string>
#include "clara.hpp"
#include <algorithm> 
#include <chrono>
#include <sstream>

void retrieveIntegers(std::string directory, char delimiter){
    std::ifstream file;
    std::vector<std::string> arry;
    std::string temp;
    file.open(directory);
    if (file.is_open()){

         while (getline(file, temp ,'/')){
            arry.push_back(temp);
         }

        file.close();

    }

    else {
        std::cerr << "Unable to open file " << directory << "\n";
    }
    for (int i=0; i< arry.size() ; i++)
        std::cout << arry[i];
}



main() {
    retrieveIntegers("/home/crow/FileParser/test-with-delimiter.txt",'/');
    return 0;
}