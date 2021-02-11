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
  string os, v, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> v >> kernel;
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

// DONE by Lidia: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  std::ifstream stream{kProcDirectory + kMeminfoFilename};
  
  std::string line;
  float Memorytotal,Memoryavailable;
  string c;
  if (stream.is_open()){
    getline(stream,line);
    std::istringstream linestream(line);
    linestream>>c>>Memorytotal;
    getline(stream,line);
    getline(stream,line);
    linestream.clear();
    linestream.str(line);
    linestream>>c>>Memoryavailable;
    }
  return (Memorytotal-Memoryavailable)/Memorytotal; }

// Done by Lidia: Read and return the system uptime
long LinuxParser::UpTime() {
  std::ifstream file{kProcDirectory + kUptimeFilename};
  std::string line;
  getline(file,line);
  std::istringstream stringstream(line);
  long time1;
  stringstream>>time1; 
  return time1;
  }

// Not necessary?TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// Not necessary?TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// Not necessary?TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// Not necessary?TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// Done by Lidia: Read and return CPU utilization (of the system) 
vector<int> LinuxParser::CpuUtilization() { 
  string line, CPU;
  int values;
  vector<int> result;
  std::ifstream stream{kProcDirectory + kStatFilename};
  getline(stream,line);
  std::istringstream linestream(line);
  linestream>>CPU;
  for (int i=0;i<10;i++){
    linestream>>values;
    result.push_back(values);
  }
  return result;
}

// DONE by me: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  return GetValue<int>("processes",kProcDirectory + kStatFilename);
  }
template <typename T> T LinuxParser::GetValue(std::string value,std::string path){
  std::ifstream stream{path};
  std::string line{""};
  std::istringstream linestream(line);
  std::string name;
  T result;
  while (getline(stream,line)){
  linestream.clear();
  linestream.str(line);
  linestream>>name;
  if (name==value){
    linestream>>result;
    return result;
  }
    
}
  return  result;
}

// DONE by me: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
 return GetValue<int>("procs_running",kProcDirectory + kStatFilename);
}

// DONE by me: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  std::ifstream stream{kProcDirectory + std::to_string(pid) + kCmdlineFilename};
  std::string line;
  getline(stream,line);
  return line; }

// DONE by Lidia: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string result= GetValue<std::string>("VmSize:",kProcDirectory+ std::to_string(pid) + kStatusFilename); 
  int i =stoi(result);
  i=i/1000;
  result=to_string(i);

return result;
} //returns Ram in Megabytes

// DONE by Lidia: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  return GetValue<std::string>("Uid:",kProcDirectory+ std::to_string(pid) + kStatusFilename);
}

// Done by Lidia: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string uid = LinuxParser::Uid(pid);
  std::ifstream file{kPasswordPath};
  string line;
  std::istringstream linestream{""};
  string user,x;
  string uid2;
  while(getline(file,line)){
    std::replace(line.begin(), line.end(), ':', ' ');
    linestream.clear();
    linestream.str(line);
    linestream>>user>>x>>uid2;
    if (uid2 == uid) return user;
  }
  return  "";
  }


// Done by Lidia: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  std::ifstream file{ kProcDirectory+ std::to_string(pid) + kStatFilename};
  string line;
  getline(file,line);
  std::istringstream linestream(line);
  string uptime;
  for (int i=0;i<22;i++){
    linestream>>uptime;
  }
 
  
  return stoi(uptime)/sysconf(_SC_CLK_TCK);//return time in seconds
}