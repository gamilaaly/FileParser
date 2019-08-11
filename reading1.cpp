#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
int main(int argc, char *argv[])
{
    string line;
    string temp;
    fstream infile;
    fstream file;
    int num;
    //string line1;
    vector<int> array;
    vector<int> array1;
    stringstream parser;
    infile.open("num.txt");
    file.open("nty.txt");
    while (getline(infile, line))
    {
        cout << line << endl;
        parser << line;
        while (!parser.eof())
        {
            parser >> temp;
            if (stringstream(temp) >> num)
            {
                //cout << "num" << num << endl;
                array.push_back(num);
            }
            temp = " ";
        }
        parser.str("");
        parser.clear();
    }
     while (getline(file, line))
    {
        cout << line << endl;
        parser << line;
        while (!parser.eof())
        {
            parser >> temp;
            if (stringstream(temp) >> num)
            {
                cout << "num" << num << endl;
                array1.push_back(num);
            }
            temp = " ";
        }
        parser.str("");
        parser.clear();
    }

     for (int i = 0; i <= array.size(); i++)
    {
        cout << array[i] << endl;
    }
     for (int i = 0; i <= array1.size(); i++)
    {
        cout << array1[i] << endl;
    }
    return 0;
}
