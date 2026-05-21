#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "boundary/RegisterInputParser.hpp"
#include "boundary/TableOutputSerializer.hpp"
#include "control/ConvertAllUnitsHandler.hpp"
#include "control/RegisterUnitHandler.hpp"
#include "domain/LengthConversionService.hpp"
#include "domain/UnitRegistry.hpp"

TEST_CASE("test_register_cubit_then_convert_to_meter", "[integration][register]") {
    // Given: 1 cubit = 0.4572 meter
    auto registry = domain::UnitRegistry::bootstrapDefault();
    boundary::RegisterInputParser register_parser;
    control::RegisterUnitHandler register_handler(registry, register_parser);

    // When: register cubit and convert cubit:1 to meter
    const auto reg = register_handler.handle("1 cubit = 0.4572 meter");
    REQUIRE(reg.success);

    domain::LengthConversionService service(registry);
    const double meters = service.convert("cubit", 1.0, "meter");

    // Then: 1 cubit = 0.4572 meter
    REQUIRE(meters == Catch::Approx(0.4572).epsilon(1e-9));
}

TEST_CASE("test_register_cubit_then_convert_to_feet", "[integration][register]") {
    // Given: 1 cubit = 0.4572 meter, 1 meter = 3.28084 feet
    auto registry = domain::UnitRegistry::bootstrapDefault();
    boundary::RegisterInputParser register_parser;
    control::RegisterUnitHandler register_handler(registry, register_parser);
    register_handler.handle("1 cubit = 0.4572 meter");

    domain::LengthConversionService service(registry);

    // When: cubit:1 to feet via meter hub
    const double feet = service.convert("cubit", 1.0, "feet");

    // Then: 0.4572 * 3.28084 feet
    REQUIRE(feet == Catch::Approx(0.4572 * 3.28084).epsilon(1e-9));
}

TEST_CASE("test_register_cubit_increases_registry_size", "[integration][register]") {
    // Given: default size 3
    auto registry = domain::UnitRegistry::bootstrapDefault();
    boundary::RegisterInputParser register_parser;
    control::RegisterUnitHandler register_handler(registry, register_parser);

    // When: register cubit
    register_handler.handle("1 cubit = 0.4572 meter");

    // Then: registry size 4
    REQUIRE(registry.size() == 4);
}

TEST_CASE("test_register_cubit_convert_all_batch_size", "[integration][register]") {
    // Given: cubit registered, 1 meter = 3.28084 feet
    auto registry = domain::UnitRegistry::bootstrapDefault();
    boundary::RegisterInputParser register_parser;
    boundary::ConvertInputParser convert_parser;
    boundary::TableOutputSerializer serializer;
    control::RegisterUnitHandler register_handler(registry, register_parser);
    control::ConvertAllUnitsHandler convert_handler(registry, convert_parser, serializer);

    register_handler.handle("1 cubit = 0.4572 meter");

    // When: convert cubit:1
    const auto output = convert_handler.handle("cubit:1");

    // Then: 4 lines (meter, feet, yard, cubit)
    REQUIRE(output.success);
    REQUIRE(output.lines.size() == 4);
}

TEST_CASE("test_register_cubit_table_contains_feet_line", "[integration][register]") {
    // Given: cubit registered
    auto registry = domain::UnitRegistry::bootstrapDefault();
    boundary::RegisterInputParser register_parser;
    boundary::ConvertInputParser convert_parser;
    boundary::TableOutputSerializer serializer;
    control::RegisterUnitHandler register_handler(registry, register_parser);
    control::ConvertAllUnitsHandler convert_handler(registry, convert_parser, serializer);
    register_handler.handle("1 cubit = 0.4572 meter");

    // When: convert cubit:1
    const auto output = convert_handler.handle("cubit:1");

    // Then: output includes feet conversion line
    bool has_feet = false;
    for (const auto& line : output.lines) {
        if (line.find("feet") != std::string::npos) {
            has_feet = true;
        }
    }
    REQUIRE(has_feet);
}

TEST_CASE("test_register_direct_registry_unit", "[integration][register]") {
    // Given: registerUnit API, 1 span = 0.2286 meter
    auto registry = domain::UnitRegistry::bootstrapDefault();

    // When: register span and convert
    REQUIRE(registry.registerUnit("span", 0.2286));
    domain::LengthConversionService service(registry);
    const double meter = service.convert("span", 2.0, "meter");

    // Then: 2 * 0.2286 meter
    REQUIRE(meter == Catch::Approx(0.4572).epsilon(1e-9));
}
