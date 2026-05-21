#pragma once

#include "boundary/ErrorCodes.hpp"

#include <optional>
#include <string>

namespace boundary {

struct RegisterRequest {
    std::string symbol;
    double meters_per_unit{0.0};
};

class RegisterInputParser {
public:
    std::optional<RegisterRequest> parse(const std::string& input, AppError& error) const;
};

}  // namespace boundary
