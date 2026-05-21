#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <cmath>

#include "domain/LengthConversionService.hpp"
#include "domain/UnitRegistry.hpp"

namespace {
constexpr double kMeterToFeet = 3.28084;
constexpr double kMeterToYard = 1.09361;
constexpr double kEpsilon = 1e-9;
constexpr double kSixDecimalEpsilon = 1e-6;
}  // namespace

TEST_CASE("test_meter_to_feet_normal_returns_82021", "[domain][normal]") {
    // Given: 1 meter = 3.28084 feet, source = 2.5 meter
    const auto registry = domain::UnitRegistry::bootstrapDefault();
    domain::LengthConversionService service(registry);

    // When: convert meter to feet
    const double result = service.convert("meter", 2.5, "feet");

    // Then: 2.5 * 3.28084 = 8.2021 (no rounding in domain)
    REQUIRE(result == Catch::Approx(2.5 * kMeterToFeet).epsilon(kEpsilon));
}

TEST_CASE("test_meter_to_yard_normal_returns_2734025", "[domain][normal]") {
    // Given: 1 meter = 1.09361 yard, source = 2.5 meter
    const auto registry = domain::UnitRegistry::bootstrapDefault();
    domain::LengthConversionService service(registry);

    // When: convert meter to yard
    const double result = service.convert("meter", 2.5, "yard");

    // Then: 2.5 * 1.09361 = 2.734025
    REQUIRE(result == Catch::Approx(2.5 * kMeterToYard).epsilon(kEpsilon));
}

TEST_CASE("test_feet_to_meter_reverse_returns_25", "[domain][normal]") {
    // Given: 1 meter = 3.28084 feet, round-trip from 2.5 meter
    const auto registry = domain::UnitRegistry::bootstrapDefault();
    domain::LengthConversionService service(registry);
    const double feet_value = 2.5 * kMeterToFeet;

    // When: convert feet back to meter
    const double result = service.convert("feet", feet_value, "meter");

    // Then: inverse restores 2.5 meter
    REQUIRE(result == Catch::Approx(2.5).epsilon(kEpsilon));
}

TEST_CASE("test_feet_to_yard_hub_only_returns_via_meter", "[domain][normal]") {
    // Given: 1 meter = 3.28084 feet, 1 meter = 1.09361 yard; 10 feet input
    const auto registry = domain::UnitRegistry::bootstrapDefault();
    domain::LengthConversionService service(registry);
    const double meter_value = 10.0 / kMeterToFeet;

    // When: feet to yard through meter hub
    const double result = service.convert("feet", 10.0, "yard");

    // Then: equals meter hub path (no direct feet-yard constant)
    REQUIRE(result == Catch::Approx(meter_value * kMeterToYard).epsilon(kEpsilon));
}

TEST_CASE("test_meter_to_meter_identity_returns_same", "[domain][normal]") {
    // Given: 1 meter = 1 meter
    const auto registry = domain::UnitRegistry::bootstrapDefault();
    domain::LengthConversionService service(registry);

    // When: convert meter to meter
    const double result = service.convert("meter", 1.0, "meter");

    // Then: identity preserves value
    REQUIRE(result == Catch::Approx(1.0).epsilon(kEpsilon));
}

TEST_CASE("test_meter_to_feet_zero_value_returns_zero", "[domain][boundary]") {
    // Given: 1 meter = 3.28084 feet, value = 0 (domain math only; boundary rejects in parser)
    const auto registry = domain::UnitRegistry::bootstrapDefault();
    domain::LengthConversionService service(registry);

    // When: convert zero meters
    const double result = service.convert("meter", 0.0, "feet");

    // Then: 0 * 3.28084 = 0
    REQUIRE(result == Catch::Approx(0.0).margin(kEpsilon));
}

TEST_CASE("test_meter_to_feet_large_value_finite", "[domain][boundary]") {
    // Given: 1 meter = 3.28084 feet, value = 1e200
    const auto registry = domain::UnitRegistry::bootstrapDefault();
    domain::LengthConversionService service(registry);

    // When: convert very large meter value
    const double result = service.convert("meter", 1e200, "feet");

    // Then: finite positive product
    REQUIRE(result == Catch::Approx(1e200 * kMeterToFeet).margin(1e190));
    REQUIRE(std::isfinite(result));
}

TEST_CASE("test_meter_to_feet_six_decimal_precision", "[domain][boundary]") {
    // Given: 1 meter = 3.28084 feet, value = 1.123456 meter
    const auto registry = domain::UnitRegistry::bootstrapDefault();
    domain::LengthConversionService service(registry);

    // When: convert with six decimal source
    const double result = service.convert("meter", 1.123456, "feet");

    // Then: within 6-decimal tolerance (1e-6)
    REQUIRE(result == Catch::Approx(1.123456 * kMeterToFeet).epsilon(kSixDecimalEpsilon));
}

TEST_CASE("test_yard_to_feet_small_fraction_precision", "[domain][boundary]") {
    // Given: 1 meter = 1.09361 yard, 1 meter = 3.28084 feet, value = 0.000001 yard
    const auto registry = domain::UnitRegistry::bootstrapDefault();
    domain::LengthConversionService service(registry);

    // When: convert tiny yard value
    const double result = service.convert("yard", 0.000001, "feet");

    // Then: hub conversion within 6-decimal tolerance
    const double meter_value = 0.000001 / kMeterToYard;
    REQUIRE(result == Catch::Approx(meter_value * kMeterToFeet).epsilon(kSixDecimalEpsilon));
}

TEST_CASE("test_convert_all_returns_registry_size", "[domain][boundary]") {
    // Given: default registry size = 3
    const auto registry = domain::UnitRegistry::bootstrapDefault();
    domain::LengthConversionService service(registry);

    // When: convertAll from meter:1
    const auto batch = service.convertAll("meter", 1.0);

    // Then: batch length equals registry size
    REQUIRE(batch.size() == registry.size());
}
