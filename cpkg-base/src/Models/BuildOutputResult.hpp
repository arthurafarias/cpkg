#pragma once

#include "Models/CompilerCommandDescriptor.hpp"

namespace Models
{
    using BuildOutputResult = std::tuple<int, Collection<CompileCommandDescriptor>>;
}