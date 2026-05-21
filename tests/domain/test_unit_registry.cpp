#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "domain/UnitRegistry.hpp"

TEST_CASE("test_registry_bootstrap_has_three_units", "[domain][registry]") {
    // Given: bootstrap default registry
    const auto registry = domain::UnitRegistry::bootstrapDefault();

    // When: inspect size
    const std::size_t count = registry.size();

    // Then: meter, feet, yard registered
    REQUIRE(count == 3);
}

TEST_CASE("test_registry_meter_factor_is_one", "[domain][registry]") {
    // Given: 1 meter = 1 meter
    const auto registry = domain::UnitRegistry::bootstrapDefault();

    // When: lookup meter
    const auto meter = registry.find("meter");

    // Then: meters_per_unit = 1.0
    REQUIRE(meter.has_value());
    REQUIRE(meter->meters_per_unit == Catch::Approx(1.0).epsilon(1e-9));
}

TEST_CASE("test_registry_feet_factor_matches_ratio", "[domain][registry]") {
    // Given: 1 meter = 3.28084 feet => meters_per_unit(feet) = 1/3.28084
    const auto registry = domain::UnitRegistry::bootstrapDefault();

    // When: lookup feet
    const auto feet = registry.find("feet");

    // Then: factor equals inverse of 3.28084
    REQUIRE(feet.has_value());
    REQUIRE(feet->meters_per_unit == Catch::Approx(1.0 / 3.28084).epsilon(1e-9));
}

TEST_CASE("test_registry_yard_factor_matches_ratio", "[domain][registry]") {
    // Given: 1 meter = 1.09361 yard
    const auto registry = domain::UnitRegistry::bootstrapDefault();

    // When: lookup yard
    const auto yard = registry.find("yard");

    // Then: factor equals inverse of 1.09361
    REQUIRE(yard.has_value());
    REQUIRE(yard->meters_per_unit == Catch::Approx(1.0 / 1.09361).epsilon(1e-9));
}

TEST_CASE("test_registry_unknown_unit_not_found", "[domain][registry]") {
    // Given: bootstrap registry without parsec
    const auto registry = domain::UnitRegistry::bootstrapDefault();

    // When: find unknown unit
    const auto parsec = registry.find("parsec");

    // Then: not registered
    REQUIRE_FALSE(parsec.has_value());
}
