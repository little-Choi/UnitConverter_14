#pragma once

#include "boundary/ErrorCodes.hpp"
#include "domain/UnitDefinition.hpp"

#include <optional>
#include <string>
#include <vector>

namespace data {

struct ConfigSnapshot {
    std::vector<domain::UnitDefinition> units;
};

class JsonConfigLoader {
public:
    std::optional<ConfigSnapshot> loadFromFile(const std::string& path, boundary::AppError& error) const;
};

class YamlConfigLoader {
public:
    std::optional<ConfigSnapshot> loadFromFile(const std::string& path, boundary::AppError& error) const;
};

}  // namespace data
