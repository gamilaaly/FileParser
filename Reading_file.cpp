#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
int main(int argc, char *argv[])
{
    string line;
    string line1;
    vector<char> line2;
    string s;
    string ss;
    char con = ' ';
    vector<char> vego;
    vector<string> vegovego;
    int num;
    fstream infile;
    stringstream line0;
    char buffer = ' ';
    string con1;
    infile.open("num.txt");
    
    while (getline(infile, line))
    {
        cout << line << endl;
        line1 = line;
        //cout << line1[0] << endl;

        for (int i = 0; i <= line1.size(); i++)
        {
            line2.push_back(line[i]);
            if (line1[i] == '1' || line1[i] == '2' || line1[i] == '0' || line1[i] == '3' || line1[i] == '4' || line1[i] == '5' || line1[i] == '6' || line1[i] == '7' || line1[i] == '8' || line1[i] == '9')
            {

                vego.push_back(line1[i]);
                 con=line1[i];
                 con1.push_back(con);
                 vegovego.push_back(con1);
                 con=' ';
                 con1=" ";
                if (i > 0)
                {
                    buffer = line1[i-1];
                    //cout << "buffer"<<buffer<<endl;
                    if (buffer == '1' || buffer == '2' || buffer == '0' || buffer == '3' || buffer == '4' || buffer == '5' || buffer == '6' || buffer == '7' || buffer == '8' || buffer == '9')
                    {
                        s += buffer;
                        s += line[i];
                        vegovego.erase(vegovego.end()-1);
                        vegovego.pop_back();
                        vegovego.push_back(s);
                        s = " ";

                     buffer = line1[i-2];
                    //cout << "buffer"<<buffer<<endl;
                    if (buffer == '1' || buffer == '2' || buffer == '0' || buffer == '3' || buffer == '4' || buffer == '5' || buffer == '6' || buffer == '7' || buffer == '8' || buffer == '9')
                    {
                        s += buffer;
                        s += vegovego.back();
                        vegovego.erase(vegovego.end()-1);
                        vegovego.pop_back();
                        vegovego.push_back(s);
                        s = " ";
                    }
                    }
                    
                }
            }
        }
    }
    /*for (int i = 0; i <= vego.size(); i++)
    {
        cout << vego[i] << endl;
    }*/
    for (int i = 0; i <= vegovego.size(); i++)
    {
        cout << vegovego[i] << endl;
    }

    if (infile.fail())
    {
        cout << "an error occurred";
    }
    return 0;
}