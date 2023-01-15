#include "class_format_in-out.h"
#include "class_recipe.h"

#ifndef CLASS_RECIPELIST
#define CLASS_RECIPELIST


class Recipelist{
public:
  Recipelist();
  Recipelist(std::string filename);
  bool populate(std::string filename);
  bool save(std::string filename);
  void get_recipes(std::vector<Recipe*>* out);
  Recipe* recipe_add(Recipe& app);
  void recipes_add(std::vector<Recipe>& app);
  bool recipe_change(long long int id, Recipe& new_recipe);
  bool recipe_remove(long long int id);
  std::vector<Recipe*>* get_all_recipes();
  std::vector<Recipe*>* find(std::wstring word);
  bool get_recipe(long long int id, Recipe * out);
  Recipe& get_recipe(long long int id, bool * state);
  void get_id(std::wstring _name, std::vector<Recipe>* write);
private:
  long long int next_id = 0;
  std::vector<Recipe> recipes;
  std::vector<Recipe*> find_list;
};

#endif
