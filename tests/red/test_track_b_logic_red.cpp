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
    FAIL("RED");
}

TEST_CASE("TC-B-03 LengthConversionService_convert_all_returns_every_registered_unit", "[red][domain]") {
    FAIL("RED");
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
