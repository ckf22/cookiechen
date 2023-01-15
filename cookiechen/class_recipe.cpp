#include "class_recipe.h"
#include <iostream>
#include <locale>
#include <codecvt>

bool Recipe::init(boost::property_tree::wptree::value_type& _init_, long long int _id){
  this->name = _init_.first;
  this->id = _id;
  boost::property_tree::wptree _init = _init_.second;
  this->describtion = _init.get<std::wstring>(L"describtion");
  this->categorys = {};
  for(auto& it : _init.get_child(L"categorys")){
    this->categorys.push_back(it.second.data());
  }
  this->ingredients = {};
  for(auto& it : _init.get_child(L"ingredients")){
    this->ingredients.push_back( { it.first, it.second.get<std::wstring>(L"unit"),
                                  it.second.get<long>(L"unit_counter") } );
  }
  this->preparation = {};
  for(auto& it: _init.get_child(L"preparation")){
    this->preparation.push_back(it.second.data());
  }
  return true;
}

void Recipe::get_tree(std::pair<std::string,boost::property_tree::ptree> * out_){
  using convert_type = std::codecvt_utf8<wchar_t>;
  std::wstring_convert<convert_type, wchar_t> c;

  out_->first = c.to_bytes(this->name);
  boost::property_tree::ptree out;
  out.put("describtion", c.to_bytes(this->describtion));
  boost::property_tree::ptree _categorys;
  for (size_t i = 0; i < this->categorys.size(); i++) {
    boost::property_tree::ptree app;
    std::wstring con = this->categorys[i];
    app.put("", c.to_bytes(con));
    _categorys.push_back(std::make_pair("",app));
  }
  out.add_child("categorys",_categorys);
  boost::property_tree::ptree _ingredients;
  for (long i = 0; i < this->ingredients.size(); i++) {
    boost::property_tree::ptree app;
    app.put("unit", c.to_bytes(this->ingredients[i].unit));
    app.put("unit_counter", this->ingredients[i].unit_counter);
    _ingredients.add_child(c.to_bytes(this->ingredients[i].name), app);
  }
  out.add_child("ingredients", _ingredients);
  boost::property_tree::ptree _preparation;
  for (size_t i = 0; i < this->preparation.size(); i++) {
    boost::property_tree::ptree app;
    app.put("", c.to_bytes(this->preparation[i]));
    _preparation.push_back(std::make_pair("", app));
  }
  out.add_child("preparation", _preparation);
  out_->second = out;
}
