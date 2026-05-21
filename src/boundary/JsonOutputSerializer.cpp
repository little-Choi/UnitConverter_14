#include "boundary/JsonOutputSerializer.hpp"

#include "boundary/TableOutputSerializer.hpp"

#include <sstream>

namespace boundary {

std::string JsonOutputSerializer::serialize(
    const std::string& source_unit, double source_value,
    const std::vector<domain::LengthConversionService::ConversionResult>& results) const {
    std::ostringstream json;
    json << "{\n";
    json << "  \"source\": { \"unit\": \"" << source_unit << "\", \"value\": "
         << TableOutputSerializer::formatDisplayValue(source_value) << " },\n";
    json << "  \"conversions\": [\n";
    for (std::size_t i = 0; i < results.size(); ++i) {
        const auto& result = results[i];
        json << "    { \"unit\": \"" << result.target_symbol << "\", \"value\": "
             << TableOutputSerializer::formatDisplayValue(result.raw_value) << " }";
        if (i + 1 < results.size()) {
            json << ',';
        }
        json << '\n';
    }
    json << "  ]\n";
    json << '}';
    return json.str();
}

}  // namespace boundary
