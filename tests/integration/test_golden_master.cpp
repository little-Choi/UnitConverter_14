#include <catch2/catch_test_macros.hpp>

#include <filesystem>
#include <vector>

#include "GoldenMasterApproval.hpp"

namespace {

const std::vector<std::string> kGoldenScenarios = {
    "meter:2.5",
    "feet:1.0",
    "yard:1.0",
    "meter:0.0",
};

std::string goldenMasterPath() {
#ifdef UNIT_CONVERTER_SOURCE_DIR
    return std::string(UNIT_CONVERTER_SOURCE_DIR) + "/tests/golden_master_expected.txt";
#else
    return "tests/golden_master_expected.txt";
#endif
}

}  // namespace

TEST_CASE("golden_master_cli_stdout_approval", "[integration][golden][e2e]") {
    const std::string expected_path = goldenMasterPath();
    const std::string actual = golden_master::buildGoldenDocument(kGoldenScenarios);

    if (!std::filesystem::exists(expected_path)) {
        golden_master::writeFile(expected_path, actual);
        INFO("Created missing golden master baseline: " << expected_path);
        INFO("Review and version-control with: git add tests/golden_master_expected.txt");
        REQUIRE(actual.size() > 0);
        return;
    }

    const std::string expected = golden_master::normalizeNewlines(golden_master::readFile(expected_path));
    const std::string actual_normalized = golden_master::normalizeNewlines(actual);
    if (expected != actual_normalized) {
        const std::string diff = golden_master::diffLines(expected, actual_normalized);
        INFO("Golden master mismatch. Diff (+ added, - removed, space changed):\n" << diff);
        INFO("Expected path: " << expected_path);
        INFO("Re-approve with: scripts/generate_golden_master.ps1 (or .sh)");
        FAIL("golden master stdout approval failed");
    }
}
