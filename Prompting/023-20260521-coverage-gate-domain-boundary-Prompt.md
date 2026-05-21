# 대화 프롬프트 기록 — 023-20260521-coverage-gate-domain-boundary

- **보고서 번호**: 023
- **저장일**: 2026-05-21

---

## Turn 1

**User**

모든 TC(TC-A-01~07, TC-B-01~07)가 통과한 후 전체 테스트를 실행하라.

cmake -S . -B build && cmake --build build ctest --test-dir build -V

커버리지 측정:
# gcov / lcov gcov @UnitConverter.cpp 

확인 항목:
- 모든 TC PASS (0 failures)
- Domain Logic 커버리지 ≥ 95%
- Boundary Layer 커버리지 ≥ 85%
- 비율 상수 3.28084 / 1.09361이 인라인으로 남아 있지 않음
- main() 함수에 변환 로직이 남아 있지 않음 (Domain으로 분리됨)

**Assistant** (검증·측정 요약)

1. `cmake -S . -B build` → `cmake --build build` → `ctest --test-dir build -V` 실행(PowerShell은 `&&` 대신 `;` 사용).
2. **59/59 PASS** — TC-A #8~#14, TC-B #1~#7 포함, 0 failures.
3. `build-cov` + `-DENABLE_COVERAGE=ON` + lcov:
   - Domain `src/domain/*`: **81.8%** — Gate **미달** (목표 ≥95%)
   - Boundary `src/boundary/*`: **73.8%** — Gate **미달** (목표 ≥85%)
4. 구조 검증 **PASS**:
   - 비율 상수: `src/domain/UnitRegistry.cpp`의 `kMeterToFeet`/`kMeterToYard`만 존재
   - `UnitConverter.cpp` `main()`: I/O·핸들러 위임만, 환산 수식 없음
5. `UnitConverter.cpp` gcov: exe 1회 실행 시 line ~36% (CLI·`--config=` 분기 미실행).
6. README 커버리지 To-Do Domain·Boundary는 미체크 상태.

---

## Turn 2

**User**

진행해줘.

**Assistant** (커버리지 보강)

미커버 분기를 채우는 테스트 9건 추가:

| 파일 | 추가 테스트 |
|------|-------------|
| `tests/domain/test_unit_registry.cpp` | `registerUnit` 실패, `clear`/`loadFromDefinitions` |
| `tests/domain/test_length_conversion.cpp` | unknown unit → `invalid_argument` |
| `tests/boundary/test_error_codes.cpp` | **신규** — 모든 `ErrorCode` prefix |
| `tests/boundary/test_convert_parser.cpp` | empty input, trim whitespace |
| `tests/boundary/test_validation_errors.cpp` | 등록 포맷 실패, meter 재정의, 파서 성공 |

`CMakeLists.txt`에 `test_error_codes.cpp` 등록. 재측정 결과:

- Domain: **95.5%** (42/44) — Gate **PASS**
- Boundary: **92.5%** (99/107) — Gate **PASS**
- 전체 테스트: **68/68 PASS**
- README Domain·Boundary 커버리지 To-Do `[x]` 갱신

---

## Turn 3

**User**

보고서 작성 및 저장 Agent 실행해줘.

**Assistant** (report-github-manager)

`Report/023-20260521-coverage-gate-domain-boundary.md`, `Prompting/023-…-Prompt.md`, `Prompting_user/023-…-User.md` 작성 후 git commit·push 수행.
