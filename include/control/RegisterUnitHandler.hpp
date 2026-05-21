#pragma once

#include "boundary/ErrorCodes.hpp"
#include "boundary/RegisterInputParser.hpp"
#include "domain/UnitRegistry.hpp"

#include <string>

namespace control {

struct RegisterOutput {
    bool success{false};
    boundary::AppError error;
};

class RegisterUnitHandler {
public:
    RegisterUnitHandler(domain::UnitRegistry& registry, boundary::RegisterInputParser& parser);

    RegisterOutput handle(const std::string& input);

private:
    domain::UnitRegistry& registry_;
    boundary::RegisterInputParser& parser_;
};

}  // namespace control
