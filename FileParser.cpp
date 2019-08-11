// THIS IS MY ATTEMPT TO BUILD A TXT FILE PARSER, IT IS NOT RELATED TO OUR GRADUATION PROJECT FINAL OUTPUT, BUT MORE OF
// WARM UP FOR MY C++ DEVELOPING SKILLS, I HOPE YOU UNDERSTAND THAT I AM NOT INTENDING TO TRESPASS ANY OF YOUR WORK JURISDICTION
// THIS ALGORITHM TAKES 2 DIRECTORIES AND AN OPERATION FROM THE TERMINAL, READS INTEGERS IN THESE FILES, PERFORM OPERATION ON BOTH OF THEM
// AND RETURNS THE RESULTS IN AN EXTERNAL TXT FILE.
// EXECUTION TIME IS CALCULATED AND PRINTED INTO TERMINAL.
// Author: As'ad


#include<iostream>
#include<fstream>
#include <vector>
#include<string>
#include "clara.hpp"
#include <algorithm> 
#include <chrono>

using namespace clara;
using namespace std::chrono;



std::vector<int> retrieveIntegers(std::string directory);
std::vector<int> operation(std::vector<int> array1, std::vector<int> array2, std::string operation);
std::vector<int> sum(std::vector<int> array1,std::vector<int> array2);
std::vector<int> subtract(std::vector<int> array1,std::vector<int> array2);
std::vector<int> multi(std::vector<int> array1,std::vector<int> array2);
std::vector<int> div(std::vector<int> array1,std::vector<int> array2);
void streamOut(std::vector<int> results);
bool toggleFlag(bool flag);
bool VALID_OPERATION = false;


int main (int argc, char **argv){
    std::vector<int> arry1,arry2,results;
    auto dir1 = std::string{};
    auto dir2 = std::string{};
    auto oper = std::string{};
    auto parser = Arg(dir1, "dir1")("The path of the first file") |
                  Arg(oper,"oper")("The operator") |
                  Arg(dir2, "dir2")("The path to the second file");

    auto result = parser.parse(Args(argc, argv));
      if (!result)
      {
         std::cerr << "Error in command line: " << result.errorMessage() << std::endl;
         return 1;
      }
      else 
      {
        arry1 = retrieveIntegers(dir1);
        arry2 = retrieveIntegers(dir2);
        // Get starting point exact time
        auto start = high_resolution_clock::now();
        results = operation(arry1,arry2,oper);
        // End point exact time
        auto stop = high_resolution_clock::now();
        // Calculate duration
        auto duration = duration_cast<microseconds>(stop - start);
        if(VALID_OPERATION) {
            streamOut(results);
            std::cout << "Execution time: " << duration.count() << "ms" << "\n";
        }
        
      }

    return 0;
}


// the function takes a directory, parses through the txt file, and store integers in a vector

std::vector<int> retrieveIntegers(std::string directory){
    std::ifstream file;
    std::vector<int> arry;
    int x;
    file.open(directory);
    if (file.is_open()){
        
        while(file >> x){
            arry.push_back(x);
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file " << directory << "\n";
    }
    return arry;
}


// Calculation function that takes the operator and perform the operation on both files

std::vector<int> operation(std::vector<int> array1, std::vector<int> array2, std::string operation){
    if (operation == "plus"){ VALID_OPERATION = true; return sum(array1,array2);}
    else if (operation == "minus"){ VALID_OPERATION = true; return subtract(array1,array2);}
    else if (operation == "multiply"){ VALID_OPERATION = true; return multi(array1,array2);}
    else if (operation == "divide"){ VALID_OPERATION = true; return div(array1,array2);}
    else std::cout << "Unable to use this operator" << "\n";
}



std::vector<int> sum(std::vector<int> array1,std::vector<int> array2){
    std::vector<int> sum;
    for(int i=0; i<array1.size(); i++){
        sum.push_back(array1[i]+array2[i]);
    }
    return sum;
}



std::vector<int> subtract(std::vector<int> array1,std::vector<int> array2){
    std::vector<int> subtraction;
    for(int i=0; i<array1.size(); i++){
        subtraction.push_back(array1[i]-array2[i]);
    }
    return subtraction;
}



std::vector<int> multi(std::vector<int> array1,std::vector<int> array2){
    std::vector<int> multi;
    for(int i=0; i<array1.size(); i++){
        multi.push_back(array1[i]*array2[i]);
    }
    return multi;
}



std::vector<int> div(std::vector<int> array1,std::vector<int> array2){
    std::vector<int> div;
    for(int i=0; i<array1.size(); i++){
        div.push_back(array1[i]/array2[i]);
    }
    return div;
}


// not used for now
bool toggleFlag(bool flag){
    if (flag == true){
        flag = false;
    } else {
        flag = true;
    }
    return flag;
}

void streamOut(std::vector<int> results){
    std::ofstream resultFile;
    int x;
    resultFile.open("results.txt");
    if (resultFile.is_open()){
        for(int i=0; i < results.size(); i++){
            resultFile << results[i] << " ";
        }
        resultFile.close();
    } else {
        std::cout << "Unable to open file";
    }

}

