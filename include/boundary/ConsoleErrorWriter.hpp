#pragma once

#include "boundary/ErrorCodes.hpp"

#include <iosfwd>

namespace boundary {

void writeAppError(std::ostream& out, const AppError& error);
void writeAppErrorToStderr(const AppError& error);

}  // namespace boundary
