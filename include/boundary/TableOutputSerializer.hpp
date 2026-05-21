#pragma once

#include "domain/LengthConversionService.hpp"

#include <string>
#include <vector>

namespace boundary {

class TableOutputSerializer {
public:
    std::vector<std::string> serialize(const std::string& source_unit, double source_value,
                                       const std::vector<domain::LengthConversionService::ConversionResult>& results) const;

    static std::string formatDisplayValue(double raw_value);
};

}  // namespace boundary
