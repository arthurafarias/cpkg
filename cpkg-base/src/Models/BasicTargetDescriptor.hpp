#pragma once

#include <Core/Containers/Collection.hpp>
#include <Core/Containers/String.hpp>

using namespace Core::Containers;
namespace Models {
struct BasicTargetDescriptor {
  String name = "";
  String version = "";
  String type = "";
  String url = "";
  String language = "c++";
  String toolchain = "";
  Collection<String> dependencies;
  Collection<String> include_directories;
  Collection<String> sources;
  Collection<String> options;
  Collection<String> link_libraries;
  Collection<String> link_directories;
};
} // namespace Models