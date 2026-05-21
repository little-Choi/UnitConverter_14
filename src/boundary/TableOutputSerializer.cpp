#include "boundary/TableOutputSerializer.hpp"

#include <cmath>
#include <sstream>
#include <iomanip>

namespace boundary {

namespace {
double roundHalfUpOneDecimal(double value) {
    return std::round(value * 10.0) / 10.0;
}
}  // namespace

std::string TableOutputSerializer::formatDisplayValue(double raw_value) {
    const double rounded = roundHalfUpOneDecimal(raw_value);
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1) << rounded;
    std::string text = oss.str();
    if (text.find('.') != std::string::npos) {
        while (!text.empty() && text.back() == '0') {
            text.pop_back();
        }
        if (!text.empty() && text.back() == '.') {
            text.pop_back();
        }
    }
    return text;
}

std::vector<std::string> TableOutputSerializer::serialize(
    const std::string& source_unit, double source_value,
    const std::vector<domain::LengthConversionService::ConversionResult>& results) const {
    std::vector<std::string> lines;
    lines.reserve(results.size());
    const std::string source_text = formatDisplayValue(source_value);
    for (const auto& result : results) {
        std::ostringstream line;
        line << source_text << ' ' << source_unit << " = "
             << formatDisplayValue(result.raw_value) << ' ' << result.target_symbol;
        lines.push_back(line.str());
    }
    return lines;
}

}  // namespace boundary
