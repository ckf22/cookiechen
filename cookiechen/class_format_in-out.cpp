#include "class_format_in-out.h"
#include <fstream>
#include <iostream>
#include <locale>
#include "shell_command.cpp"
#include <boost/property_tree/json_parser.hpp>


bool FormatIn::read_of_file(std::string filename, std::vector<Recipe>* recipes){
  *recipes = {};
  namespace json = boost::property_tree;
  std::string buffer = "jsonlint-php " + filename;
  if( shell_command(buffer.c_str()) != "Valid JSON ("+filename+")\n" )
    return false;
  std::wifstream check(filename);
  if(!check)
    return false;
  check.imbue(std::locale("en_US.UTF-8"));
  json::wptree file;
  json::read_json(check, file);
  long long int id = 0;
  for(auto& it : file){
    Recipe push;
    push.init(it, id);
    recipes->push_back(push);
    ++id;
  }
  return true;
}
bool FormatOut::write_to_file(std::string filename, std::vector<Recipe>& recipes){
  std::ofstream check(filename);
  if(!check)
    return false;
  boost::property_tree::ptree write;
  std::pair<std::string,boost::property_tree::ptree> app;
  for (size_t i = 0; i < recipes.size(); i++) {
    recipes[i].get_tree(&app);
    write.push_back(app);
  }
  boost::property_tree::write_json(check, write);
  check.close();
  return true;
}
