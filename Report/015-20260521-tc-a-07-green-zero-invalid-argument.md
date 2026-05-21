# 작업 보고서 — TC-A-07 GREEN (zero value → invalid_argument)

- **보고서 번호**: 015
- **작성일**: 2026-05-21
- **브랜치**: green
- **커밋(작성 시점)**: 미커밋

## 1. 작업 개요

Dual-Track TDD GREEN 7차 커밋으로 README RED To-Do **TC-A-07**(영값 입력 `meter:0` → `std::invalid_argument`)을 처리했다. RED 스켈레톤 `FAIL("RED")`를 `REQUIRE_THROWS_AS(convertFromInput("meter:0"), std::invalid_argument)` 본문으로 교체했다. Boundary `ConvertInputParser` POL-NEG(`value <= 0` → `ERR-INPUT_NEGATIVE`) 및 `convertFromInput` 예외 매핑은 BCE `test_parse_zero_value_rejected` 단계에서 이미 구현되어 있어 **프로덕션 코드 변경 없음**. TC-A-01~06 PASS·BCE 45건 회귀 유지, Track B TC-B-01~06 RED 스켈레톤은 계속 실패한다.

## 2. 변경·산출물 목록

| 구분 | 경로/항목 | 설명 |
|------|-----------|------|
| GREEN 테스트 | `tests/red/test_track_a_ui_red.cpp` | TC-A-07 Given/When/Then; 입력 `meter:0` (test_plan B-06) |
| README | `README.md` | RED To-Do TC-A-07 체크 `[x]` |
| 프로덕션 | — | 변경 없음 (기존 파서·계약 예외 경로 재사용) |
| 보고서 | `Report/015-20260521-tc-a-07-green-zero-invalid-argument.md` | 본 문서 |
| 프롬프트 | `Prompting/015-20260521-tc-a-07-green-zero-invalid-argument-Prompt.md`, `Prompting_user/015-20260521-tc-a-07-green-zero-invalid-argument-User.md` | 세션 대화·User만 저장 |

## 3. 주요 결정·이슈

- **결정**: TC-A-07만 GREEN — 계약 API `convertFromInput` 실패 시 `std::invalid_argument` 검증만 추가.
- **결정**: 입력 샘플은 README·test_plan **B-06**과 정합한 `meter:0` (BCE `test_parse_zero_value_rejected`와 동일 정책).
- **결정**: POL-NEG-01 — length value **> 0** only; zero는 TC-A-03(음수)과 동일 `value <= 0.0` 경로.
- **이슈(미해결)**: Track B TC-B-01~06은 아직 `FAIL("RED")` 스켈레톤.

## 4. 테스트·검증

| 명령 | 결과 |
|------|------|
| `cmake -S . -B build; cmake --build build` | 성공 |
| Step 2 `unit_converter_tests "TC-A-07*"` | **FAIL** (`FAIL("RED")`, 기대) |
| Step 4 `unit_converter_tests "TC-A-07*"` | **PASS** (1 assertion) |
| `unit_converter_tests "TC-A-01*"` ~ `"TC-A-06*"` | **PASS** (각 1~4 assertions) |
| `unit_converter_tests "~[red]"` | **PASS** (45 test cases, 85 assertions) |
| `unit_converter_tests "[red]"` | 7 passed, **6 failed** (TC-B-01~06 `FAIL("RED")`, 기대) |

## 5. 다음 단계

1. Track B **TC-B-01** GREEN: `convert("meter", 2.5, "feet")` ≈ 8.20210 (ε=1e-5).
2. Track B TC-B-02~06 — `UnitConverterContract` Domain API 순차 GREEN.
3. Track A RED To-Do 완료 — Track B·커버리지 목표로 전환.
