#include "boundary/ConsoleErrorWriter.hpp"
#include "boundary/ConvertInputParser.hpp"
#include "boundary/RegisterInputParser.hpp"
#include "boundary/TableOutputSerializer.hpp"
#include "control/ApplicationBootstrap.hpp"
#include "control/ConvertAllUnitsHandler.hpp"
#include "control/RegisterUnitHandler.hpp"

#include <iostream>
#include <string>

int main(int argc, char** argv) {
    auto registry = control::loadRegistryFromArgv(argc, argv);

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
            boundary::writeAppErrorToStderr(result.error);
            return 1;
        }
        std::cout << "Registered " << input << '\n';
        return 0;
    }

    const auto result = convert_handler.handle(input);
    if (!result.success) {
        boundary::writeAppErrorToStderr(result.error);
        return 1;
    }

    for (const auto& line : result.lines) {
        std::cout << line << '\n';
    }
    return 0;
}
