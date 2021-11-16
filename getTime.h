#include <iostream>
#include <ctime>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <sys/time.h>
using namespace std;
#define DATE "date \"+ %H\" >./log/time.log"

int getTime()
{    
    //cout<<DATE<<endl;
    system(DATE);
    ifstream file;
    file.open("./log/time.log"); 
    string str;
    vector<string> log;
    getline(file,str);
    file.close();
    return atoi(str.c_str());
}

int getTime(timeval &nowTus)
{
    struct tm now_time;
    gettimeofday(&nowTus, NULL);
    localtime_r(&nowTus.tv_sec, &now_time);
    // printf("%d-%d-%d %d:%d:%d\n", now_time.tm_year + 1900, now_time.tm_mon + 1,
    //     now_time.tm_mday, now_time.tm_hour, now_time.tm_min, now_time.tm_sec);
    
    return now_time.tm_hour;    
}