#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>

#ifndef CLASS_RECIPE
#define CLASS_RECIPE


class Recipe{
public:
  struct Ingredient{
    std::wstring name;
    std::wstring unit;
    long unit_counter;
  };
  struct pair{
    std::wstring key;
    std::wstring value;
  };
  bool init(boost::property_tree::wptree::value_type& _init, long long int _id);
  void get_tree(std::pair<std::string,boost::property_tree::ptree> * out);
  std::wstring name;
  std::wstring describtion;
  std::vector<Ingredient> ingredients;
  std::vector<std::wstring> preparation;
  long long int id;
  std::vector<std::wstring> categorys = {L""};
};

#endif
