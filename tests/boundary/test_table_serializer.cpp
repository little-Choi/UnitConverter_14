#include <catch2/catch_test_macros.hpp>

#include "boundary/TableOutputSerializer.hpp"
#include "domain/LengthConversionService.hpp"
#include "domain/UnitRegistry.hpp"

TEST_CASE("test_display_meter_25_feet_half_up_82", "[boundary][display]") {
    // Given: 1 meter = 3.28084 feet, raw 8.2021
    // When: format display value
    const std::string text = boundary::TableOutputSerializer::formatDisplayValue(8.2021);

    // Then: one decimal half-up => 8.2
    REQUIRE(text == "8.2");
}

TEST_CASE("test_display_meter_25_yard_half_up_27", "[boundary][display]") {
    // Given: 1 meter = 1.09361 yard, raw 2.734025
    // When: format display
    const std::string text = boundary::TableOutputSerializer::formatDisplayValue(2.734025);

    // Then: half-up => 2.7
    REQUIRE(text == "2.7");
}

TEST_CASE("test_table_meter_25_golden_lines", "[boundary][display]") {
    // Given: 1 meter = 3.28084 feet, 1 meter = 1.09361 yard, meter:2.5
    const auto registry = domain::UnitRegistry::bootstrapDefault();
    domain::LengthConversionService service(registry);
    boundary::TableOutputSerializer serializer;
    const auto results = service.convertAll("meter", 2.5);

    // When: serialize table lines
    const auto lines = serializer.serialize("meter", 2.5, results);

    // Then: README golden feet/yard display
    REQUIRE(lines.size() == 3);
    REQUIRE(lines[0] == "2.5 meter = 2.5 meter");
    REQUIRE(lines[1] == "2.5 meter = 8.2 feet");
    REQUIRE(lines[2] == "2.5 meter = 2.7 yard");
}

TEST_CASE("test_display_integer_no_trailing_zero", "[boundary][display]") {
    // Given: integer raw 5.0
    // When: format
    const std::string text = boundary::TableOutputSerializer::formatDisplayValue(5.0);

    // Then: displays 5
    REQUIRE(text == "5");
}

TEST_CASE("test_display_rounds_half_up_at_five", "[boundary][display]") {
    // Given: value 5.05 needs half-up to 5.1
    // When: format
    const std::string text = boundary::TableOutputSerializer::formatDisplayValue(5.05);

    // Then: 5.1
    REQUIRE(text == "5.1");
}
