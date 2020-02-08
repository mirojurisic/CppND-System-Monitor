#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel,version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version>>kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// DONE: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
      std::string key,value,key1,value1,key2,value2,line;
      key1 = "MemTotal:";//total memory
      key2 = "MemFree:";//available memory
      value1=value2="-";
  std::ifstream stream (kProcDirectory + kMeminfoFilename);
  if(stream.is_open())
  {
    while(std::getline(stream,line))
    {
      std::istringstream stringStream(line);
      stringStream>>key>>value;
      if(key==key1)
      
        value1 = value;
      
      else if (key==key2)
      
        value2 = value;
      
      
    }
  }
  if(value1!="-" && value2!="-")
  return 1-std::stod(value2)/std::stod(value1);
}

// DONE: Read and return the system uptime
long LinuxParser::UpTime() { 
  string line,time;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> time ;
  }
  return std::stol(time);
 }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// DONE: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
    std::string key,value,line;
  std::ifstream stream (kProcDirectory + kStatFilename);
  if(stream.is_open())
  {
    while(std::getline(stream,line))
    {
      std::istringstream stringStream(line);
      stringStream>>key>>value;
      if(key=="processes")
        return std::stoi(value);
    }
  }
  return 0; 
}

// DONE: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  std::string key,value,line;
  std::ifstream stream (kProcDirectory + kStatFilename);
  if(stream.is_open())
  {
    while(std::getline(stream,line))
    {
      std::istringstream stringStream(line);
      stringStream>>key>>value;
      if(key=="procs_running")
        return std::stoi(value);
    }
  }
  return 0; }

// DONE: Read and return the command associated with a process
string LinuxParser::Command(int pid) { 
    string  command;
    std::ifstream stream(kProcDirectory + std::to_string(pid)+ kCmdlineFilename);
    if (stream.is_open()) {
      std::getline(stream, command);
  }
  return command;
   }

// DONE: Read and return the memory used by a process
string LinuxParser::Ram(int pid) { 
  std::string key,value,line;
  std::ifstream stream (kProcDirectory + std::to_string(pid) + kStatusFilename);
  if(stream.is_open())
  {
    while(std::getline(stream,line))
    {
      std::istringstream stringStream(line);
      stringStream>>key>>value;
      if(key=="VmSize:")
        return std::to_string( std::stoi(value)/1000);
    }
  }
  return string();
}

// DONE: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) { 
      std::string key,value,line;
  std::ifstream stream (kProcDirectory + std::to_string(pid) + kStatusFilename);
  if(stream.is_open())
  {
    while(std::getline(stream,line))
    {
      std::istringstream stringStream(line);
      stringStream>>key>>value;
      if(key=="Uid:")
        return value;
    }
  }
  return string();
 }

// DONE: Read and return the user associated with a process
string LinuxParser::User(int pid) { 
  string Uid = LinuxParser::Uid(pid);
  std::string key,x,line,value_uid;
  std::ifstream stream (kPasswordPath);
  if(stream.is_open())
  {
    while(std::getline(stream,line))
    {
      std::replace(line.begin(),line.end(),':',' ');
      std::istringstream stringStream(line);
      while (stringStream>>key>>x>>value_uid) 
      {
          if(x=="x"&&value_uid == Uid)
            return key;
    }
  }
  }
  
  return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }

