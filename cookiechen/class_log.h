#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#ifndef CLASS_LOG
#define CLASS_LOG


class Log{
public:

  enum Log_type {
    fatal_error = 0,
    error = 1,
    warning = 2,
    debug = 3
  };

  Log(std::string filename);
  Log();
  bool open(std::string filename);
  std::string opend_file();
  bool close();
  bool log(Log_type log_type, std::string log_message);
  bool log(Log_type log_type, unsigned long line, std::string filename, std::string log_message);
  bool& operator!();
private:
  std::ofstream file;
  bool opend = false;
  std::string opend_file_;
  std::vector<std::string> Log_type_names = {"fatal_error","error","warning","debug"};
};

#endif
