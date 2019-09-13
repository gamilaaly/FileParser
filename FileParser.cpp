
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
//#include <fmt/format.h>

// Functions

std::vector<int> retrieveIntegers(const std::string &directory);
std::vector<int> retrieveIntegers(const std::string &directory, const char &delimiter);
std::vector<int> operation(std::vector<int> &array1, std::vector<int> &array2, const char &operation);
std::vector<int> sum(const std::vector<int> &array1, const std::vector<int> &array2);
std::vector<int> sub(const std::vector<int> &array1, const std::vector<int> &array2);
std::vector<int> mul(const std::vector<int> &array1, const std::vector<int> &array2);
std::vector<int> div(const std::vector<int> &array1, const std::vector<int> &array2);
void streamOut(const std::vector<int> &results, const std::string &outDir);

/**
 * 5- Never make global variables, unless for defining global constants. // I don't get what is the problem here as we use it in main function and other function.
 * */
bool VALID_OPERATION = false;

int main(int argc, char **argv)
{
    std::vector<int> arry1, arry2, results;
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

        arry1 = retrieveIntegers(dir1, delim1);
        arry2 = retrieveIntegers(dir2, delim2);

        // Get starting point exact time
        auto start = std::chrono::high_resolution_clock::now();
        results = operation(arry1, arry2, oper);
        // End point exact time
        auto stop = std::chrono::high_resolution_clock::now();
        // Calculate duration
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        if (VALID_OPERATION)
        {

            // streamOut(results,outDir);
          //  fmt::print("Execution time {}\n ", duration.count());
             std::cout << "Execution time: " << duration.count() << "ms" << "\n";
        }
    }
    return 0;
}

// This function takes a directory and a delimiter, parses through the txt file, and returns a vector containing the integers

std::vector<int> retrieveIntegers(const std::string &directory, const char &delimiter)
{
    std::ifstream file;
    std::vector<std::string> arry;
    std::vector<int> arryint;
    std::string temp;
    file.open(directory);
    if (file.is_open())
    {

        while (getline(file, temp, delimiter))
        {
            arry.push_back(temp);
        }

        file.close();
    }

    else
    {
        std::cerr << "Unable to open file " << directory << "\n";
    }
    for (int i = 0; i < arry.size(); i++)
    {
        arryint.push_back(std::stoi(arry[i]));
    }
    return arryint;
}

// Calculation function that takes the operator and perform the operation on both files
// In case of unequal lengths of arrays, the shorter array is concatenated with 0s in cases of subtraction and addition
// or 1s in cases of multiplication or division

std::vector<int> operation(std::vector<int> &array1, std::vector<int> &array2, const char &operation)
{

    switch (operation)
    {
    case 'p':
        VALID_OPERATION = true;
        if (array1.size() > array2.size())
        {
            for (int i = 0; i < (array1.size() - array2.size()); i++)
            {
                array2.push_back(0);
            }
        }
        else if (array2.size() > array1.size())
        {
            for (int i = 0; i < (array2.size() - array1.size()); i++)
            {
                array1.push_back(0);
            }
        }
        return sum(array1, array2);

    case 's':
        VALID_OPERATION = true;
        if (array1.size() > array2.size())
        {
            for (int i = 0; i < (array1.size() - array2.size()); i++)
            {
                array2.push_back(0);
            }
        }
        else if (array2.size() > array1.size())
        {
            for (int i = 0; i < (array2.size() - array1.size()); i++)
            {
                array1.push_back(0);
            }
        }
        return sub(array1, array2);

    case 'm':
        VALID_OPERATION = true;
        if (array1.size() > array2.size())
        {
            for (int i = 0; i < (array1.size() - array2.size()); i++)
            {
                array2.push_back(1);
            }
        }
        else if (array2.size() > array1.size())
        {
            for (int i = 0; i < (array2.size() - array1.size()); i++)
            {
                array1.push_back(1);
            }
        }
        return mul(array1, array2);

    case 'd':
        VALID_OPERATION = true;
        if (array1.size() > array2.size())
        {
            for (int i = 0; i < (array1.size() - array2.size()); i++)
            {
                array2.push_back(1);
            }
        }
        else if (array2.size() > array1.size())
        {
            for (int i = 0; i < (array2.size() - array1.size()); i++)
            {
                array1.push_back(1);
            }
        }
        return div(array1, array2);

    default:
        //fmt::print("Invalid operator! Expected {0}, {1}, {2} or {3} got {4} \n ", '+', '-', '*', '/', operation);

        std::cout << "Invalid operator!" << "\n" << "Expected '+', '-', '*' or '/' " << "got " << operation << std::endl;
    }
}

std::vector<int> sum(const std::vector<int> &array1, const std::vector<int> &array2)
{
    std::vector<int> sum;

    for (int i = 0; i < array1.size(); i++)
    {
        sum.push_back(array1[i] + array2[i]);
    }
    return sum;
}

std::vector<int> sub(const std::vector<int> &array1, const std::vector<int> &array2)
{
    std::vector<int> subtraction;

    for (int i = 0; i < array1.size(); i++)
    {
        subtraction.push_back(array1[i] - array2[i]);
    }
    return subtraction;
}

std::vector<int> mul(const std::vector<int> &array1, const std::vector<int> &array2)
{
    std::vector<int> multi;

    for (int i = 0; i < array1.size(); i++)
    {
        multi.push_back(array1[i] * array2[i]);
    }
    return multi;
}

std::vector<int> div(const std::vector<int> &array1, const std::vector<int> &array2)
{
    std::vector<int> div;

    for (int i = 0; i < array1.size(); i++)
    {
        div.push_back(array1[i] / array2[i]);
    }
    return div;
}

// The function that export the results into a .txt file called "results.txt"

void streamOut(const std::vector<int> &results, const std::string &outDir)
{
    std::ofstream resultFile;
    resultFile.open(outDir);
    if (resultFile.is_open())
    {
        for (int i = 0; i < results.size(); i++)
        {
            resultFile << results[i] << " ";
        }
        resultFile.close();
    }
    else
    {
        //fmt::print("{}", "Unable to open file");

        std::cout << "Unable to open file";
    }
}
