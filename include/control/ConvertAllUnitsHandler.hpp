#pragma once

#include "boundary/ConvertInputParser.hpp"
#include "boundary/ErrorCodes.hpp"
#include "boundary/TableOutputSerializer.hpp"
#include "domain/LengthConversionService.hpp"
#include "domain/UnitRegistry.hpp"

#include <string>
#include <vector>

namespace control {

struct ConvertOutput {
    bool success{false};
    std::vector<std::string> lines;
    boundary::AppError error;
};

class ConvertAllUnitsHandler {
public:
    ConvertAllUnitsHandler(domain::UnitRegistry& registry,
                           boundary::ConvertInputParser& parser,
                           boundary::TableOutputSerializer& serializer);

    ConvertOutput handle(const std::string& input);

private:
    domain::UnitRegistry& registry_;
    boundary::ConvertInputParser& parser_;
    boundary::TableOutputSerializer& serializer_;
};

}  // namespace control
