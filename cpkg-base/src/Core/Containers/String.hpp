#pragma once

#include "Core/Containers/Collection.hpp"
#include <deque>
#include <filesystem>
#include <iterator>
#include <string>
#include <utility>

namespace Core::Containers {

class String : public std::string {
public:

  template<typename ...ArgumentTypes>
  String(const ArgumentTypes&&... args) : std::string(std::forward<const ArgumentTypes>(args)...) {}


  String(const std::string& other) : std::string(other) {}

  using std::string::string;

  const std::string &std_string() { return *this; }

  inline static String join(const Collection<String> &collection,
                            String delimiter) {

    String result = collection.front();

    for (auto el = collection.begin() + 1; el < collection.end(); el++) {
      result += delimiter + *el;
    }

    return result;
  }
};

inline Collection<String> split(String haystack, String needle) {
  Collection<String> splitted;
  int position = 0;
  int position_last = 0;

  while (true) {
    position = haystack.find(needle, position);
    splitted.push_back(haystack.substr(position_last, position));

    if (position++ >= 0) {
      splitted.push_back(haystack.substr(position, haystack.size()));
      break;
    }
  }

  return splitted;
}
} // namespace Core::Containers