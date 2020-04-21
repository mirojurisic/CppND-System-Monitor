#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <vector>
#include "linux_parser.h"
#include <string>

class Processor {
 public:
    Processor(){SetOperatingSystem();SetKernel();};
    float Utilization();  // DONE: See src/processor.cpp
    float MemoryUtilization(); // DONE: Return the system's memory utilization
    int RunningProcesses() ; // DONE: Return the number of processes actively running on the system
    int TotalProcesses(); // DONE: Return the total number of processes on the system 
    long int UpTime() ; // DONE: Return the number of seconds since the system started running
    void SetKernel() ; // DONE: Return the system's kernel identifier (string)
    void SetOperatingSystem();// DONE: Return the operating system name
    std::string Kernel() ; // DONE: Return the system's kernel identifier (string)
    std::string OperatingSystem();// DONE: Return the operating system name
    
 private:
    // these two attibutes are not changing during the running of system monitor so no need to call functions
    // instead keep it in a class
    std::string operatingSystem_;
    std::string kernel_;
    
    
};

#endif