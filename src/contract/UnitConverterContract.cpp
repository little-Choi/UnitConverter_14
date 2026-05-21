#include "contract/UnitConverterContract.hpp"

#include "boundary/ConvertInputParser.hpp"
#include "boundary/TableOutputSerializer.hpp"
#include "control/ConvertAllUnitsHandler.hpp"
#include "domain/UnitRegistry.hpp"

#include <stdexcept>

namespace unit_converter {

std::vector<std::string> convertFromInput(const std::string& input) {
    auto registry = domain::UnitRegistry::bootstrapDefault();
    boundary::ConvertInputParser parser;
    boundary::TableOutputSerializer serializer;
    control::ConvertAllUnitsHandler handler(registry, parser, serializer);

    const auto output = handler.handle(input);
    if (!output.success) {
        throw std::invalid_argument(output.error.message);
    }
    return output.lines;
}

}  // namespace unit_converter
