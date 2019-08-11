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
 fstream infile;
 infile.open("nty.txt");
  while (getline(infile, line,'/')){
      cout<<line<<endl;
       while (getline(infile, line1,',')){
       cout<<line1<<endl;
      while (getline(infile, line2,'*')){
      cout<<line2<<endl;
       while (getline(infile, line3,'|'))
       cout<<line3<<endl;
  }}}

    return 0;
}