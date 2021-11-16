#include <cstring>
#include <unistd.h>
#include "uv.h" 
#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include "getTime.h"
using namespace std;
#ifndef _WIN32

#endif

#define START_TIME 21
#define END_TIME  8

#define LOOP_TIME 600
#define TASK "tasklist.exe /fi \"imagename eq  nbminer.exe\" >./log/task.log"


static string KILL = "taskkill.exe /PID ";
static string KILL2 = "taskkill.exe /im nbminer.exe /f";
void killProcess(uv_timer_t *handle)
{
    cout<<TASK<<endl;
    system(TASK);
    ifstream file;
    file.open("./log/task.log"); 
    string str;
    vector<string> log;
    vector<int> PID;
    while(file)
    {
        getline(file,str);
        if(file.fail()) 
            break;
        log.push_back(str);
    }
    file.close();

    for (int i = 0; i < log.size(); i++) {
        string line = log[i];
        int start = line.find("exe");
        if (start == -1) {
            continue;
        }
        int end = line.find("Console");
        string num = line.substr(start + 3, end - start);
        cout<<num<<endl;
        cout<<atoi(num.c_str())<<endl;
        PID.push_back(atoi(num.c_str()));
    }

    for (int num : PID) {
        string kill_pid(KILL);
        kill_pid.append(to_string(num));
        kill_pid.append("/f");
        cout<<kill_pid<<endl;
        system(kill_pid.c_str());
    }
    uv_timer_stop(handle);
    return ;
}
void checkTime(uv_timer_t *handle) 
{
    int hour;
#ifdef HOUR_BY_DATE
    hour = getTime();
#endif //HOUR_BY_DATE

#ifdef HOUR_BY_API
    timeval nowTus;
    hour = getTime(nowTus);
#endif // HOUR_BY_API
    //cout<<hour<<endl;
    if (hour >= START_TIME | hour < END_TIME) {
        return;
    }
    //killProcess(handle);
    cout<<KILL2<<endl;
    system(KILL2.c_str());
    uv_timer_stop(handle);
    return;
}

void timer_func(uv_timer_t *handle) {
    checkTime(handle);
    return ;
}

int main()
{
    uv_loop_t *loop;
    uv_timer_t gc_req;
    loop = uv_default_loop();
    uv_timer_init(loop, &gc_req);  
    uv_timer_start(&gc_req, timer_func, 0, LOOP_TIME);
    uv_run(loop, UV_RUN_DEFAULT);   
    return 0;
}