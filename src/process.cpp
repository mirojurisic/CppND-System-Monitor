#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;


// DONE: Return this process's ID
int Process::Pid() { return pid; }

// DONE: Return this process's CPU utilization
float Process::CpuUtilization() { return cpuUtilization; }

// DONE: Return the command that generated this process
string Process::Command() { return command; }

// DONE: Return this process's memory utilization
string Process::Ram() { return ram; }

// DONE: Return the user (name) that generated this process
string Process::User() { return user; }

// DONE: Return the age of this process (in seconds)
long int Process::UpTime() { return uptime; }

// DONE: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const { 
    return this->cpuUtilization > a.cpuUtilization; }

Process::Process(int pid,
    std::string user,
    std::string command,
    std::string ram,
    long int uptime ,
    float cpuUtilization)
    :    pid(pid),
         user(user),
         command(command),
         ram(ram),
         uptime(uptime),
         cpuUtilization(cpuUtilization){};
