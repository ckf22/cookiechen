#include <iostream>
#include <string>
#include <locale>
#include <codecvt>

#ifndef CONVERT_CPP
#define CONVERT_CPP

template<class To, typename From>
std::__cxx11::basic_string<To> convert(std::__cxx11::basic_string<From> from){
  return std::wstring_convert<std::codecvt_utf8<To>,To>{}.from_bytes(std::wstring_convert<std::codecvt_utf8<From>,From>{}.to_bytes(from));
}

template<typename From>
std::string convert(std::__cxx11::basic_string<From> from){
  return std::wstring_convert<std::codecvt_utf8<From>,From>{}.to_bytes(from);
}

template<class To>
std::__cxx11::basic_string<To> convert(std::string from){
  return std::wstring_convert<std::codecvt_utf8<To>,To>{}.from_bytes(from);
}

#endif
