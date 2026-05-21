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

double convert(const std::string& from_unit, double value, const std::string& to_unit) {
    auto registry = domain::UnitRegistry::bootstrapDefault();
    domain::LengthConversionService service(registry);
    return service.convert(from_unit, value, to_unit);
}

std::vector<ConvertAllEntry> convertAll(const std::string& from_unit, double value) {
    auto registry = domain::UnitRegistry::bootstrapDefault();
    domain::LengthConversionService service(registry);
    const auto results = service.convertAll(from_unit, value);
    std::vector<ConvertAllEntry> entries;
    entries.reserve(results.size());
    for (const auto& result : results) {
        entries.push_back(ConvertAllEntry{result.target_symbol, result.raw_value});
    }
    return entries;
}

}  // namespace unit_converter
