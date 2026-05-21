#include "data/ConfigLoader.hpp"

#include <fstream>
#include <regex>
#include <sstream>

namespace data {

namespace {

bool hasMeterBase(const std::vector<domain::UnitDefinition>& units) {
    for (const auto& unit : units) {
        if (unit.symbol == "meter" && unit.meters_per_unit == 1.0) {
            return true;
        }
    }
    return false;
}

}  // namespace

std::optional<ConfigSnapshot> YamlConfigLoader::loadFromFile(const std::string& path,
                                                             boundary::AppError& error) const {
    std::ifstream file(path);
    if (!file.is_open()) {
        error = {boundary::ErrorCode::ConfigLoad, path};
        return std::nullopt;
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    const std::string content = buffer.str();

    if (content.find("base_unit:") == std::string::npos) {
        error = {boundary::ErrorCode::ConfigSchema, "missing base_unit"};
        return std::nullopt;
    }

    std::vector<domain::UnitDefinition> units;
    const std::regex yaml_unit(
        R"(-\s*symbol:\s*([a-z0-9_]+)\s+meters_per_unit:\s*([0-9]+(?:\.[0-9]+)?))");
    auto begin = std::sregex_iterator(content.begin(), content.end(), yaml_unit);
    auto end = std::sregex_iterator();
    for (auto it = begin; it != end; ++it) {
        const double factor = std::stod((*it)[2].str());
        if (factor <= 0.0) {
            error = {boundary::ErrorCode::ConfigSchema, "non-positive meters_per_unit"};
            return std::nullopt;
        }
        units.push_back(domain::UnitDefinition{(*it)[1].str(), factor});
    }

    if (units.empty() || !hasMeterBase(units)) {
        error = {boundary::ErrorCode::ConfigSchema, "invalid yaml units schema"};
        return std::nullopt;
    }

    return ConfigSnapshot{units};
}

}  // namespace data
