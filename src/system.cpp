#include <unistd.h>

#include <algorithm>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
// testing make sure to comment this out
#include <stdlib.h> /* srand, rand */

#include <iostream>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// DONE: Return the system's CPU
Processor& System::Cpu() {
  cpu_ = Processor();
  return cpu_;
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
  processes_.clear();
  vector<int> pids = LinuxParser::Pids();
  int count  = 0;
  for (auto pid : pids) {
        processes_.emplace_back(Process(pid));
        //processes_.at(count).Debugging(pid);
        count ++;
  }
  std::sort(processes_.begin(), processes_.end());

  return processes_;
}

// DONE: Return the system's kernel identifier (string)
std::string System::Kernel() { return cpu_.Kernel(); }

// DONE: Return the system's memory utilization
float System::MemoryUtilization() { return cpu_.MemoryUtilization(); }

// DONE: Return the operating system name
std::string System::OperatingSystem() { return cpu_.OperatingSystem(); }

// DONE: Return the number of processes actively running on the system
int System::RunningProcesses() { return cpu_.RunningProcesses(); }

// DONE: Return the total number of processes on the system
int System::TotalProcesses() { return cpu_.TotalProcesses(); }

// DONE: Return the number of seconds since the system started running
long int System::UpTime() { return cpu_.UpTime(); }