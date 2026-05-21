#include "boundary/RegisterInputParser.hpp"

#include <regex>

namespace boundary {

namespace {
const std::regex kRegisterPattern(R"(^1\s+([a-z0-9_]+)\s*=\s*(\d+(\.\d+)?)\s+meter$)");
}  // namespace

std::optional<RegisterRequest> RegisterInputParser::parse(const std::string& input,
                                                          AppError& error) const {
    std::smatch match;
    if (!std::regex_match(input, match, kRegisterPattern)) {
        error = {ErrorCode::InputFormat, "invalid register format"};
        return std::nullopt;
    }

    double factor = 0.0;
    try {
        factor = std::stod(match[2].str());
    } catch (...) {
        error = {ErrorCode::InputFormat, "invalid factor"};
        return std::nullopt;
    }

    if (factor <= 0.0) {
        error = {ErrorCode::InputInvalidFactor, match[2].str()};
        return std::nullopt;
    }

    const std::string symbol = match[1].str();
    if (symbol == "meter") {
        error = {ErrorCode::InputInvalidFactor, "cannot redefine meter"};
        return std::nullopt;
    }

    return RegisterRequest{symbol, factor};
}

}  // namespace boundary
