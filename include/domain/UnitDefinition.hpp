#pragma once

#include <string>

namespace domain {

struct UnitDefinition {
    std::string symbol;
    double meters_per_unit{0.0};
};

}  // namespace domain
