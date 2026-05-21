#pragma once

#include <string>

namespace boundary {

enum class ErrorCode {
    None,
    InputFormat,
    InputNegative,
    InputUnknownUnit,
    InputInvalidFactor,
    InputDuplicateRegister,
    ConfigLoad,
    ConfigSchema
};

std::string errorCodeToPrefix(ErrorCode code);

struct AppError {
    ErrorCode code{ErrorCode::None};
    std::string message;
};

}  // namespace boundary
