#include "control/RegisterUnitHandler.hpp"

namespace control {

RegisterUnitHandler::RegisterUnitHandler(domain::UnitRegistry& registry,
                                         boundary::RegisterInputParser& parser)
    : registry_(registry), parser_(parser) {}

RegisterOutput RegisterUnitHandler::handle(const std::string& input) {
    RegisterOutput output;
    boundary::AppError parse_error;
    const auto request = parser_.parse(input, parse_error);
    if (!request) {
        output.error = parse_error;
        return output;
    }

    if (registry_.find(request->symbol)) {
        output.error = {boundary::ErrorCode::InputDuplicateRegister, request->symbol};
        return output;
    }

    if (!registry_.registerUnit(request->symbol, request->meters_per_unit)) {
        output.error = {boundary::ErrorCode::InputInvalidFactor, request->symbol};
        return output;
    }

    output.success = true;
    return output;
}

}  // namespace control
