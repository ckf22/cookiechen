#include "class_recipelist.h"
#include "class_format_in-out.h"
#include "class_log.h"
#include "class_config.cpp"
#include <QString>
#include <string>
#include <vector>

#ifndef CLASS_HANDLER_H
#define CLASS_HANDLER_H

class Handler{
public:
    Handler(Log * _log);
    bool open_file(std::string filename);
    std::vector<std::string>& get_all_recipes_name(std::wstring find);
    void save(std::string filename);
    bool delRecipe(long long int id);
    Recipe * addRecipe(Recipe _recipe);
    std::vector<Recipe*>* get_all_recipes();
    std::string opend_file;
    std::vector<Recipe*>* find_list;
private:
    std::vector<std::string> find_list_names;
    Log * log;
    Config config;
    Recipelist recipes;
    FormatIn read;
    FormatOut write;
};

#endif // CLASS_HANDLER_H
