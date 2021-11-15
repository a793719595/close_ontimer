#include <iostream>
#include <ctime>
#include <fstream>
#include <cstring>
#include <unistd.h>
using namespace std;
#define DATE "date \"+ %H\" >./log/time.log"

int getTime()
{    
    cout<<DATE<<endl;
    system(DATE);
    ifstream file;
    file.open("./log/time.log"); 
    string str;
    vector<string> log;
    getline(file,str);
    file.close();
    return atoi(str.c_str());
}