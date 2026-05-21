# 작업 보고서 — TC-A-04 GREEN (unknown unit → invalid_argument)

- **보고서 번호**: 012
- **작성일**: 2026-05-21
- **브랜치**: green
- **커밋(작성 시점)**: 4105041 (feat), 5595189 (docs)

## 1. 작업 개요

Dual-Track TDD GREEN 4차 커밋으로 README RED To-Do **TC-A-04**(없는 단위 `parsec:1.0` → `std::invalid_argument`)을 처리했다. RED 스켈레톤 `FAIL("RED")`를 `REQUIRE_THROWS_AS(convertFromInput("parsec:1.0"), std::invalid_argument)` 본문으로 교체하고 Given 주석에 test_plan B-04·`test_handler_unknown_unit_parsec`를 명시했다. Boundary `ConvertAllUnitsHandler` ERR-INPUT_UNKNOWN_UNIT 및 `convertFromInput` 예외 매핑은 BCE `test_handler_unknown_unit_parsec` 단계에서 이미 구현되어 있어 **프로덕션 코드 변경 없음**. TC-A-01~03 PASS 유지, BCE 45건 회귀 유지, TC-A-05~07·Track B 9건 RED 스켈레톤은 계속 실패.

## 2. 변경·산출물 목록

| 구분 | 경로/항목 | 설명 |
|------|-----------|------|
| GREEN 테스트 | `tests/red/test_track_a_ui_red.cpp` | TC-A-04 Given/When/Then; 입력 `parsec:1.0` |
| README | `README.md` | RED To-Do TC-A-04 체크 `[x]` |
| 프로덕션 | — | 변경 없음 (기존 핸들러·계약 예외 경로 재사용) |
| Git | `4105041`, `5595189` | feat: TC-A-04 GREEN test; docs: report 012 + prompts |
| 보고서 | `Report/012-20260521-tc-a-04-green-unknown-unit-invalid-argument.md` | 본 문서 |
| 프롬프트 | `Prompting/012-…-Prompt.md`, `Prompting_user/012-…-User.md` | 세션 대화·User만 저장 |

## 3. 주요 결정·이슈

- **결정**: TC-A-04만 GREEN — 계약 API `convertFromInput`이 미등록 단위에서 `std::invalid_argument`를 던지는지 검증만 추가.
- **결정**: 입력 샘플은 README·test_plan **B-04**와 정합한 `parsec:1.0` (bootstrap registry에 parsec 없음).
- **이슈(미해결)**: TC-A-05·TC-A-07 및 Track B TC-B-01~06은 아직 `FAIL("RED")` 스켈레톤.

## 4. 테스트·검증

| 명령 | 결과 |
|------|------|
| `cmake -S . -B build; cmake --build build` | 성공 |
| Step 2 `unit_converter_tests "TC-A-04*"` | **FAIL** (`FAIL("RED")`, 기대) |
| Step 4 `unit_converter_tests "TC-A-04*"` | **PASS** (1 assertion) |
| `unit_converter_tests "TC-A-01*"` | **PASS** (4 assertions) |
| `unit_converter_tests "TC-A-02*"` | **PASS** (1 assertion) |
| `unit_converter_tests "TC-A-03*"` | **PASS** (1 assertion) |
| `unit_converter_tests "~[red]"` | **PASS** (45 test cases, 85 assertions) |
| `unit_converter_tests "[red]"` | 4 passed, **9 failed** (TC-A-05~07, TC-B-01~06 `FAIL("RED")`, 기대) |

## 5. 다음 단계

1. **TC-A-05** GREEN: `meter:abc` → `std::invalid_argument`.
2. **TC-A-07** GREEN: `meter:0` → `std::invalid_argument`.
3. Track B **TC-B-01~06** — `UnitConverterContract` 나머지 API.
