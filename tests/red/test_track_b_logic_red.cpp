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

TEST_CASE("TC-B-04 UnitRegistry_register_unit_then_convert", "[red][domain]") {
    FAIL("RED");
}

TEST_CASE("TC-B-05 ConfigLoader_load_config_valid_path_applies_ratios", "[red][domain]") {
    FAIL("RED");
}

TEST_CASE("TC-B-06 ConfigLoader_load_config_missing_path_keeps_default_ratios", "[red][domain]") {
    FAIL("RED");
}
