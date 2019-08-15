
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
#include <utility> // for std::pair
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm> 
#include <chrono>

// Misc.
#include "clara.hpp"
#include "fmt/format.h"


/**
 * 4- Avoid opening namespaces global-wide.
 * You can instead open a namespace only within the function body, where you actually invoke the library. (done)
 * */



// Functions

/**
 * 11- A general rule for all of the functions in this file.
 * If you are receiving a container that you only read from, then receive it by constant reference (e.g const std::string &dictionary).
 * If you are receiving a container that you will modify, then receive it by reference (e.g std::string &dictionary).
 * By using references, you avoid the overhead of the unnecessary copying of data to a new container.
 * */

std::vector<int> retrieveIntegers(const std::string &directory);
std::vector<int> retrieveIntegers(const std::string &directory,const char &delimiter);

/**
 * 13- You can return two variables here: the results and a flag indicating whether it is a valid operation.
 * For that we can use `std::pair` class: doc https://en.cppreference.com/w/cpp/utility/pair
 * */
std::pair< std::vector<int>, bool> operation(std::vector<int> &array1, std::vector<int> &array2, const char &operation);
std::vector<int> sum(const std::vector<int> &array1, const std::vector<int> &array2);
std::vector<int> sub(const std::vector<int> &array1,const std::vector<int> &array2);
std::vector<int> mul(const std::vector<int> &array1,const std::vector<int> &array2);
std::vector<int> div(const std::vector<int> &array1,const std::vector<int> &array2);
void streamOut(const std::vector<int> &results, const std::string &outDir);


/**
 * 5- Never make global variables, unless for defining global constants. 
 * // I don't get what is the problem here as we use it in main function and other function.
 * Asem: in the current task this global variable is not problematic, which is not always the case.
 * Watch an alternative solution to avoid this global variable.
 * */

int main (int argc, char **argv){
    std::vector<int> arry1,arry2,results;
    std::string dir1, dir2; // 6- Just a matter of taste, and to be consistent with the style at line 74.
    std::string outDir = "results.txt"; // 7- Always better to declare and initialize at the same line, when possible. 
    char delim1 = ' ';
    char delim2 = ' ';
    char oper;
    auto parser = clara::Arg(dir1, "dir1")("The path of the first file") |
                  clara::Arg(oper,"oper")("The operator") |
                  clara::Arg(dir2, "dir2")("The path to the second file") |
                  clara::Opt(delim1, "delimiter")["-f"]("Delimiter if exists")|
                  clara::Opt(delim2, "delimiter")["-s"]("Delimiter if exists") |
                  clara::Opt(outDir, "output directory")["-e"]("Output Directory");


    auto result = parser.parse(clara::Args(argc, argv));
      if (!result){
         std::cerr << "Error in command line: " << result.errorMessage() << std::endl;
         return 1;
      }
      else {
        
        arry1 = retrieveIntegers(dir1,delim1);
        arry2 = retrieveIntegers(dir2,delim2);

        // Get starting point exact time
        auto start = std::chrono::high_resolution_clock::now();

        /**
         * This is a good technique to learn, called structured binding, introduced in C++17.
         * */
        auto [results, valid] = operation(arry1,arry2,oper);
        // End point exact time
        auto stop = std::chrono::high_resolution_clock::now();
        // Calculate duration
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        if(valid) {
            streamOut(results,outDir);
            std::cout << "Execution time: " << duration.count() << "ms" << "\n";
            }
        }
         return 0;
      }


// This function takes a directory and a delimiter, parses through the txt file, and returns a vector containing the integers

std::vector<int> retrieveIntegers(const std::string &directory, const char &delimiter){
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

std::pair< std::vector<int>, bool>
operation(std::vector<int> &array1, std::vector<int> &array2, const char &operation){

    /**
     * 9- Here you better represent the operation with `char` type (e.g '+', '-', etc.) to 
     * avoid the misspelling of words, or ideally, in big projects, using Enum Classes.
     * By using `char` or Enums, here we optimally can use the switch-case statement that 
     * provides a more readable logic. (done)
     * */

    /**
     * 12- You can kill the redundancy of the padding logic.
     * */
    int neutral = (operation == '+' || operation == '-')? 0 : 1;

    if (array1.size() > array2.size()){
        for (int i=0; i < (array1.size() - array2.size()); i++){
            array2.push_back(neutral);
            } 
        }  
    else if ( array2.size() > array1.size() ) {
        for (int i=0; i < (array2.size() - array1.size()); i++){
            array1.push_back(neutral);
        }    
    }

    /**
     * 13- Just forgot to warn you about some special characters 
     * that you may wish to avoid conflicts of using in the command line like '*' (astrist) and forward '/' (forward slash).
     * Astrisk is used in the terminal for wild card tricks (pattern matching).
     * Forward slash is used as directories separator.
     * */
    std::vector< int > results;
    bool valid = true;
    switch (operation){
        case '+':  results = sum(array1,array2); break;

        case '-':  results = sub(array1,array2); break;

        case 'm':  results = mul(array1,array2); break;

        case 'd':  results = div(array1,array2); break;
        
        default:   valid = false;
                std::cout << "Invalid operator!" << "\n" 
                        << "Expected '+', '-', 'm' or 'd' " 
                        << "got " << operation << std::endl; 
    }

    return std::make_pair( results, valid );
}



std::vector<int> sum(const std::vector<int> &array1,const std::vector<int> &array2){
    std::vector<int> sum;
        
    for(int i=0; i<array1.size(); i++){
        sum.push_back(array1[i]+array2[i]);
    }
    return sum;
}



std::vector<int> sub(const std::vector<int> &array1,const std::vector<int> &array2){
    std::vector<int> subtraction;
        
    for(int i=0; i<array1.size(); i++){
        subtraction.push_back(array1[i]-array2[i]);
    }
    return subtraction;
}



std::vector<int> mul(const std::vector<int> &array1,const std::vector<int> &array2){
    std::vector<int> multi;
        
    for(int i=0; i<array1.size(); i++){
        multi.push_back(array1[i]*array2[i]);
    }
    return multi;
}

std::vector<int> div(const std::vector<int> &array1,const std::vector<int> &array2){
    std::vector<int> div;
        
    for(int i=0; i<array1.size(); i++){
        div.push_back(array1[i]/array2[i]);
    }
    return div;
}


// The function that export the results into a .txt file called "results.txt"

void streamOut(const std::vector<int> &results, const std::string &outDir){
    std::ofstream resultFile;
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