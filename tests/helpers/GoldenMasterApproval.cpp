#include "GoldenMasterApproval.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace fs = std::filesystem;

namespace golden_master {

namespace {

constexpr const char* kCliPrompt = "Insert value for converting (ex: meter:2.5): ";

std::string shellQuote(const std::string& path) {
#ifdef _WIN32
    return "\"" + path + "\"";
#else
    return "'" + path + "'";
#endif
}

int runShellCommand(const std::string& command) {
    return std::system(command.c_str());
}

std::string tempPath(const fs::path& dir, const std::string& name) {
    return (dir / name).string();
}

}  // namespace

RunCliOptions defaultRunCliOptions() {
    RunCliOptions options;
#ifdef UNIT_CONVERTER_EXE_PATH
    options.executable_path = UNIT_CONVERTER_EXE_PATH;
#else
    options.executable_path = "UnitConverter";
#endif
#ifdef UNIT_CONVERTER_SOURCE_DIR
    options.working_directory = UNIT_CONVERTER_SOURCE_DIR;
#else
    options.working_directory = ".";
#endif
    return options;
}

ScenarioCapture runCliScenario(const RunCliOptions& options, const std::string& input_line) {
    const fs::path work_dir = fs::path(options.working_directory);
    const fs::path scratch = work_dir / "tests" / ".golden_master_scratch";
    fs::create_directories(scratch);

    const std::string input_path = tempPath(scratch, "input.txt");
    const std::string stdout_path = tempPath(scratch, "stdout.txt");
    const std::string stderr_path = tempPath(scratch, "stderr.txt");

    {
        std::ofstream input_file(input_path, std::ios::binary);
        if (!input_file) {
            throw std::runtime_error("cannot write golden master input file: " + input_path);
        }
        input_file << input_line;
    }

    std::ostringstream command;
#ifdef _WIN32
    command << "cmd /c " << shellQuote(options.executable_path) << " < " << shellQuote(input_path)
            << " > " << shellQuote(stdout_path) << " 2> " << shellQuote(stderr_path);
#else
    command << shellQuote(options.executable_path) << " < " << shellQuote(input_path) << " > "
            << shellQuote(stdout_path) << " 2> " << shellQuote(stderr_path);
#endif

    ScenarioCapture capture;
    capture.input = input_line;
    capture.exit_code = runShellCommand(command.str());
    capture.stdout_text = readFile(stdout_path);
    capture.stderr_text = readFile(stderr_path);
    return capture;
}

std::string normalizeNewlines(std::string text) {
    std::string normalized;
    normalized.reserve(text.size());
    for (std::size_t i = 0; i < text.size(); ++i) {
        if (text[i] == '\r') {
            if (i + 1 < text.size() && text[i + 1] == '\n') {
                normalized.push_back('\n');
                ++i;
            } else {
                normalized.push_back('\n');
            }
            continue;
        }
        normalized.push_back(text[i]);
    }
    return normalized;
}

std::string stripCliPrompt(const std::string& stdout_text) {
    std::string text = normalizeNewlines(stdout_text);
    if (text.rfind(kCliPrompt, 0) == 0) {
        text = text.substr(std::strlen(kCliPrompt));
    }
    return text;
}

std::string formatScenarioBlock(const ScenarioCapture& capture) {
    std::ostringstream block;
    block << '[' << capture.input << "]\n";

    const std::string body = stripCliPrompt(capture.stdout_text);
    if (!body.empty()) {
        block << body;
        if (body.back() != '\n') {
            block << '\n';
        }
    }

    const std::string stderr_text = normalizeNewlines(capture.stderr_text);
    if (!stderr_text.empty()) {
        block << stderr_text;
        if (stderr_text.back() != '\n') {
            block << '\n';
        }
    }

    return block.str();
}

std::string buildGoldenDocument(const std::vector<std::string>& scenario_inputs) {
    const RunCliOptions options = defaultRunCliOptions();
    std::ostringstream document;
    for (std::size_t i = 0; i < scenario_inputs.size(); ++i) {
        const ScenarioCapture capture = runCliScenario(options, scenario_inputs[i]);
        document << formatScenarioBlock(capture);
        if (i + 1 < scenario_inputs.size()) {
            document << "---\n";
        }
    }
    return document.str();
}

std::string readFile(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        return {};
    }
    std::ostringstream buffer;
    buffer << file.rdbuf();
    return normalizeNewlines(buffer.str());
}

void writeFile(const std::string& path, const std::string& content) {
    const fs::path parent = fs::path(path).parent_path();
    if (!parent.empty()) {
        fs::create_directories(parent);
    }
    std::ofstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("cannot write file: " + path);
    }
    file << normalizeNewlines(content);
}

std::string diffLines(const std::string& expected, const std::string& actual) {
    std::istringstream expected_stream(expected);
    std::istringstream actual_stream(actual);
    std::ostringstream diff;
    std::string expected_line;
    std::string actual_line;
    std::size_t line_no = 0;
    bool has_diff = false;

    while (std::getline(expected_stream, expected_line) || std::getline(actual_stream, actual_line)) {
        ++line_no;
        if (!expected_stream && expected_line.empty() && !actual_line.empty()) {
            diff << '+' << line_no << ": " << actual_line << '\n';
            has_diff = true;
            while (std::getline(actual_stream, actual_line)) {
                ++line_no;
                diff << '+' << line_no << ": " << actual_line << '\n';
            }
            break;
        }
        if (!actual_stream && actual_line.empty() && !expected_line.empty()) {
            diff << '-' << line_no << ": " << expected_line << '\n';
            has_diff = true;
            while (std::getline(expected_stream, expected_line)) {
                ++line_no;
                diff << '-' << line_no << ": " << expected_line << '\n';
            }
            break;
        }
        if (expected_line != actual_line) {
            diff << ' ' << line_no << " expected: " << expected_line << '\n';
            diff << ' ' << line_no << " actual  : " << actual_line << '\n';
            has_diff = true;
        }
    }

    if (!has_diff && expected != actual) {
        diff << "documents differ in trailing content or line endings\n";
    }
    return diff.str();
}

}  // namespace golden_master
