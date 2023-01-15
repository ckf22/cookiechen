#include "class_recipe.h"
#include <string>
#include <vector>

#ifndef CLASS_FORMAT_IN_OUT
#define CLASS_FORMAT_IN_OUT

class FormatIn{
public:
  bool read_of_file(std::string filename, std::vector<Recipe> * recipes);
};
class FormatOut{
public:
  bool write_to_file(std::string filename, std::vector<Recipe>& recipes);
};

#endif
