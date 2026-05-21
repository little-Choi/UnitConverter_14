#include <catch2/catch_test_macros.hpp>

#include "contract/UnitConverterContract.hpp"

// Track A — UI / Boundary (ConvertInputParser, ConvertAllUnitsHandler, TableOutputSerializer, JsonOutputSerializer)

TEST_CASE("TC-A-01 convert_from_input_meter_colon_25_returns_conversion_lines", "[red][boundary]") {
    // Given: meter:2.5, default registry (meter, feet, yard)
    // When: convertFromInput
    const auto lines = unit_converter::convertFromInput("meter:2.5");

    // Then: table golden lines (source preserved, target half-up 1 decimal)
    REQUIRE(lines.size() == 3);
    REQUIRE(lines[0] == "2.5 meter = 2.5 meter");
    REQUIRE(lines[1] == "2.5 meter = 8.2 feet");
    REQUIRE(lines[2] == "2.5 meter = 2.7 yard");
}

TEST_CASE("TC-A-02 convert_from_input_without_colon_throws_invalid_argument", "[red][boundary]") {
    FAIL("RED");
}

TEST_CASE("TC-A-03 convert_from_input_negative_value_throws_invalid_argument", "[red][boundary]") {
    FAIL("RED");
}

TEST_CASE("TC-A-04 convert_from_input_unknown_unit_throws_invalid_argument", "[red][boundary]") {
    FAIL("RED");
}

TEST_CASE("TC-A-05 table_output_preserves_source_unit_and_value", "[red][boundary]") {
    FAIL("RED");
}

TEST_CASE("TC-A-06 json_output_matches_schema", "[red][boundary]") {
    FAIL("RED");
}

TEST_CASE("TC-A-07 convert_from_input_zero_value_throws_invalid_argument", "[red][boundary]") {
    FAIL("RED");
}
