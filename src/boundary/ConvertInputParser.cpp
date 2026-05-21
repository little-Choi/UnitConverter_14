#include "boundary/ConvertInputParser.hpp"

#include <cctype>
#include <regex>
#include <sstream>

namespace boundary {

namespace {
const std::regex kConvertPattern(
    R"(^([a-z0-9_]+):([+-]?[0-9]+(\.[0-9]+)?([eE][+-]?[0-9]+)?)$)");

std::string trim(const std::string& input) {
    std::size_t start = 0;
    while (start < input.size() && std::isspace(static_cast<unsigned char>(input[start]))) {
        ++start;
    }
    std::size_t end = input.size();
    while (end > start && std::isspace(static_cast<unsigned char>(input[end - 1]))) {
        --end;
    }
    return input.substr(start, end - start);
}
}  // namespace

std::optional<ConvertRequest> ConvertInputParser::parse(const std::string& input,
                                                        AppError& error) const {
    const std::string trimmed = trim(input);
    if (trimmed.empty()) {
        error = {ErrorCode::InputFormat, "empty input"};
        return std::nullopt;
    }

    std::smatch match;
    if (!std::regex_match(trimmed, match, kConvertPattern)) {
        error = {ErrorCode::InputFormat, "invalid unit:value format"};
        return std::nullopt;
    }

    double value = 0.0;
    try {
        value = std::stod(match[2].str());
    } catch (...) {
        error = {ErrorCode::InputFormat, "invalid number token"};
        return std::nullopt;
    }

    if (value <= 0.0) {
        error = {ErrorCode::InputNegative, match[2].str()};
        return std::nullopt;
    }

    return ConvertRequest{match[1].str(), value};
}

}  // namespace boundary
