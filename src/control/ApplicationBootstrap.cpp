#include "control/ApplicationBootstrap.hpp"

#include "boundary/ConsoleErrorWriter.hpp"
#include "boundary/ErrorCodes.hpp"
#include "data/ConfigLoader.hpp"

#include <cstdlib>
#include <string>

namespace control {

domain::UnitRegistry loadRegistryFromArgv(int argc, char** argv) {
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
            boundary::writeAppErrorToStderr(error);
            std::exit(1);
        }
    }
    return registry;
}

}  // namespace control
