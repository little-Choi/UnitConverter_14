#include "domain/LengthConversionService.hpp"

#include <cmath>
#include <stdexcept>

namespace domain {

LengthConversionService::LengthConversionService(const UnitRegistry& registry) : registry_(registry) {}

double LengthConversionService::convert(const std::string& source_symbol, double source_value,
                                        const std::string& target_symbol) const {
    const auto source = registry_.find(source_symbol);
    const auto target = registry_.find(target_symbol);
    if (!source || !target) {
        throw std::invalid_argument("Unknown unit in conversion");
    }
    const double meter_value = source_value * source->meters_per_unit;
    return meter_value / target->meters_per_unit;
}

std::vector<LengthConversionService::ConversionResult> LengthConversionService::convertAll(
    const std::string& source_symbol, double source_value) const {
    std::vector<ConversionResult> results;
    results.reserve(registry_.size());
    for (const auto& unit : registry_.units()) {
        results.push_back(ConversionResult{
            unit.symbol,
            convert(source_symbol, source_value, unit.symbol),
        });
    }
    return results;
}

}  // namespace domain
