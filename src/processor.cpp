#include "processor.h"

// TODO: Return the aggregate CPU utilization
double Processor::Utilization() { 
    std::vector<std::string> cpus_ = LinuxParser::CpuUtilization();
    long uptime = LinuxParser::UpTime();
    return (std::stof(cpus_[0])+std::stof(cpus_[1]))/(uptime*1000.);
}


// DONE: Return the system's memory utilization
double Processor::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }



// DONE: Return the number of processes actively running on the system
int Processor::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// DONE: Return the total number of processes on the system
int Processor::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// DONE: Return the number of seconds since the system started running
long int Processor::UpTime() { 
    return LinuxParser::UpTime(); }

// DONE: Return the system's kernel identifier (string)
std::string Processor::Kernel() { 
    return this->kernel_ ;
    }

// DONE: Return the operating system name
std::string Processor::OperatingSystem() { 
    return this->operatingSystem_;
    }
    
void Processor::SetKernel() {
    this->kernel_ =  LinuxParser::Kernel();
    } 
void Processor::SetOperatingSystem()
    {
        this->operatingSystem_ =   LinuxParser::OperatingSystem(); 
  
    }