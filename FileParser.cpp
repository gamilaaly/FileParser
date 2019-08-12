// THIS IS MY ATTEMPT TO BUILD A TXT FILE PARSER, IT IS NOT RELATED TO OUR GRADUATION PROJECT FINAL OUTPUT, BUT MORE OF
// WARM UP FOR MY C++ DEVELOPING SKILLS, I HOPE YOU UNDERSTAND THAT I AM NOT INTENDING TO TRESPASS ANY OF YOUR WORK JURISDICTION
// THIS ALGORITHM TAKES 2 DIRECTORIES AND AN OPERATION FROM THE TERMINAL, READS INTEGERS IN THESE FILES, PERFORM OPERATION ON BOTH OF THEM
// AND RETURNS THE RESULTS IN AN EXTERNAL TXT FILE.
// EXECUTION TIME IS CALCULATED AND PRINTED INTO TERMINAL.
// EDIT::
// NOW ADDED AN OPTION TO ADD THE DELIMITER THROUGH THE TERMINAL ARGUMENTS TO PARSE ALL KINDS OF DELIMITERS
// Author: As'ad


#include<iostream>
#include<fstream>
#include <vector>
#include<string>
#include <clara/clara.hpp>
#include <algorithm> 
#include <chrono>
#include <sstream>
#include <fmt/format.h>

using namespace clara;
using namespace std::chrono;



std::vector<int> retrieveIntegers(std::string directory);
std::vector<int> retrieveIntegers(std::string directory,char delimiter);
std::vector<int> operation(std::vector<int> array1, std::vector<int> array2, std::string operation);
std::vector<int> sum(std::vector<int> array1,std::vector<int> array2);
std::vector<int> subtract(std::vector<int> array1,std::vector<int> array2);
std::vector<int> multi(std::vector<int> array1,std::vector<int> array2);
std::vector<int> div(std::vector<int> array1,std::vector<int> array2);
void streamOut(std::vector<int> results, std::string outDir);
bool toggleFlag(bool flag);
bool VALID_OPERATION = false;


int main (int argc, char **argv){
    std::vector<int> arry1,arry2,results;
    auto dir1 = std::string{};
    auto dir2 = std::string{};
    auto oper = std::string{};
    auto outDir = std::string{};
    outDir = "results.txt";
    char delim1 = ' ';
    char delim2 = ' ';
    auto parser = Arg(dir1, "dir1")("The path of the first file") |
                  Arg(oper,"oper")("The operator") |
                  Arg(dir2, "dir2")("The path to the second file") |
                  Opt(delim1, "delimiter")["-q"]("Delimiter if exists")|
                  Opt(delim2, "delimiter")["-w"]("Delimiter if exists") |
                  Opt(outDir, "output directory")["-e"]("Output Directory");


    auto result = parser.parse(Args(argc, argv));
      if (!result){
         std::cerr << "Error in command line: " << result.errorMessage() << std::endl;
         return 1;
      }
      else {
        
        arry1 = retrieveIntegers(dir1,delim1);
        arry2 = retrieveIntegers(dir2,delim2);

        // Get starting point exact time
        auto start = high_resolution_clock::now();
        results = operation(arry1,arry2,oper);
        // End point exact time
        auto stop = high_resolution_clock::now();
        // Calculate duration
        auto duration = duration_cast<microseconds>(stop - start);
        if(VALID_OPERATION) {
            streamOut(results,outDir);
            std::cout << "Execution time: " << duration.count() << "ms" << "\n";
            }
        }
         return 0;
      }



// The function takes a directory, parses through the txt file, and returns a vector containing the integers


std::vector<int> retrieveIntegers(std::string directory){
    std::ifstream file;
    std::vector<int> arry;
    int temp;
    file.open(directory);
    if (file.is_open()){

        while(file >> temp){
            arry.push_back(temp);
        }

        file.close();

    }

    else {
        std::cerr << "Unable to open file " << directory << "\n";
    }

    return arry;
}

// This function takes a directory and a delimiter, parses through the txt file, and returns a vector containing the integers

std::vector<int> retrieveIntegers(std::string directory, char delimiter){
    std::ifstream file;
    std::vector<std::string> arry;
    std::vector<int> arryint;
    std::string temp;
    file.open(directory);
    if (file.is_open()){

         while (getline(file, temp ,delimiter)){
            arry.push_back(temp);
         }

        file.close();

    }

    else {
        std::cerr << "Unable to open file " << directory << "\n";
    }
    for (int i=0; i<arry.size();i++){
        arryint.push_back(std::stoi(arry[i]));
    }
    return arryint;
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
        if (array1.size() > array2.size()){
        for (int i=0; i < (array1.size() - array2.size()); i++){
            array2.push_back(0);
        } 
    } else if ( array2.size() > array1.size() ) {
        for (int i=0; i < (array2.size() - array1.size()); i++){
            array1.push_back(0);
        } 
    }
    for(int i=0; i<array1.size(); i++){
        sum.push_back(array1[i]+array2[i]);
    }
    return sum;
}



std::vector<int> subtract(std::vector<int> array1,std::vector<int> array2){
    std::vector<int> subtraction;
        if (array1.size() > array2.size()){
        for (int i=0; i < (array1.size() - array2.size()); i++){
            array2.push_back(0);
        } 
    } else if ( array2.size() > array1.size() ) {
        for (int i=0; i < (array2.size() - array1.size()); i++){
            array1.push_back(0);
        } 
    }
    for(int i=0; i<array1.size(); i++){
        subtraction.push_back(array1[i]-array2[i]);
    }
    return subtraction;
}



std::vector<int> multi(std::vector<int> array1,std::vector<int> array2){
    std::vector<int> multi;
        if (array1.size() > array2.size()){
        for (int i=0; i < (array1.size() - array2.size()); i++){
            array2.push_back(1);
        } 
    } else if ( array2.size() > array1.size() ) {
        for (int i=0; i < (array2.size() - array1.size()); i++){
            array1.push_back(1);
        } 
    }
    for(int i=0; i<array1.size(); i++){
        multi.push_back(array1[i]*array2[i]);
    }
    return multi;
}



std::vector<int> div(std::vector<int> array1,std::vector<int> array2){
    std::vector<int> div;
        if (array1.size() > array2.size()){
        for (int i=0; i < (array1.size() - array2.size()); i++){
            array2.push_back(1);
        } 
    } else if ( array2.size() > array1.size() ) {
        for (int i=0; i < (array2.size() - array1.size()); i++){
            array1.push_back(1);
        } 
    }
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


// The function that export the results into a .txt file called "results.txt"

void streamOut(std::vector<int> results, std::string outDir){
    std::ofstream resultFile;
    int x;
    resultFile.open(outDir);
    if (resultFile.is_open()){
        for(int i=0; i < results.size(); i++){
            resultFile << results[i] << " ";
        }
        resultFile.close();
    } else {
        std::cout << "Unable to open file";
    }

}



