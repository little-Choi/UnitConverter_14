#pragma once

#include "domain/UnitRegistry.hpp"

#include <string>

namespace domain {

class LengthConversionService {
public:
    explicit LengthConversionService(const UnitRegistry& registry);

    double convert(const std::string& source_symbol, double source_value,
                   const std::string& target_symbol) const;

    struct ConversionResult {
        std::string target_symbol;
        double raw_value{0.0};
    };

    std::vector<ConversionResult> convertAll(const std::string& source_symbol,
                                             double source_value) const;

private:
    const UnitRegistry& registry_;
};

}  // namespace domain
