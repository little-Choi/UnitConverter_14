#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "data/ConfigLoader.hpp"
#include "domain/LengthConversionService.hpp"
#include "domain/UnitRegistry.hpp"

#include <filesystem>
#include <string>

namespace {
std::string fixturePath(const std::string& name) {
#ifdef UNIT_CONVERTER_TEST_FIXTURE_DIR
    return std::string(UNIT_CONVERTER_TEST_FIXTURE_DIR) + "/" + name;
#else
    return std::string("tests/fixtures/") + name;
#endif
}
}  // namespace

TEST_CASE("test_json_config_valid_loads_three_units", "[data][config]") {
    // Given: valid units_valid.json with meter base
    data::JsonConfigLoader loader;
    boundary::AppError error;

    // When: load file
    const auto snapshot = loader.loadFromFile(fixturePath("units_valid.json"), error);

    // Then: three units loaded
    REQUIRE(snapshot.has_value());
    REQUIRE(snapshot->units.size() == 3);
    REQUIRE(error.code == boundary::ErrorCode::None);
}

TEST_CASE("test_json_config_valid_matches_default_conversion", "[data][config]") {
    // Given: 1 meter = 3.28084 feet from config file
    data::JsonConfigLoader loader;
    boundary::AppError error;
    const auto snapshot = loader.loadFromFile(fixturePath("units_valid.json"), error);
    REQUIRE(snapshot.has_value());

    domain::UnitRegistry registry;
    registry.loadFromDefinitions(snapshot->units);
    domain::LengthConversionService service(registry);

    // When: convert meter:2.5 to feet
    const double result = service.convert("meter", 2.5, "feet");

    // Then: matches config feet factor (1 feet = 0.3048 meter => 2.5 m = 2.5/0.3048 ft)
    REQUIRE(result == Catch::Approx(2.5 / 0.3048).margin(1e-6));
}

TEST_CASE("test_json_config_missing_file_load_error", "[data][config]") {
    // Given: non-existent path
    data::JsonConfigLoader loader;
    boundary::AppError error;

    // When: load missing file
    const auto snapshot = loader.loadFromFile(fixturePath("not_exists_404.json"), error);

    // Then: ERR-CONFIG_LOAD
    REQUIRE_FALSE(snapshot.has_value());
    REQUIRE(error.code == boundary::ErrorCode::ConfigLoad);
    REQUIRE(boundary::errorCodeToPrefix(error.code) == "ERR-CONFIG_LOAD:");
}

TEST_CASE("test_json_config_invalid_schema_no_meter", "[data][config]") {
    // Given: schema without meter unit
    data::JsonConfigLoader loader;
    boundary::AppError error;

    // When: load invalid schema
    const auto snapshot = loader.loadFromFile(fixturePath("units_invalid_schema.json"), error);

    // Then: ERR-CONFIG_SCHEMA
    REQUIRE_FALSE(snapshot.has_value());
    REQUIRE(error.code == boundary::ErrorCode::ConfigSchema);
}

TEST_CASE("test_yaml_config_valid_loads_three_units", "[data][config]") {
    // Given: valid units_valid.yaml
    data::YamlConfigLoader loader;
    boundary::AppError error;

    // When: load yaml
    const auto snapshot = loader.loadFromFile(fixturePath("units_valid.yaml"), error);

    // Then: success with meter base
    REQUIRE(snapshot.has_value());
    REQUIRE(snapshot->units.size() == 3);
}

TEST_CASE("test_yaml_config_missing_file_load_error", "[data][config]") {
    // Given: missing yaml path
    data::YamlConfigLoader loader;
    boundary::AppError error;

    // When: load
    const auto snapshot = loader.loadFromFile(fixturePath("missing_units.yaml"), error);

    // Then: ERR-CONFIG_LOAD
    REQUIRE_FALSE(snapshot.has_value());
    REQUIRE(error.code == boundary::ErrorCode::ConfigLoad);
}
