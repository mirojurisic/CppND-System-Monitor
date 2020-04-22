#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONEx2: An example of how to read data from the filesystem
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
std::vector<std::string> meanings{
    "(1) pid",          "(2) comm",         "(3) state",
    "(4) ppid",         "(5) pgrp",         "(6) session",
    "(7) tty_nr",       "(8) tpgid",        "(9) flags",
    "(10) minflt",      "(11) cminflt",     "(12) majflt",
    "(13) cmajflt",     "(14) utime",       "(15) stime",
    "(16) cutime",      "(17) cstime",      "(18) priority",
    "(19) nice",        "(20) num_threads", "(21) itrealvalue",
    "(22) starttime",   "(23) vsize",       "(24) rss",
    "(25) rsslim",      "(26) startcode",   "(27) endcode",
    "(28) startstack",  "(29) kstkesp",     "(30) kstkeip",
    "(31) signal",      "(32) blocked",     "(33) sigignore",
    "(34) sigcatch",    "(35) wchan",       "(36) nswap",
    "(37) cnswap",      "(38) exit_signal", "(39) processor",
    "(40) rt_priority", "(41) policy",      "(42) delayacct_blkio_ticks",
    "(43) guest_time",  "(44) cguest_time", "(45) start_data",
    "(46) end_data",    "(47) start_brk",   "(48) arg_start",
    "(49) arg_end",     "(50) env_start",   "(51) env_end",
    "(52) exit_code"};

// DONEx2: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
// DONEx2
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
  std::string key, value, key1, value1, key2, value2, line;
  key1 = "MemTotal:";  // total memory
  key2 = "MemFree:";   // available memory
  value1 = value2 = "-";
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream stringStream(line);
      stringStream >> key >> value;
      if (key == key1)

        value1 = value;

      else if (key == key2)

        value2 = value;
    }
  }
  if (value1 != "-" && value2 != "-")
    return 1 - std::stod(value2) / std::stod(value1);
  return 0.0;
}

// DONEx2: Read and return the system uptime
long LinuxParser::UpTime() {
  string line, time;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> time;
  }
  return std::stol(time);
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid ) { 
  string line, token;
  vector<string> values;
  std::ifstream filestream(LinuxParser::kProcDirectory + to_string(pid) +
                           LinuxParser::kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    while (linestream >> token) {
      values.push_back(token);
    }
  }
  long jiffies{0};
  if (values.size() > 21) {
    long user = stol(values[13]);
    long kernel = stol(values[14]);
    long children_user = stol(values[15]);
    long children_kernel = stol(values[16]);
    jiffies = user + kernel + children_user + children_kernel;
  }
  return jiffies;
   }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  vector<string> cpu;
  std::string key, user, line, system, value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream stringStream(line);
      stringStream >> key >> user >> value >> system;
      if (key == "cpu") {
        cpu.push_back(user);
        cpu.push_back(system);
      }
    }
  }
  return cpu;
}
//

// DONEx2: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  std::string key, value, line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream stringStream(line);
      stringStream >> key >> value;
      if (key == "processes") return std::stoi(value);
    }
  }
  return 0;
}

// DONEx2: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  std::string key, value, line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream stringStream(line);
      stringStream >> key >> value;
      if (key == "procs_running") return std::stoi(value);
    }
  }
  return 0;
}

// DONEx2: Read and return the command associated with a process
string LinuxParser::Command(int pid) {
  string command;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, command);
  }
  if(command.size()>40)
    command = command.substr(0,40);
  return command;
}

// DONEx2: Read and return the memory used by a process
string LinuxParser::Ram(int pid) {
  std::string key, value, line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream stringStream(line);
      stringStream >> key >> value;
      if (key == "VmData:") return std::to_string(std::stoi(value) / 1000);
    }
  }
  return string();
}

// DONEx2: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
  std::string key, value, line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream stringStream(line);
      stringStream >> key >> value;
      if (key == "Uid:") return value;
    }
  }
  return string();
}

// DONEx2: Read and return the user associated with a process
string LinuxParser::User(int pid) {
  string Uid = LinuxParser::Uid(pid);
  std::string key, x, line, value_uid;
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream stringStream(line);
      while (stringStream >> key >> x >> value_uid) {
        if (x == "x" && value_uid == Uid) return key;
      }
    }
  }

  return string();
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  string upTime;
  if (stream.is_open()) {
    std::string line;
    std::getline(stream, line);
    std::istringstream linestream(line);
    string num;
    for (int i = 0; i < 21; i++) {
      linestream >> num;
    }
    linestream >> upTime;
    return LinuxParser::UpTime() - std::stol(upTime)/sysconf(_SC_CLK_TCK);

  }
  return 0.;
}

float LinuxParser::CpuUtilization(int pid) {
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);

  if (stream.is_open()) {
    std::string line;
    std::getline(stream, line);
    std::istringstream linestream(line);
    std::string ignore;
    long utime;
    long stime;
    long cutime;
    long cstime;
    long starttime;
    for (int i = 0; i < 13; i++) linestream >> ignore;
    linestream >> utime >> stime >> cutime >> cstime;
    for (int i = 0; i < 4; i++) linestream >> ignore;
    linestream >> starttime;
    return 1. * (utime + stime + cutime + cstime) / LinuxParser::UpTime(pid);
  }
  return 0.;

}
