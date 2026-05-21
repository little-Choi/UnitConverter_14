#pragma once

#include <string>
#include <vector>

namespace golden_master {

struct ScenarioCapture {
    std::string input;
    std::string stdout_text;
    std::string stderr_text;
    int exit_code{0};
};

struct RunCliOptions {
    std::string executable_path;
    std::string working_directory;
};

RunCliOptions defaultRunCliOptions();

ScenarioCapture runCliScenario(const RunCliOptions& options, const std::string& input_line);

std::string stripCliPrompt(const std::string& stdout_text);

std::string formatScenarioBlock(const ScenarioCapture& capture);

std::string buildGoldenDocument(const std::vector<std::string>& scenario_inputs);

std::string readFile(const std::string& path);

std::string normalizeNewlines(std::string text);

void writeFile(const std::string& path, const std::string& content);

std::string diffLines(const std::string& expected, const std::string& actual);

}  // namespace golden_master
