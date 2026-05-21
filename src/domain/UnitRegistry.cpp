#include "domain/UnitRegistry.hpp"

#include <algorithm>

namespace domain {

namespace {
constexpr double kMeterToFeet = 3.28084;
constexpr double kMeterToYard = 1.09361;
}  // namespace

UnitRegistry UnitRegistry::bootstrapDefault() {
    UnitRegistry registry;
    registry.registerUnit("meter", 1.0);
    registry.registerUnit("feet", 1.0 / kMeterToFeet);
    registry.registerUnit("yard", 1.0 / kMeterToYard);
    return registry;
}

bool UnitRegistry::registerUnit(const std::string& symbol, double meters_per_unit) {
    if (symbol.empty() || meters_per_unit <= 0.0) {
        return false;
    }
    for (const auto& unit : units_) {
        if (unit.symbol == symbol) {
            return false;
        }
    }
    units_.push_back(UnitDefinition{symbol, meters_per_unit});
    return true;
}

std::optional<UnitDefinition> UnitRegistry::find(const std::string& symbol) const {
    for (const auto& unit : units_) {
        if (unit.symbol == symbol) {
            return unit;
        }
    }
    return std::nullopt;
}

void UnitRegistry::clear() {
    units_.clear();
}

void UnitRegistry::loadFromDefinitions(const std::vector<UnitDefinition>& definitions) {
    units_ = definitions;
}

}  // namespace domain
