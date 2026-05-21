#include "boundary/ConvertInputParser.hpp"
#include "boundary/ErrorCodes.hpp"
#include "boundary/RegisterInputParser.hpp"
#include "boundary/TableOutputSerializer.hpp"
#include "control/ConvertAllUnitsHandler.hpp"
#include "control/RegisterUnitHandler.hpp"
#include "data/ConfigLoader.hpp"
#include "domain/UnitRegistry.hpp"

#include <iostream>
#include <string>

namespace {

domain::UnitRegistry loadRegistry(int argc, char** argv) {
    domain::UnitRegistry registry = domain::UnitRegistry::bootstrapDefault();
    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];
        const std::string prefix = "--config=";
        if (arg.rfind(prefix, 0) == 0) {
            const std::string path = arg.substr(prefix.size());
            boundary::AppError error;
            data::JsonConfigLoader json_loader;
            if (auto snapshot = json_loader.loadFromFile(path, error)) {
                registry.clear();
                registry.loadFromDefinitions(snapshot->units);
                return registry;
            }
            data::YamlConfigLoader yaml_loader;
            if (auto snapshot = yaml_loader.loadFromFile(path, error)) {
                registry.clear();
                registry.loadFromDefinitions(snapshot->units);
                return registry;
            }
            std::cerr << boundary::errorCodeToPrefix(error.code) << ' ' << error.message << '\n';
            std::exit(1);
        }
    }
    return registry;
}

}  // namespace

int main(int argc, char** argv) {
    auto registry = loadRegistry(argc, argv);

    std::cout << "Insert value for converting (ex: meter:2.5): ";
    std::string input;
    if (!std::getline(std::cin, input)) {
        return 1;
    }

    boundary::ConvertInputParser convert_parser;
    boundary::RegisterInputParser register_parser;
    boundary::TableOutputSerializer serializer;
    control::ConvertAllUnitsHandler convert_handler(registry, convert_parser, serializer);
    control::RegisterUnitHandler register_handler(registry, register_parser);

    if (input.rfind("1 ", 0) == 0) {
        const auto result = register_handler.handle(input);
        if (!result.success) {
            std::cerr << boundary::errorCodeToPrefix(result.error.code) << ' '
                      << result.error.message << '\n';
            return 1;
        }
        std::cout << "Registered " << input << '\n';
        return 0;
    }

    const auto result = convert_handler.handle(input);
    if (!result.success) {
        std::cerr << boundary::errorCodeToPrefix(result.error.code) << ' '
                  << result.error.message << '\n';
        return 1;
    }

    for (const auto& line : result.lines) {
        std::cout << line << '\n';
    }
    return 0;
}
