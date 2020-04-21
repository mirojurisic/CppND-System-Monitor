#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

     
// DONE: Return this process's ID
int Process::Pid() { 
    return pid_; }

// DONE: Return this process's CPU utilization
float Process::CpuUtilization() { return cpuUtilization_; }

// DONE: Return the command that generated this process
string Process::Command() { return command_; }

// DONE: Return this process's memory utilization
string Process::Ram() { return ram_; }

// DONE: Return the user (name) that generated this process
string Process::User() { return user_; }

// DONE: Return the age of this process (in seconds)
long int Process::UpTime() { return uptime_; }

// DONE: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const { 
    return this->cpuUtilization_ > a.cpuUtilization_;
    
     }



Process::Process(int pid)
{   
    pid_ = pid;
    user_ =    LinuxParser::User(pid_);
    command_ = LinuxParser::Command(pid_);
    ram_=   LinuxParser::Ram(pid_);
    uptime_= LinuxParser::UpTime(pid_);
    cpuUtilization_= LinuxParser::CpuUtilization(pid_);

}
