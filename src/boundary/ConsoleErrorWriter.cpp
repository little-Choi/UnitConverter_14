#include "boundary/ConsoleErrorWriter.hpp"

#include <iostream>

namespace boundary {

void writeAppError(std::ostream& out, const AppError& error) {
    out << errorCodeToPrefix(error.code) << ' ' << error.message << '\n';
}

void writeAppErrorToStderr(const AppError& error) {
    writeAppError(std::cerr, error);
}

}  // namespace boundary
