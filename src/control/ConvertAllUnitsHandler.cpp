#include "control/ConvertAllUnitsHandler.hpp"

#include "domain/LengthConversionService.hpp"

namespace control {

ConvertAllUnitsHandler::ConvertAllUnitsHandler(domain::UnitRegistry& registry,
                                               boundary::ConvertInputParser& parser,
                                               boundary::TableOutputSerializer& serializer)
    : registry_(registry), parser_(parser), serializer_(serializer) {}

ConvertOutput ConvertAllUnitsHandler::handle(const std::string& input) {
    ConvertOutput output;
    boundary::AppError parse_error;
    const auto request = parser_.parse(input, parse_error);
    if (!request) {
        output.error = parse_error;
        return output;
    }

    if (!registry_.find(request->unit)) {
        output.error = {boundary::ErrorCode::InputUnknownUnit, request->unit};
        return output;
    }

    domain::LengthConversionService service(registry_);
    const auto results = service.convertAll(request->unit, request->value);
    output.lines = serializer_.serialize(request->unit, request->value, results);
    output.success = true;
    return output;
}

}  // namespace control
