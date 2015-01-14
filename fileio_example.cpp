#include <iostream>
#include <fstream>
using namespace std;

int main(void)
{
    std::string buffer;
    buffer.resize(200);
    
    ifstream ifile;
    ofstream ofile;
    ifile.open("in.csv");
    ofile.open("out.csv");
    
    if (!ifile)
    {
        cout << "in file does not exist \n";
        exit(1);
    }
    
    else
    {
        while (std::getline(ifile, buffer ))
        {
            buffer[28] = 'Y';
            buffer[29] = 'E';
            buffer[30] = 'S';
            buffer[31] = '!';
            buffer[32] = '!';
            ofile << buffer;
        }
    }
    
}