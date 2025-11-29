#pragma once

#include "Models/BasicProjectDescriptor.hpp"
#include "Models/BasicTargetDescriptor.hpp"
#include <Controllers/Project.hpp>
#include <Controllers/ToolchainManager.hpp>
#include <Core/Containers/Variant.hpp>
#include <Utils/Print.hpp>

#include <deque>
#include <dlfcn.h>
#include <fstream>
#include <memory>
#include <ostream>

using namespace Core::Containers;

#ifndef CPKG_BUILD_HEADERS_PATH
#define CPKG_BUILD_HEADERS_PATH "./"
#endif

#ifndef CPKG_BUILD_INSTALL_HEADERS_PATH
#define CPKG_BUILD_INSTALL_HEADERS_PATH "/usr/share/cpkg-build/private-headers/"
#endif

#ifndef CPKG_BASE_HEADERS_PATH
#define CPKG_BASE_HEADERS_PATH "./"
#endif

#ifndef CPKG_BASE_INSTALL_HEADERS_PATH
#define CPKG_BASE_INSTALL_HEADERS_PATH "/usr/share/cpkg-base/private-headers/"
#endif

namespace Controllers {

using namespace Models;

inline BasicTargetDescriptor ManifestPackage = {
    .name = "project-manifest",
    .type = "shared-library",
    .dependencies = {"cpkg-base"},
    .include_directories = {CPKG_BUILD_INSTALL_HEADERS_PATH,
                            CPKG_BUILD_HEADERS_PATH, CPKG_BASE_HEADERS_PATH,
                            CPKG_BASE_INSTALL_HEADERS_PATH},
    .sources = {"package.cpp", "package.loader.cpp"},
    .options = {"-std=c++23", "-Wall", "-Werror", "-pedantic"}};

inline const std::string BasicProjectLoaderSource = R"(
#include <Models/BasicProjectDescriptor.hpp>

using namespace Models;

extern BasicProjectDescriptor project;

extern "C" const BasicProjectDescriptor* get_project()  { return &project; }
)";

struct ProjectDescriptor : public BasicProjectDescriptor {
public:
  ProjectDescriptor(const BasicProjectDescriptor &other)
      : BasicProjectDescriptor(other) {}
  ProjectDescriptor(const ProjectDescriptor &) = default;
  ProjectDescriptor(ProjectDescriptor &&) = default;
  ProjectDescriptor &operator=(const ProjectDescriptor &) = delete;
  ProjectDescriptor &operator=(ProjectDescriptor &&) = delete;

  static const std::shared_ptr<ProjectDescriptor>
  load_from_manifest(std::string manifest_path) {
    typedef ProjectDescriptor *(*getter_type)();

    void *handle = dlopen("./project-manifest.so", RTLD_LAZY | RTLD_DEEPBIND);

    if (handle == nullptr) {
      return nullptr;
    }

    auto get_project =
        reinterpret_cast<getter_type>(dlsym(handle, "get_project"));

    if (get_project == nullptr) {
      return nullptr;
    }

    auto _retval = *get_project();

    auto retval = std::make_shared<ProjectDescriptor>(_retval);

    dlclose(handle);

    return retval;
  }

  static int clean(std::string path, std::deque<std::string> extra_paths = {}) {

    // objects
    for (auto source : ManifestPackage.sources) {
      std::filesystem::remove_all(
          std::filesystem::path(path).append(source.std_string()).append(".o"));
    }

    // generate packages
    std::filesystem::remove_all(
        std::filesystem::path(path).append("package.cpp.o"));

    std::filesystem::remove_all(
        std::filesystem::path(path).append("package.loader.cpp.o"));

    std::filesystem::remove_all(
        std::filesystem::path(path).append("package.loader.cpp"));

    return 0;
  }

  static int build_manifest(std::string path,
                            std::deque<std::string> extra_paths = {}) {

    if (__generate_loader(path) != 0) {
      return -1;
    }

    if (Controllers::ToolchainManager::current().build(ManifestPackage) != 0) {
      return -1;
    }

    return 0;
  }

private:
  static int __generate_loader(std::string base_path) {
    std::ofstream loader_source(base_path + "/package.loader.cpp",
                                std::ios_base::trunc | std::ios_base::out);
    loader_source << BasicProjectLoaderSource;
    loader_source.flush();
    return 0;
  }
};

} // namespace Controllers

namespace Utils {
using namespace Controllers;
template <>
inline std::ostream &print<ProjectDescriptor>(std::ostream &os,
                                              ProjectDescriptor project) {
  print(os, "{");

  for (auto pkg : project.targets) {
    print(os, pkg);
  }

  print(os, "}");

  return os;
}
} // namespace Utils