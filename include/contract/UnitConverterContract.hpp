#pragma once

#include <string>
#include <vector>

namespace unit_converter {

/// Parses "unit:value", converts to all registered targets, returns display lines.
/// Contract: "2.5 meter = 8.202100 feet" (source unit/value preserved, target 6 decimals).
/// Throws std::invalid_argument on malformed input, non-positive value, or unknown unit.
std::vector<std::string> convertFromInput(const std::string& input);

/// Same as convertFromInput but JSON schema output when format is "json".
std::string convertFromInputAsJson(const std::string& input);

double convert(const std::string& from_unit, double value, const std::string& to_unit);

struct ConvertAllEntry {
    std::string unit;
    double value{0.0};
};

std::vector<ConvertAllEntry> convertAll(const std::string& from_unit, double value);

void registerUnit(const std::string& name, double ratio_to_meter);

/// Loads ratios from JSON or YAML. On missing/invalid file, keeps built-in defaults
/// (1 meter = 3.28084 feet, 1 meter = 1.09361 yard).
void loadConfig(const std::string& path);

double meterToFeetRatio();
double meterToYardRatio();

}  // namespace unit_converter
