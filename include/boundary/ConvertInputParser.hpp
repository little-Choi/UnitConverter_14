#pragma once

#include "boundary/ErrorCodes.hpp"

#include <optional>
#include <string>

namespace boundary {

struct ConvertRequest {
    std::string unit;
    double value{0.0};
};

class ConvertInputParser {
public:
    std::optional<ConvertRequest> parse(const std::string& input, AppError& error) const;
};

}  // namespace boundary
