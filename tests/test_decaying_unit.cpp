#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <stdexcept>

#include "DecayingUnit.hpp"

namespace {

constexpr double kCubitMeters = 0.4572;
constexpr double kMeterToFeet = 3.28084;
constexpr double kMeterToYard = 1.09361;

}  // namespace

TEST_CASE("DecayingUnit_bonus_register_and_convert", "[bonus]") {
    SECTION("BT-01: registerUnit cubit then cubit to meter") {
        DecayingUnit converter;
        converter.registerUnit("cubit", kCubitMeters);

        const double result = converter.convert("cubit", 1.0, "meter");
        REQUIRE(result == Catch::Approx(kCubitMeters).margin(1e-5));
    }

    SECTION("BT-02: registerUnit cubit then meter to cubit inverse") {
        DecayingUnit converter;
        converter.registerUnit("cubit", kCubitMeters);

        const double result = converter.convert("meter", 1.0, "cubit");
        REQUIRE(result == Catch::Approx(1.0 / kCubitMeters).margin(1e-5));
    }

    SECTION("BT-03: registerUnit cubit then cubit to feet cross conversion") {
        DecayingUnit converter;
        converter.registerUnit("cubit", kCubitMeters);

        const double result = converter.convert("cubit", 1.0, "feet");
        REQUIRE(result == Catch::Approx(kCubitMeters * kMeterToFeet).margin(1e-5));
    }

    SECTION("BT-04: negative ratio registration throws invalid_argument") {
        DecayingUnit converter;
        REQUIRE_THROWS_AS(converter.registerUnit("bad", -0.4572), std::invalid_argument);
    }

    SECTION("BT-05: registerUnit cubit then convertAll returns all units") {
        DecayingUnit converter;
        converter.registerUnit("cubit", kCubitMeters);

        const auto results = converter.convertAll("cubit", 1.0);
        REQUIRE(results.size() == 4);

        std::size_t matched = 0;
        for (const auto& entry : results) {
            if (entry.unit == "cubit") {
                REQUIRE(entry.value == Catch::Approx(1.0).margin(1e-5));
                ++matched;
            } else if (entry.unit == "meter") {
                REQUIRE(entry.value == Catch::Approx(kCubitMeters).margin(1e-5));
                ++matched;
            } else if (entry.unit == "feet") {
                REQUIRE(entry.value == Catch::Approx(kCubitMeters * kMeterToFeet).margin(1e-5));
                ++matched;
            } else if (entry.unit == "yard") {
                REQUIRE(entry.value == Catch::Approx(kCubitMeters * kMeterToYard).margin(1e-5));
                ++matched;
            }
        }
        REQUIRE(matched == 4);
    }

    SECTION("BT-06: meter to feet unchanged after cubit registration") {
        DecayingUnit converter;
        converter.registerUnit("cubit", kCubitMeters);
        const double result = converter.convert("meter", 1.0, "feet");
        REQUIRE(result == Catch::Approx(kMeterToFeet).margin(1e-5));
    }
}
