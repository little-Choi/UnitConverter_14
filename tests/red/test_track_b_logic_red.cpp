#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "contract/UnitConverterContract.hpp"

// Track B — Domain / Logic (LengthConversionService, UnitRegistry, ConfigLoader)

TEST_CASE("TC-B-01 LengthConversionService_convert_meter_to_feet_within_1e_5", "[red][domain]") {
    // Given: default registry (meter hub), source = 2.5 meter (test_plan D-01, README TC-B-01)
    // When: convert meter to feet via contract API
    const double result = unit_converter::convert("meter", 2.5, "feet");

    // Then: 2.5 * 3.28084 = 8.20210 (domain raw double, ε = 1e-5)
    REQUIRE(result == Catch::Approx(8.20210).margin(1e-5));
}

TEST_CASE("TC-B-02 LengthConversionService_convert_meter_to_yard_within_1e_5", "[red][domain]") {
    // Given: default registry (meter hub), source = 1.0 meter (README TC-B-02)
    // When: convert meter to yard via contract API
    const double result = unit_converter::convert("meter", 1.0, "yard");

    // Then: 1.0 * 1.09361 = 1.09361 (domain raw double, ε = 1e-5)
    REQUIRE(result == Catch::Approx(1.09361).margin(1e-5));
}

TEST_CASE("TC-B-03 LengthConversionService_convert_feet_to_meter_within_1e_5", "[red][domain]") {
    // Given: default registry (meter hub), source = 1.0 feet (README TC-B-03, 역변환)
    // When: convert feet to meter via contract API
    const double result = unit_converter::convert("feet", 1.0, "meter");

    // Then: 1.0 / 3.28084 = 0.30480 (domain raw double, ε = 1e-5)
    REQUIRE(result == Catch::Approx(0.30480).margin(1e-5));
}

TEST_CASE("TC-B-04 convertAll_meter_returns_all_registered_units", "[red][domain]") {
    // Given: default registry (meter, feet, yard) — README TC-B-04
    // When: convertAll from meter:1.0
    const auto results = unit_converter::convertAll("meter", 1.0);

    // Then: one entry per registered unit with hub conversions (ε = 1e-5)
    REQUIRE(results.size() == 3);

    std::size_t matched = 0;
    for (const auto& entry : results) {
        if (entry.unit == "meter") {
            REQUIRE(entry.value == Catch::Approx(1.0).margin(1e-5));
            ++matched;
        } else if (entry.unit == "feet") {
            REQUIRE(entry.value == Catch::Approx(3.28084).margin(1e-5));
            ++matched;
        } else if (entry.unit == "yard") {
            REQUIRE(entry.value == Catch::Approx(1.09361).margin(1e-5));
            ++matched;
        }
    }
    REQUIRE(matched == 3);
}

TEST_CASE("TC-B-05 UnitRegistry_register_unit_cubit_then_convert", "[red][domain]") {
    // Given: default registry, register cubit (README TC-B-05, DEF-015)
    unit_converter::registerUnit("cubit", 0.4572);

    // When: convert 1 cubit to meter via contract API
    const double result = unit_converter::convert("cubit", 1.0, "meter");

    // Then: 1 cubit = 0.4572 meter (domain raw double, ε = 1e-5)
    REQUIRE(result == Catch::Approx(0.4572).margin(1e-5));
}

TEST_CASE("TC-B-06 ConfigLoader_load_config_valid_path_applies_ratios", "[red][domain]") {
    // Given: valid units_valid.json (README TC-B-06 — feet 0.3048 m per unit)
#ifdef UNIT_CONVERTER_TEST_FIXTURE_DIR
    const std::string path = std::string(UNIT_CONVERTER_TEST_FIXTURE_DIR) + "/units_valid.json";
#else
    const std::string path = "tests/fixtures/units_valid.json";
#endif

    // When: loadConfig then convert meter to feet
    unit_converter::loadConfig(path);
    const double result = unit_converter::convert("meter", 2.5, "feet");

    // Then: config ratio (2.5 m = 2.5/0.3048 ft), not default 8.20210
    REQUIRE(result == Catch::Approx(2.5 / 0.3048).margin(1e-5));
}

TEST_CASE("TC-B-07 ConfigLoader_load_config_missing_path_keeps_default_ratios", "[red][domain]") {
    // Given: non-default config loaded, then missing path (README TC-B-07)
#ifdef UNIT_CONVERTER_TEST_FIXTURE_DIR
    const std::string custom_path =
        std::string(UNIT_CONVERTER_TEST_FIXTURE_DIR) + "/units_non_default.json";
    const std::string missing_path =
        std::string(UNIT_CONVERTER_TEST_FIXTURE_DIR) + "/units_does_not_exist.json";
#else
    const std::string custom_path = "tests/fixtures/units_non_default.json";
    const std::string missing_path = "tests/fixtures/units_does_not_exist.json";
#endif
    unit_converter::loadConfig(custom_path);
    REQUIRE(unit_converter::convert("meter", 1.0, "feet") == Catch::Approx(2.0).margin(1e-5));

    // When: loadConfig on missing path
    unit_converter::loadConfig(missing_path);
    const double feet_result = unit_converter::convert("meter", 1.0, "feet");
    const double yard_result = unit_converter::convert("meter", 1.0, "yard");

    // Then: built-in defaults 3.28084 / 1.09361 (ε = 1e-5)
    REQUIRE(feet_result == Catch::Approx(3.28084).margin(1e-5));
    REQUIRE(yard_result == Catch::Approx(1.09361).margin(1e-5));
}
