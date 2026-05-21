#include <catch2/catch_test_macros.hpp>

#include <sstream>

#include "boundary/ConsoleErrorWriter.hpp"
#include "boundary/ErrorCodes.hpp"

TEST_CASE("test_error_code_prefix_all_codes", "[boundary][error]") {
    REQUIRE(boundary::errorCodeToPrefix(boundary::ErrorCode::None) == "");
    REQUIRE(boundary::errorCodeToPrefix(boundary::ErrorCode::InputFormat) == "ERR-INPUT_FORMAT:");
    REQUIRE(boundary::errorCodeToPrefix(boundary::ErrorCode::InputNegative) == "ERR-INPUT_NEGATIVE:");
    REQUIRE(boundary::errorCodeToPrefix(boundary::ErrorCode::InputUnknownUnit) ==
            "ERR-INPUT_UNKNOWN_UNIT:");
    REQUIRE(boundary::errorCodeToPrefix(boundary::ErrorCode::InputInvalidFactor) ==
            "ERR-INPUT_INVALID_FACTOR:");
    REQUIRE(boundary::errorCodeToPrefix(boundary::ErrorCode::InputDuplicateRegister) ==
            "ERR-INPUT_DUPLICATE_REGISTER:");
    REQUIRE(boundary::errorCodeToPrefix(boundary::ErrorCode::ConfigLoad) == "ERR-CONFIG_LOAD:");
    REQUIRE(boundary::errorCodeToPrefix(boundary::ErrorCode::ConfigSchema) == "ERR-CONFIG_SCHEMA:");
    REQUIRE(boundary::errorCodeToPrefix(static_cast<boundary::ErrorCode>(999)) == "");
}

TEST_CASE("test_write_app_error_format_matches_cli_contract", "[boundary][error]") {
    std::ostringstream out;
    boundary::AppError error{boundary::ErrorCode::InputFormat, "meter2.5"};
    boundary::writeAppError(out, error);
    REQUIRE(out.str() == "ERR-INPUT_FORMAT: meter2.5\n");
}
