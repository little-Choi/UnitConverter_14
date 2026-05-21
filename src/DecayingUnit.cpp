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

void DecayingUnit::registerUnit(const std::string& name, double meters_per_unit) {
    (void)name;
    (void)meters_per_unit;
    // RED stub — not implemented
}

double DecayingUnit::convert(const std::string& from_unit, double value,
                             const std::string& to_unit) const {
    (void)from_unit;
    (void)value;
    (void)to_unit;
    return 0.0;  // RED stub — forces test failure
}

std::vector<DecayingUnit::ConvertAllEntry> DecayingUnit::convertAll(const std::string& from_unit,
                                                                    double value) const {
    (void)from_unit;
    (void)value;
    return {};  // RED stub — forces test failure
}
