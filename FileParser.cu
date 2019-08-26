
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

// Misc.
#include <clara/clara.hpp>
#include <fmt/format.h>


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
std::vector<int> operation(std::vector<int> &array1, std::vector<int> &array2, const char &operation);
void sum(const std::vector<int> &array1, const std::vector<int> &array2, std::vector<int> &result);
void sub(const std::vector<int> &array1,const std::vector<int> &array2, std::vector<int> &result);
void mul(const std::vector<int> &array1,const std::vector<int> &array2, std::vector<int> &result);
void div(const std::vector<int> &array1,const std::vector<int> &array2, std::vector<int> &result);
void streamOut(const std::vector<int> &results, const std::string &outDir);


/**
 * 5- Never make global variables, unless for defining global constants. // I don't get what is the problem here as we use it in main function and other function.
 * */
bool VALID_OPERATION = false;

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
        results = operation(arry1,arry2,oper);


        if(VALID_OPERATION) {
            streamOut(results,outDir);

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

std::vector<int> operation(std::vector<int> &array1, std::vector<int> &array2, const char &operation){

    std::vector<int> result;
    /**
     * 9- Here you better represent the operation with `char` type (e.g '+', '-', etc.) to 
     * avoid the misspelling of words, or ideally, in big projects, using Enum Classes.
     * By using `char` or Enums, here we optimally can use the switch-case statement that 
     * provides a more readable logic. (done)
     * */
    switch (operation){
        case '+':   VALID_OPERATION = true;
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
                    sum<<<1,1>>>(array1,array2,result);
                    return result;

        case '-':   VALID_OPERATION = true;
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
                    sub<<<1,1>>>(array1,array2,result);
                    return result;

        case '*':   VALID_OPERATION = true;
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
                    mul<<<1,1>>>(array1,array2,result);
                    return result;

        case '/':   VALID_OPERATION = true;
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
                    div<<<1,1>>>(array1,array2,result);
                    return result;
        
        default:    std::cout << "Invalid operator!" << "\n" << "Expected '+', '-', '*' or '/' " << "got " << operation << std::endl;
                    std::vector<int> emptyVector;
                    return emptyVector;
    }
}


__global__
void sum(const std::vector<int> &array1,const std::vector<int> &array2, std::vector<int> &result){
    for(int i=0; i<array1.size(); i++){
        result.push_back(array1[i]+array2[i]);
    }
}

__global__
void sub(const std::vector<int> &array1,const std::vector<int> &array2, std::vector<int> &result){
    for(int i=0; i<array1.size(); i++){
        result.push_back(array1[i]-array2[i]);
    }
}


__global__
void mul(const std::vector<int> &array1,const std::vector<int> &array2, std::vector<int> &result){
    for(int i=0; i<array1.size(); i++){
        result.push_back(array1[i]*array2[i]);
    }
}
__global__
void div(const std::vector<int> &array1,const std::vector<int> &array2, std::vector<int> &result){
    for(int i=0; i<array1.size(); i++){
        result.push_back(array1[i]/array2[i]);
    }
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



