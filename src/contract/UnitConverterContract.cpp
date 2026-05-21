#include "contract/UnitConverterContract.hpp"

#include "boundary/ConvertInputParser.hpp"
#include "boundary/JsonOutputSerializer.hpp"
#include "boundary/TableOutputSerializer.hpp"
#include "control/ConvertAllUnitsHandler.hpp"
#include "data/ConfigLoader.hpp"
#include "domain/LengthConversionService.hpp"
#include "domain/UnitRegistry.hpp"

#include <optional>
#include <stdexcept>
#include <vector>

namespace unit_converter {

namespace {

std::vector<domain::UnitDefinition> g_pending_registrations;
std::optional<std::vector<domain::UnitDefinition>> g_config_units;

domain::UnitRegistry registryWithPending() {
    if (g_config_units) {
        domain::UnitRegistry registry;
        registry.loadFromDefinitions(*g_config_units);
        for (const auto& unit : g_pending_registrations) {
            registry.registerUnit(unit.symbol, unit.meters_per_unit);
        }
        g_pending_registrations.clear();
        return registry;
    }
    auto registry = domain::UnitRegistry::bootstrapDefault();
    for (const auto& unit : g_pending_registrations) {
        registry.registerUnit(unit.symbol, unit.meters_per_unit);
    }
    g_pending_registrations.clear();
    return registry;
}

}  // namespace

std::vector<std::string> convertFromInput(const std::string& input) {
    auto registry = domain::UnitRegistry::bootstrapDefault();
    boundary::ConvertInputParser parser;
    boundary::TableOutputSerializer serializer;
    control::ConvertAllUnitsHandler handler(registry, parser, serializer);

    const auto output = handler.handle(input);
    if (!output.success) {
        throw std::invalid_argument(output.error.message);
    }
    return output.lines;
}

std::string convertFromInputAsJson(const std::string& input) {
    auto registry = domain::UnitRegistry::bootstrapDefault();
    boundary::ConvertInputParser parser;
    boundary::JsonOutputSerializer serializer;

    boundary::AppError parse_error;
    const auto request = parser.parse(input, parse_error);
    if (!request) {
        throw std::invalid_argument(parse_error.message);
    }

    if (!registry.find(request->unit)) {
        throw std::invalid_argument(request->unit);
    }

    domain::LengthConversionService service(registry);
    const auto results = service.convertAll(request->unit, request->value);
    return serializer.serialize(request->unit, request->value, results);
}

void registerUnit(const std::string& name, double ratio_to_meter) {
    g_pending_registrations.push_back(domain::UnitDefinition{name, ratio_to_meter});
}

double convert(const std::string& from_unit, double value, const std::string& to_unit) {
    auto registry = registryWithPending();
    domain::LengthConversionService service(registry);
    return service.convert(from_unit, value, to_unit);
}

std::vector<ConvertAllEntry> convertAll(const std::string& from_unit, double value) {
    auto registry = domain::UnitRegistry::bootstrapDefault();
    domain::LengthConversionService service(registry);
    const auto results = service.convertAll(from_unit, value);
    std::vector<ConvertAllEntry> entries;
    entries.reserve(results.size());
    for (const auto& result : results) {
        entries.push_back(ConvertAllEntry{result.target_symbol, result.raw_value});
    }
    return entries;
}

void loadConfig(const std::string& path) {
    boundary::AppError error;
    data::JsonConfigLoader json_loader;
    if (const auto snapshot = json_loader.loadFromFile(path, error)) {
        g_config_units = snapshot->units;
        return;
    }
    data::YamlConfigLoader yaml_loader;
    if (const auto snapshot = yaml_loader.loadFromFile(path, error)) {
        g_config_units = snapshot->units;
    }
}

}  // namespace unit_converter
