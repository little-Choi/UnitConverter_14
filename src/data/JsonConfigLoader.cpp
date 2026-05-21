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

std::vector<domain::UnitDefinition> parseUnitsArray(const std::string& content) {
    std::vector<domain::UnitDefinition> units;
    const std::regex unit_block(
        R"json(\{\s*"symbol"\s*:\s*"([a-z0-9_]+)"\s*,\s*"meters_per_unit"\s*:\s*([0-9]+(?:\.[0-9]+)?)\s*\})json");
    auto begin = std::sregex_iterator(content.begin(), content.end(), unit_block);
    auto end = std::sregex_iterator();
    for (auto it = begin; it != end; ++it) {
        const double factor = std::stod((*it)[2].str());
        if (factor <= 0.0) {
            return {};
        }
        units.push_back(domain::UnitDefinition{(*it)[1].str(), factor});
    }
    return units;
}

}  // namespace

std::optional<ConfigSnapshot> JsonConfigLoader::loadFromFile(const std::string& path,
                                                             boundary::AppError& error) const {
    std::ifstream file(path);
    if (!file.is_open()) {
        error = {boundary::ErrorCode::ConfigLoad, path};
        return std::nullopt;
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    const std::string content = buffer.str();

    if (content.find("\"base_unit\"") == std::string::npos ||
        content.find("\"meter\"") == std::string::npos) {
        error = {boundary::ErrorCode::ConfigSchema, "missing base_unit meter"};
        return std::nullopt;
    }

    const auto units = parseUnitsArray(content);
    if (units.empty() || !hasMeterBase(units)) {
        error = {boundary::ErrorCode::ConfigSchema, "invalid units schema"};
        return std::nullopt;
    }

    return ConfigSnapshot{units};
}

}  // namespace data
