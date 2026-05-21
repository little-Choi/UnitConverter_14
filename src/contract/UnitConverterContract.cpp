#include "contract/UnitConverterContract.hpp"

#include "boundary/ConvertInputParser.hpp"
#include "boundary/JsonOutputSerializer.hpp"
#include "boundary/TableOutputSerializer.hpp"
#include "control/ConvertAllUnitsHandler.hpp"
#include "domain/LengthConversionService.hpp"
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

std::string convertFromInputAsJson(const std::string& input) {
    auto registry = domain::UnitRegistry::bootstrapDefault();
    boundary::ConvertInputParser parser;
    boundary::JsonOutputSerializer serializer;

    boundary::AppError parse_error;
    const auto request = parser.parse(input, parse_error);
    if (!request) {
        throw std::invalid_argument(parse_error.message);
    }

    if (!registry.find(request->unit)) {
        throw std::invalid_argument(request->unit);
    }

    domain::LengthConversionService service(registry);
    const auto results = service.convertAll(request->unit, request->value);
    return serializer.serialize(request->unit, request->value, results);
}

}  // namespace unit_converter
