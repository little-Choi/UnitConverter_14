#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "boundary/ConvertInputParser.hpp"
#include "boundary/ErrorCodes.hpp"

TEST_CASE("test_parse_meter_colon_25_success", "[boundary][parse]") {
    // Given: valid pattern meter:2.5
    boundary::ConvertInputParser parser;
    boundary::AppError error;

    // When: parse input
    const auto result = parser.parse("meter:2.5", error);

    // Then: unit and value extracted
    REQUIRE(result.has_value());
    REQUIRE(result->unit == "meter");
    REQUIRE(result->value == Catch::Approx(2.5).epsilon(1e-9));
    REQUIRE(error.code == boundary::ErrorCode::None);
}

TEST_CASE("test_parse_feet_colon_10_success", "[boundary][parse]") {
    // Given: 1 meter = 3.28084 feet, input feet:10
    boundary::ConvertInputParser parser;
    boundary::AppError error;

    // When: parse feet:10
    const auto result = parser.parse("feet:10", error);

    // Then: parse succeeds
    REQUIRE(result.has_value());
    REQUIRE(result->unit == "feet");
    REQUIRE(result->value == Catch::Approx(10.0).epsilon(1e-9));
}

TEST_CASE("test_parse_yard_colon_1_success", "[boundary][parse]") {
    // Given: 1 meter = 1.09361 yard, input yard:1
    boundary::ConvertInputParser parser;
    boundary::AppError error;

    // When: parse yard:1
    const auto result = parser.parse("yard:1", error);

    // Then: parse succeeds
    REQUIRE(result.has_value());
    REQUIRE(result->unit == "yard");
    REQUIRE(result->value == Catch::Approx(1.0).epsilon(1e-9));
}

TEST_CASE("test_parse_six_decimal_value_success", "[boundary][parse]") {
    // Given: six-decimal value 1.123456
    boundary::ConvertInputParser parser;
    boundary::AppError error;

    // When: parse meter:1.123456
    const auto result = parser.parse("meter:1.123456", error);

    // Then: preserves six decimals
    REQUIRE(result.has_value());
    REQUIRE(result->value == Catch::Approx(1.123456).epsilon(1e-6));
}

TEST_CASE("test_parse_large_value_1e100_success", "[boundary][parse]") {
    // Given: very large positive value
    boundary::ConvertInputParser parser;
    boundary::AppError error;

    // When: parse meter:1e100
    const auto result = parser.parse("meter:1e100", error);

    // Then: large value accepted at boundary
    REQUIRE(result.has_value());
    REQUIRE(result->value == Catch::Approx(1e100).margin(1.0));
}
