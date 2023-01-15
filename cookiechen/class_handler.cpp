#include "class_handler.h"
#include "class_config.cpp"
#include "class_log.h"
#include "class_recipe.h"
#include <QWidget>
#include <vector>
#include "convert.cpp"
#include <iostream>


Handler::Handler(Log * _log){
    this->log = _log;
    this->find_list = recipes.get_all_recipes();
}

bool Handler::open_file(std::string filename = "../recipe-manager-2/default-data.json"){

    if(!this->recipes.populate( filename ))
            return false;
    this->opend_file = filename;
    return true;
}

std::vector<std::string>& Handler::get_all_recipes_name(std::wstring find){
    this->find_list = this->recipes.find(find);
    this->find_list_names = {};
    for(size_t i = 0; i < this->find_list->size(); ++i)
        this->find_list_names.push_back( convert( this->find_list->operator[](i)->name ) );
    return this->find_list_names;
}

void Handler::save(std::string filename){
    this->recipes.save(filename);
}

Recipe * Handler::addRecipe(Recipe _recipe){
    return recipes.recipe_add(_recipe);
}

bool Handler::delRecipe(long long int id){
    return recipes.recipe_remove(id);
}

std::vector<Recipe*>* Handler::get_all_recipes(){
    this->find_list = recipes.get_all_recipes();
    return this->find_list;
}
