#include "class_log.h"
#include <ctime>

Log::Log(std::string filename){
  this->open(filename);
}

Log::Log(){}

std::string Log::opend_file(){
  return this->opend_file_;
}

bool Log::open(std::string filename){
  this->file.open(filename, std::ofstream::out | std::ofstream::app);
  if(!this->file)
    return false;
  this->opend = true;
  this->opend_file_ = filename;
  return true;
}

bool Log::close(){
  if(this->opend == true){
    this->opend = false;
    this->file.close();
    return true;
  }
  return false;
}

bool Log::log(Log_type log_type, std::string log_message){
  if(this->opend == false)
    return false;

  time_t now = time(0);
  std::string time = "  [";
  time += ctime(&now);
  time += "]";
  time.erase( ( time.begin()+time.size() ) - 2 );
  this->file << this->Log_type_names[ static_cast< int >( log_type ) ] << " : \""
             << log_message << "\"" << time << std::endl;

  if(log_type == fatal_error || log_type == error || log_type == warning)
    std::cout << this->Log_type_names[ static_cast< int >( log_type ) ] << " : \""
              << log_message << "\"" << time << std::endl;
  return true;
}

bool Log::log(Log_type log_type, unsigned long line, std::string filename, std::string log_message){
  if(this->opend == false)
    return false;

  time_t now = time(0);
  std::string time = "  [";
  time += ctime(&now);
  time += "]";
  time.erase( ( time.begin()+time.size() ) - 2 );
  this->file << this->Log_type_names[ static_cast< int >( log_type ) ] << " : \""
             << log_message << "\"  [" << filename << "] line " << std::to_string(line) << time << std::endl;

  if(log_type == fatal_error || log_type == error || log_type == warning)
    std::cout << this->Log_type_names[ static_cast< int >( log_type ) ] << " : \""
              << log_message << "\"  [" << filename << "] line " << std::to_string(line) << time << std::endl;
  return true;
}

bool& Log::operator!(){
  bool * ret;
  *ret = !this->opend;
  return *ret;
}
