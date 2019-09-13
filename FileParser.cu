// STL
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <bits/stdc++.h>

#define SIZE 1024
using namespace std;
// Misc.
#include <clara/clara.hpp>
//#include <fmt/format.h>

//functions
int *retrieveIntegers(const std::string &directory, const char &delimiter);
int *operation(int *array1, int *array2, const char &operation);
void streamOut(int *results, const std::string &outDir);

__global__ void sum(int *array1, int *array2, int *results)
{   

    int i=threadIdx.x;
    if (i <SIZE)    {
        results[i] = array1[i] + array2[i];

    
    }
}
__global__ void sub(int *array1, int *array2, int *results)
{
    int i=threadIdx.x;
    if (i <SIZE)
    {
        results[i] = array1[i] - array2[i];
    }
}
__global__ void mul(int *array1, int *array2, int *results)
{
    int i=threadIdx.x;
    if (i <SIZE){
        results[i] = array1[i] * array2[i];
    }
}
__global__ void div(int *array1, int *array2, int *results)
{
    int i=threadIdx.x;
    if (i <SIZE) {
        results[i] = array1[i] / array2[i];
    }
}

bool VALID_OPERATION = false;

int main(int argc, char **argv)
{

    std::string dir1, dir2;
    std::string outDir = "results.txt";
    char delim1 = ' ';
    char delim2 = ' ';
    char oper;
    auto parser = clara::Arg(dir1, "dir1")("The path of the first file") |
                  clara::Arg(oper, "oper")("The operator") |
                  clara::Arg(dir2, "dir2")("The path to the second file") |
                  clara::Opt(delim1, "delimiter")["-f"]("Delimiter if exists") |
                  clara::Opt(delim2, "delimiter")["-s"]("Delimiter if exists") |
                  clara::Opt(outDir, "output directory")["-e"]("Output Directory");

    auto result = parser.parse(clara::Args(argc, argv));
    if (!result)
    {
        std::cerr << "Error in command line: " << result.errorMessage() << std::endl;
        return 1;
    }
    else
    {
        int *arry1, *arry2, *results;
        cudaMallocManaged(&arry1 , SIZE*sizeof(int));
        cudaMallocManaged(&arry2 , SIZE*sizeof(int));
        cudaMallocManaged(&results, SIZE*sizeof(int));

        arry1 = retrieveIntegers(dir1, delim1);
        arry2 = retrieveIntegers(dir2, delim2);
        results = operation(&arry1[0], &arry2[0], oper);
        
        if (VALID_OPERATION)
        {
            streamOut(&results[0], outDir);
        }
        cudaFree(arry1);
        cudaFree(arry2);
        cudaFree(results);
    }

    return 0;
}

int *retrieveIntegers(const std::string &directory, const char &delimiter)
{
    std::ifstream file;
    std::string temp;

    std::vector<std::string> arry;
    int *arryint;
    string *a;
    cudaMallocManaged(&arryint , SIZE*sizeof(int));
    cudaMallocManaged(&a , SIZE*sizeof(string));
   
    file.open(directory);
    if (file.is_open())
    {
        while (getline(file, temp, delimiter))
        {
            arry.push_back(temp);
        }
        std::copy(arry.begin(), arry.end(), a);
        file.close();
    }

    else
    {
        std::cerr << "Unable to open file " << directory << "\n";
    }

    for (int i = 0; i <10 ; i++)
    {

        arryint[i] = (std::stoi(a[i]));
    
    }
    return arryint;
}

int *operation(int *array1, int *array2, const char &operation)
{
    int *result ;
    cudaMallocManaged(&result , SIZE*sizeof(int));


    switch (operation)
    {
    case 'p':
        VALID_OPERATION = true;
        {
            sum<<<1,SIZE>>>(&array1[0], &array2[0], &result[0]);
            cudaDeviceSynchronize();
            return result;
        }

    case 's':
        VALID_OPERATION = true;
        {
            sub<<<1,SIZE>>>(&array1[0], &array2[0], &result[0]);
            cudaDeviceSynchronize();
            return result;
        }

    case 'm':
        VALID_OPERATION = true;
        {
            mul<<<1,SIZE>>>(&array1[0], &array2[0], &result[0]);
            cudaDeviceSynchronize();
            return result;
        }

    case 'd':
        VALID_OPERATION = true;
        {
            div<<<1,SIZE>>>(&array1[0], &array2[0], &result[0]);
            cudaDeviceSynchronize();
            return result;
            
        }
        cudaFree(result);

    default:
        std::cout << "Invalid operator!"
                  << "\n"
                  << "Expected '+', '-', '*' or '/' "
                  << "got " << operation << std::endl;
        int *emptyArray;

        return emptyArray;
    }

}

// The function that export the results into a .txt file called "results.txt"

void streamOut(int *results, const std::string &outDir)
{
    std::ofstream resultFile;
    resultFile.open(outDir);
    if (resultFile.is_open())
    {
        for (int i = 0; i < SIZE; i++)
        {
            resultFile << results[i] << " ";
        }
        resultFile.close();
    }
    else
    {
        std::cout << "Unable to open file";
    }
}
