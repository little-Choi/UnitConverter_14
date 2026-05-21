#pragma once

#include "domain/LengthConversionService.hpp"

#include <string>
#include <vector>

namespace boundary {

class JsonOutputSerializer {
public:
    std::string serialize(const std::string& source_unit, double source_value,
                          const std::vector<domain::LengthConversionService::ConversionResult>& results) const;
};

}  // namespace boundary
