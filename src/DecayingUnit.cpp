#include "DecayingUnit.hpp"

#include <stdexcept>

namespace {

constexpr double kMeterToFeet = 3.28084;
constexpr double kMeterToYard = 1.09361;

}  // namespace

DecayingUnit::DecayingUnit() {
    units_.push_back({"meter", 1.0});
    units_.push_back({"feet", 1.0 / kMeterToFeet});
    units_.push_back({"yard", 1.0 / kMeterToYard});
}

const DecayingUnit::UnitEntry* DecayingUnit::findUnit(const std::string& symbol) const {
    for (const auto& unit : units_) {
        if (unit.symbol == symbol) {
            return &unit;
        }
    }
    return nullptr;
}

void DecayingUnit::registerUnit(const std::string& name, double meters_per_unit) {
    if (meters_per_unit <= 0.0) {
        throw std::invalid_argument("meters_per_unit must be positive");
    }
    for (const auto& unit : units_) {
        if (unit.symbol == name) {
            return;
        }
    }
    units_.push_back({name, meters_per_unit});
}

double DecayingUnit::convert(const std::string& from_unit, double value,
                             const std::string& to_unit) const {
    const UnitEntry* source = findUnit(from_unit);
    const UnitEntry* target = findUnit(to_unit);
    if (!source || !target) {
        throw std::invalid_argument("Unknown unit in conversion");
    }
    const double meter_value = value * source->meters_per_unit;
    return meter_value / target->meters_per_unit;
}

std::vector<DecayingUnit::ConvertAllEntry> DecayingUnit::convertAll(const std::string& from_unit,
                                                                    double value) const {
    std::vector<ConvertAllEntry> results;
    results.reserve(units_.size());
    for (const auto& unit : units_) {
        results.push_back(ConvertAllEntry{
            unit.symbol,
            convert(from_unit, value, unit.symbol),
        });
    }
    return results;
}
