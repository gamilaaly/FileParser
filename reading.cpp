#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
int main(int argc, char *argv[])
{
  string line;
  string line1;
  string line2;
  string line3;
  stringstream po;
  fstream infile;
  fstream file;
  vector<int> array1;
  vector<int> array2;
  int x;
  infile.open("nty.txt");
  while (getline(infile, line, '/'))
  {
    cout << line << endl;
    std::istringstream parser(line);
    parser >> x;
    array1.push_back(x);
    while (getline(infile, line1, ','))
    {
      cout << line1 << endl;
      std::istringstream parser(line1);
      parser >> x;
      array1.push_back(x);
      while (getline(infile, line2, '*'))
      {
        cout << line2 << endl;
        std::istringstream parser(line2);
        parser >> x;
        array1.push_back(x);
        while (getline(infile, line3, '|'))
          //cout << "line3" << line3 << endl;
        po << line3;
        po >> x;
        //cout << "x3ndline3" << x << endl;
        array1.push_back(x);
      }
    }
  }
  file.open("num.txt");
  while (getline(file, line, '/'))
  {
    cout << "tanyfile";
    cout << line << endl;
    std::istringstream parser(line);
    parser >> x;
    array2.push_back(x);
    while (getline(file, line1, ','))
    {
      cout << line1 << endl;
      std::istringstream parser(line1);
      parser >> x;
      array2.push_back(x);
      while (getline(file, line2, '*'))
      {
        cout << line2 << endl;
        std::istringstream parser(line2);
        parser >> x;
        array2.push_back(x);
        while (getline(file, line3, '|'))
          cout << line3 << endl;
        std::istringstream parser1(line3);
        parser1 >> x;
        cout << "x" << x << endl;
        array2.push_back(x);
      }
    }
  }
  for (int i = 0; i <= array1.size(); i++)
  {

    cout << array1[i] << endl;
  }
  for (int i = 0; i <= array2.size(); i++)
  {
    cout << array2[i] << endl;
  }
  return 0;
}