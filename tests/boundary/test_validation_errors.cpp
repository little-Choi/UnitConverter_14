#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "boundary/ConvertInputParser.hpp"
#include "boundary/ErrorCodes.hpp"
#include "boundary/RegisterInputParser.hpp"
#include "control/ConvertAllUnitsHandler.hpp"
#include "control/RegisterUnitHandler.hpp"
#include "boundary/TableOutputSerializer.hpp"
#include "domain/UnitRegistry.hpp"

TEST_CASE("test_parse_no_colon_format_error", "[boundary][exception]") {
    // Given: invalid format without colon
    boundary::ConvertInputParser parser;
    boundary::AppError error;

    // When: parse meter2.5
    const auto result = parser.parse("meter2.5", error);

    // Then: ERR-INPUT_FORMAT
    REQUIRE_FALSE(result.has_value());
    REQUIRE(error.code == boundary::ErrorCode::InputFormat);
    REQUIRE(boundary::errorCodeToPrefix(error.code) == "ERR-INPUT_FORMAT:");
}

TEST_CASE("test_parse_negative_value_rejected", "[boundary][exception]") {
    // Given: POL-NEG policy, input meter:-1
    boundary::ConvertInputParser parser;
    boundary::AppError error;

    // When: parse negative
    const auto result = parser.parse("meter:-1", error);

    // Then: ERR-INPUT_NEGATIVE with raw token
    REQUIRE_FALSE(result.has_value());
    REQUIRE(error.code == boundary::ErrorCode::InputNegative);
    REQUIRE(error.message == "-1");
}

TEST_CASE("test_parse_zero_value_rejected", "[boundary][exception]") {
    // Given: POL-NEG policy, input meter:0
    boundary::ConvertInputParser parser;
    boundary::AppError error;

    // When: parse zero
    const auto result = parser.parse("meter:0", error);

    // Then: ERR-INPUT_NEGATIVE
    REQUIRE_FALSE(result.has_value());
    REQUIRE(error.code == boundary::ErrorCode::InputNegative);
    REQUIRE(error.message == "0");
}

TEST_CASE("test_parse_abc_number_format_error", "[boundary][exception]") {
    // Given: non-numeric value token
    boundary::ConvertInputParser parser;
    boundary::AppError error;

    // When: parse meter:abc
    const auto result = parser.parse("meter:abc", error);

    // Then: ERR-INPUT_FORMAT
    REQUIRE_FALSE(result.has_value());
    REQUIRE(error.code == boundary::ErrorCode::InputFormat);
}

TEST_CASE("test_handler_unknown_unit_parsec", "[boundary][exception]") {
    // Given: bootstrap registry without parsec
    auto registry = domain::UnitRegistry::bootstrapDefault();
    boundary::ConvertInputParser parser;
    boundary::TableOutputSerializer serializer;
    control::ConvertAllUnitsHandler handler(registry, parser, serializer);

    // When: convert parsec:1.0
    const auto output = handler.handle("parsec:1.0");

    // Then: ERR-INPUT_UNKNOWN_UNIT with symbol
    REQUIRE_FALSE(output.success);
    REQUIRE(output.lines.empty());
    REQUIRE(output.error.code == boundary::ErrorCode::InputUnknownUnit);
    REQUIRE(output.error.message.find("parsec") != std::string::npos);
}

TEST_CASE("test_parse_double_decimal_format_error", "[boundary][exception]") {
    // Given: invalid double decimal meter:2.5.3
    boundary::ConvertInputParser parser;
    boundary::AppError error;

    // When: parse
    const auto result = parser.parse("meter:2.5.3", error);

    // Then: ERR-INPUT_FORMAT
    REQUIRE_FALSE(result.has_value());
    REQUIRE(error.code == boundary::ErrorCode::InputFormat);
}

TEST_CASE("test_register_invalid_factor_zero", "[boundary][exception]") {
    // Given: register 1 cubit = 0 meter
    auto registry = domain::UnitRegistry::bootstrapDefault();
    boundary::RegisterInputParser parser;
    control::RegisterUnitHandler handler(registry, parser);

    // When: register zero factor
    const auto output = handler.handle("1 cubit = 0 meter");

    // Then: ERR-INPUT_INVALID_FACTOR
    REQUIRE_FALSE(output.success);
    REQUIRE(output.error.code == boundary::ErrorCode::InputInvalidFactor);
}

TEST_CASE("test_register_parser_invalid_format", "[boundary][exception]") {
    boundary::RegisterInputParser parser;
    boundary::AppError error;

    const auto result = parser.parse("cubit:1", error);

    REQUIRE_FALSE(result.has_value());
    REQUIRE(error.code == boundary::ErrorCode::InputFormat);
}

TEST_CASE("test_register_parser_redefine_meter_rejected", "[boundary][exception]") {
    boundary::RegisterInputParser parser;
    boundary::AppError error;

    const auto result = parser.parse("1 meter = 1 meter", error);

    REQUIRE_FALSE(result.has_value());
    REQUIRE(error.code == boundary::ErrorCode::InputInvalidFactor);
    REQUIRE(error.message == "cannot redefine meter");
}

TEST_CASE("test_register_parser_success", "[boundary][parse]") {
    boundary::RegisterInputParser parser;
    boundary::AppError error;

    const auto result = parser.parse("1 cubit = 0.4572 meter", error);

    REQUIRE(result.has_value());
    REQUIRE(result->symbol == "cubit");
    REQUIRE(result->meters_per_unit == Catch::Approx(0.4572).epsilon(1e-9));
}

TEST_CASE("test_register_duplicate_symbol_error", "[boundary][exception]") {
    // Given: feet already in registry
    auto registry = domain::UnitRegistry::bootstrapDefault();
    boundary::RegisterInputParser parser;
    control::RegisterUnitHandler handler(registry, parser);

    // When: register duplicate feet
    const auto output = handler.handle("1 feet = 0.3048 meter");

    // Then: ERR-INPUT_DUPLICATE_REGISTER
    REQUIRE_FALSE(output.success);
    REQUIRE(output.error.code == boundary::ErrorCode::InputDuplicateRegister);
}
