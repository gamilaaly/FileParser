// This is my attempt to build a txt file parser, it is not related to our graduation project final output, but more of
// warm up for my c++ developing skills, I hope you understand that I am not intending to trespass any of your work jurisdiction
// this algorithm takes 2 directories and an operation from the terminal, reads integers in these files, perform operation on both of them
// and returns the results in an external txt file.
// Execution time is calculated and printed into terminal.
// Edit::
// Now added an option to add the delimiter through the terminal arguments to parse all kinds of delimiters.
/**
 * Asem: 
 * 1- The above paragraph is difficult to read. No need to upper case'ing it. (done)
 * */


/**
 * 
 * 2- The includes can be better sorted and made in related groups, I fixed this. done by Eng.Asem
 * 3- Be strictly consistent in using spaces, for example: done by Eng.Asem
 * Do not:
 * #include<fstream>
 * #include <vector>
 * Instead:
 * #include <fstream>
 * #include <vector>
 * I fixed this.
 * */

// STL
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm> 
#include <chrono>

// Misc.
#include <clara/clara.hpp>
#include <fmt/format.h>


/**
 * 4- Avoid opening namespaces global-wide.
 * You can instead open a namespace only within the function body, where you actually invoke the library. (done)
 * */
using namespace std::chrono; // I don't know where to put this in the other functions


// Functions & Flags declaration

/**
 * 11- A general rule for all of the functions in this file.
 * If you are receiving a container that you only read from, then receive it by constant reference (e.g const std::string &dictionary).
 * If you are receiving a container that you will modify, then receive it by reference (e.g std::string &dictionary).
 * By using references, you avoid the overhead of the unnecessary copying of data to a new container.
 * */

std::vector<int> retrieveIntegers(std::string directory);
std::vector<int> retrieveIntegers(std::string directory,char delimiter);
std::vector<int> operation(std::vector<int> array1, std::vector<int> array2, std::string operation);
std::vector<int> sum(std::vector<int> array1,std::vector<int> array2);
std::vector<int> subtract(std::vector<int> array1,std::vector<int> array2);
std::vector<int> multi(std::vector<int> array1,std::vector<int> array2);
std::vector<int> div(std::vector<int> array1,std::vector<int> array2);
void streamOut(std::vector<int> results, std::string outDir);
bool toggleFlag(bool flag);

/**
 * 5- Never make global variables, unless for defining global constants. // I don't get what is the problem here as we use it in main function and other function.
 * */
bool VALID_OPERATION = false;

int main (int argc, char **argv){
    std::vector<int> arry1,arry2,results;
    std::string dir1, dir2, oper; // 6- Just a matter of taste, and to be consistent with the style at line 74.
    std::string outDir = "results.txt"; // 7- Always better to declare and initialize at the same line, when possible. 

    using namespace clara;
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
// In case of unequal lengths of arrays, the shorter array is concatenated with 0s in cases of subtraction and addition
// or 1s in cases of multiplication or division

std::vector<int> operation(std::vector<int> array1, std::vector<int> array2, std::string operation){

    /**
     * 9- Here you better represent the operation with `char` type (e.g '+', '-', etc.) to 
     * avoid the misspelling of words, or ideally, in big projects, using Enum Classes.
     * By using `char` or Enums, here we optimally can use the switch-case statement that 
     * provides a more readable logic. (done)
     * */

    if (operation == "+"){ 
        VALID_OPERATION = true;
        if (array1.size() > array2.size()){
            for (int i=0; i < (array1.size() - array2.size()); i++){
                array2.push_back(0);
            } 
        }  
        else if ( array2.size() > array1.size() ) {
            for (int i=0; i < (array2.size() - array1.size()); i++){
            array1.push_back(0);
            }    
        }
        return sum(array1,array2);
    }

    else if (operation == "-"){ 
        VALID_OPERATION = true; 
        if (array1.size() > array2.size()){
            for (int i=0; i < (array1.size() - array2.size()); i++){
                array2.push_back(0);
            } 
        } 
        else if ( array2.size() > array1.size() ) {
            for (int i=0; i < (array2.size() - array1.size()); i++){
            array1.push_back(0);
            } 
        }
        return subtract(array1,array2);
    }
    else if (operation == "*"){ 
        VALID_OPERATION = true;
        if (array1.size() > array2.size()){
            for (int i=0; i < (array1.size() - array2.size()); i++){
                array2.push_back(1);
            } 
        } 
        else if ( array2.size() > array1.size() ) {
            for (int i=0; i < (array2.size() - array1.size()); i++){
                array1.push_back(1);
            } 
        }
        return multi(array1,array2);
    }
    else if (operation == "/"){ 
        VALID_OPERATION = true;
        if (array1.size() > array2.size()){
            for (int i=0; i < (array1.size() - array2.size()); i++){
                array2.push_back(1);
            } 
        } 
        else if ( array2.size() > array1.size() ) {
            for (int i=0; i < (array2.size() - array1.size()); i++){
                array1.push_back(1);
            } 
        }
        return div(array1,array2);
    }

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



