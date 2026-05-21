cmake_minimum_required(VERSION 3.16)
project(UnitConverter VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_COVERAGE "Build with gcov coverage" OFF)
if(ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(--coverage -O0 -g)
  add_link_options(--coverage)
endif()

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.4
)
FetchContent_MakeAvailable(Catch2)

add_library(unit_converter_core
  src/domain/UnitRegistry.cpp
  src/domain/LengthConversionService.cpp
  src/boundary/ConvertInputParser.cpp
  src/boundary/RegisterInputParser.cpp
  src/boundary/TableOutputSerializer.cpp
  src/boundary/JsonOutputSerializer.cpp
  src/boundary/ErrorCodes.cpp
  src/data/JsonConfigLoader.cpp
  src/data/YamlConfigLoader.cpp
  src/control/ConvertAllUnitsHandler.cpp
  src/control/RegisterUnitHandler.cpp
  src/contract/UnitConverterContract.cpp
)

target_include_directories(unit_converter_core PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(UnitConverter UnitConverter.cpp)
target_link_libraries(UnitConverter PRIVATE unit_converter_core)

enable_testing()

add_executable(unit_converter_tests
  tests/domain/test_length_conversion.cpp
  tests/domain/test_unit_registry.cpp
  tests/boundary/test_convert_parser.cpp
  tests/boundary/test_validation_errors.cpp
  tests/boundary/test_table_serializer.cpp
  tests/data/test_config_loader.cpp
  tests/integration/test_dynamic_register.cpp
  tests/red/test_track_a_ui_red.cpp
  tests/red/test_track_b_logic_red.cpp
)

target_link_libraries(unit_converter_tests PRIVATE
  unit_converter_core
  Catch2::Catch2WithMain
)

target_compile_definitions(unit_converter_tests PRIVATE
  UNIT_CONVERTER_TEST_FIXTURE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/tests/fixtures"
)

include(CTest)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(unit_converter_tests)
