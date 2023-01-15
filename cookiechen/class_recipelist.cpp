#include "class_recipelist.h"
#include <iostream>

Recipelist::Recipelist(){}
Recipelist::Recipelist(std::string filename){
  this->populate(filename);
}
bool Recipelist::populate(std::string filename){
  FormatIn read;
  return read.read_of_file(filename, &this->recipes );
}
bool Recipelist::save(std::string filename){
  FormatOut write;
  return write.write_to_file(filename, this->recipes);
}
void Recipelist::get_recipes(std::vector<Recipe*>* out){
  *out = {};
  for(auto& it : this->recipes)
      out->push_back(&it);
}
Recipe * Recipelist::recipe_add(Recipe& app){
  app.id = next_id;
  ++this->next_id;
  this->recipes.push_back(app);
  return &this->recipes[this->recipes.size()-1];
}
void Recipelist::recipes_add(std::vector<Recipe>& app){
  for (size_t i = 0; i < app.size(); i++) {
    app[i].id = next_id;
    ++next_id;
    this->recipes.push_back(app[i]);
  }
}
bool Recipelist::get_recipe(long long int id, Recipe * out){
  for (size_t i = 0; i < this->recipes.size(); i++) {
    if (this->recipes[i].id == id){
      *out = this->recipes[i];
      return true;
    }
  }
  return false;
}
bool Recipelist::recipe_change(long long int _id, Recipe& new_recipe){
  for (size_t i = 0; i < this->recipes.size(); i++) {
    if(this->recipes[i].id == _id){
      new_recipe.id = this->recipes[i].id;
      this->recipes[i] = new_recipe;
      return true;
    }
  }
  return false;
}
bool Recipelist::recipe_remove(long long int id){
  for (size_t i = 0; i < this->recipes.size(); i++) {
    if(this->recipes[i].id == id){
      this->recipes.erase(this->recipes.begin()+i);
      return true;
    }
  }
  return false;
}
std::vector<Recipe*>* Recipelist::find(std::wstring word){
  bool findet = false;
  this->find_list = {};
  if (word == L"") {
    for(auto& it : this->recipes)
      this->find_list.push_back( &it );
    return &this->find_list;
  }
  for (size_t i = 0; i < this->recipes.size(); i++) {
    if( this->recipes[i].name.find(word) != std::string::npos ){
      this->find_list.push_back( &this->recipes[i] );
      findet = true;
    }
    if (findet == false) {
      for (size_t j = 0; j < this->recipes[i].categorys.size(); j++) {
        if(this->recipes[i].categorys[j].find(word) != std::string::npos){
          this->find_list.push_back( &this->recipes[i] );
          break;
        }
      }
    }
    findet = false;
  }
  return &this->find_list;
}
Recipe& Recipelist::get_recipe(long long int id, bool * state){
  Recipe * recipe;
  *state = this->get_recipe(id, recipe);
  return *recipe;
}
std::vector<Recipe*>* Recipelist::get_all_recipes(){
    this->find_list = {};
    for(auto& it : this->recipes)
        this->find_list.push_back(&it);
    return &this->find_list;
}
void Recipelist::get_id(std::wstring _name, std::vector<Recipe>* write){
  for (size_t i = 0; i < this->recipes.size(); i++) {
    if (this->recipes[i].name == _name){
      write->push_back(this->recipes[i]);
    }
  }
}
