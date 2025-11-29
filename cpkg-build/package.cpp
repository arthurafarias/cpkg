#include <Models/TargetDescriptor.hpp>

auto cpkg_build_target = Models::TargetDescriptor()
    .name_set("cpkg-build")
    .version_set("1.0.0")
    .type_set("executable")
    .dependencies_append({"cpkg-base"})
    .include_directories_append({"src"})
    .sources_append({"src/cpkg-build.cpp"})
    .create();