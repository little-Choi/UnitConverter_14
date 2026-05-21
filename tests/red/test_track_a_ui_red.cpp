#include <catch2/catch_test_macros.hpp>

#include <stdexcept>

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
    // Given: colon missing (test_plan B-03 meter2.5)
    // When/Then: convertFromInput throws std::invalid_argument
    REQUIRE_THROWS_AS(unit_converter::convertFromInput("meter2.5"), std::invalid_argument);
}

TEST_CASE("TC-A-03 convert_from_input_negative_value_throws_invalid_argument", "[red][boundary]") {
    // Given: POL-NEG policy, negative value (test_plan B-07 meter:-1.0)
    // When/Then: convertFromInput throws std::invalid_argument
    REQUIRE_THROWS_AS(unit_converter::convertFromInput("meter:-1.0"), std::invalid_argument);
}

TEST_CASE("TC-A-04 convert_from_input_unknown_unit_throws_invalid_argument", "[red][boundary]") {
    // Given: bootstrap registry without parsec (test_plan B-04, test_handler_unknown_unit_parsec)
    // When/Then: convertFromInput throws std::invalid_argument
    REQUIRE_THROWS_AS(unit_converter::convertFromInput("parsec:1.0"), std::invalid_argument);
}

TEST_CASE("TC-A-05 table_output_preserves_source_unit_and_value", "[red][boundary]") {
    // Given: non-numeric value token (test_plan B-05, test_parse_abc_number_format_error)
    // When/Then: convertFromInput throws std::invalid_argument
    REQUIRE_THROWS_AS(unit_converter::convertFromInput("meter:abc"), std::invalid_argument);
}

TEST_CASE("TC-A-06 json_output_matches_schema", "[red][boundary]") {
    // Given: meter:2.5, default registry (test_plan B-10, PRD §6.2 OUT-03)
    // When: convertFromInputAsJson
    const auto json = unit_converter::convertFromInputAsJson("meter:2.5");

    // Then: JSON schema — source preserved; conversions length = Registry.size(); half-up targets
    const std::string expected = R"({
  "source": { "unit": "meter", "value": 2.5 },
  "conversions": [
    { "unit": "meter", "value": 2.5 },
    { "unit": "feet", "value": 8.2 },
    { "unit": "yard", "value": 2.7 }
  ]
})";
    REQUIRE(json == expected);
}

TEST_CASE("TC-A-07 convert_from_input_zero_value_throws_invalid_argument", "[red][boundary]") {
    FAIL("RED");
}
