#!/usr/bin/env bash
# Generate tests/golden_master_expected.txt from UnitConverter CLI stdout/stderr.
# Usage (from repo root):
#   ./scripts/generate_golden_master.sh [build_dir] [--git-add]

set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

BUILD_DIR="${1:-build}"
GIT_ADD=0
if [[ "${2:-}" == "--git-add" ]] || [[ "${1:-}" == "--git-add" ]]; then
  GIT_ADD=1
fi
if [[ "${1:-}" == "--git-add" ]]; then
  BUILD_DIR="build"
fi

EXE="${BUILD_DIR}/UnitConverter"
if [[ ! -x "$EXE" ]]; then
  echo "Building UnitConverter in ${BUILD_DIR} ..."
  cmake -S . -B "${BUILD_DIR}"
  cmake --build "${BUILD_DIR}" --target UnitConverter
fi

PROMPT='Insert value for converting (ex: meter:2.5): '
SCRATCH="${ROOT}/tests/.golden_master_scratch"
mkdir -p "${SCRATCH}"

OUT="${ROOT}/tests/golden_master_expected.txt"
: > "${OUT}"

scenarios=("meter:2.5" "feet:1.0" "yard:1.0" "meter:0.0")
last_index=$((${#scenarios[@]} - 1))

for i in "${!scenarios[@]}"; do
  input_line="${scenarios[$i]}"
  printf '%s' "${input_line}" > "${SCRATCH}/input.txt"
  "${EXE}" < "${SCRATCH}/input.txt" > "${SCRATCH}/stdout.txt" 2> "${SCRATCH}/stderr.txt" || true

  {
    printf '[%s]\n' "${input_line}"
    body="$(<"${SCRATCH}/stdout.txt")"
    if [[ "${body}" == "${PROMPT}"* ]]; then
      body="${body#${PROMPT}}"
    fi
    if [[ -n "${body}" ]]; then
      printf '%s' "${body}"
      [[ "${body}" == *$'\n' ]] || printf '\n'
    fi
    if [[ -s "${SCRATCH}/stderr.txt" ]]; then
      cat "${SCRATCH}/stderr.txt"
    fi
    if [[ "${i}" -lt "${last_index}" ]]; then
      printf '%s\n' '---'
    fi
  } >> "${OUT}"
done

echo "Wrote ${OUT}"
echo "Capture command per scenario:"
echo "  ./UnitConverter < input.txt > actual.txt"

if [[ "${GIT_ADD}" -eq 1 ]]; then
  git add tests/golden_master_expected.txt
  echo "Staged tests/golden_master_expected.txt"
fi
