#include "boundary/ErrorCodes.hpp"

namespace boundary {

std::string errorCodeToPrefix(ErrorCode code) {
    switch (code) {
        case ErrorCode::InputFormat:
            return "ERR-INPUT_FORMAT:";
        case ErrorCode::InputNegative:
            return "ERR-INPUT_NEGATIVE:";
        case ErrorCode::InputUnknownUnit:
            return "ERR-INPUT_UNKNOWN_UNIT:";
        case ErrorCode::InputInvalidFactor:
            return "ERR-INPUT_INVALID_FACTOR:";
        case ErrorCode::InputDuplicateRegister:
            return "ERR-INPUT_DUPLICATE_REGISTER:";
        case ErrorCode::ConfigLoad:
            return "ERR-CONFIG_LOAD:";
        case ErrorCode::ConfigSchema:
            return "ERR-CONFIG_SCHEMA:";
        default:
            return "";
    }
}

}  // namespace boundary
