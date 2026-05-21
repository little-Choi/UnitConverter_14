# 작업 보고서 — TC-A-05 GREEN (abc 파싱 실패 → invalid_argument)

- **보고서 번호**: 013
- **작성일**: 2026-05-21
- **브랜치**: green
- **커밋(작성 시점)**: 293349f (docs: report 012)

## 1. 작업 개요

Dual-Track TDD GREEN 5차 커밋으로 README RED To-Do **TC-A-05**(비숫자 값 `meter:abc` → `std::invalid_argument`)을 처리했다. RED 스켈레톤 `FAIL("RED")`를 `REQUIRE_THROWS_AS(convertFromInput("meter:abc"), std::invalid_argument)` 본문으로 교체하고 Given 주석에 test_plan B-05·`test_parse_abc_number_format_error`를 명시했다. `ConvertInputParser` 정규식이 비숫자 토큰을 거부하고, BCE `test_parse_abc_number_format_error`가 이미 GREEN이며 `convertFromInput`이 핸들러 실패를 `std::invalid_argument`로 매핑하므로 **프로덕션 코드 변경 없음**. TC-A-01~04 PASS 유지, BCE 45건 회귀 유지, TC-A-06~07·Track B 8건 RED 스켈레톤은 계속 실패.

## 2. 변경·산출물 목록

| 구분 | 경로/항목 | 설명 |
|------|-----------|------|
| GREEN 테스트 | `tests/red/test_track_a_ui_red.cpp` | TC-A-05 Given/When/Then; 입력 `meter:abc` |
| README | `README.md` | RED To-Do TC-A-05 체크 `[x]` |
| 프로덕션 | — | 변경 없음 (파서·계약 예외 경로 재사용) |
| 보고서 | `Report/013-20260521-tc-a-05-green-abc-invalid-argument.md` | 본 문서 |
| 프롬프트 | `Prompting/013-…-Prompt.md`, `Prompting_user/013-…-User.md` | 세션 대화·User만 저장 |

## 3. 주요 결정·이슈

- **결정**: TC-A-05만 GREEN — 계약 API `convertFromInput`이 비숫자 값 토큰에서 `std::invalid_argument`를 던지는지 검증만 추가.
- **결정**: 입력 샘플은 README·test_plan **B-05**와 정합한 `meter:abc`.
- **이슈(미해결)**: TC-A-06·TC-A-07 및 Track B TC-B-01~06은 아직 `FAIL("RED")` 스켈레톤.

## 4. 테스트·검증

| 명령 | 결과 |
|------|------|
| `cmake -S . -B build; cmake --build build` | 성공 |
| Step 2 `unit_converter_tests "TC-A-05*"` | **FAIL** (`FAIL("RED")`, 기대) |
| Step 4 `unit_converter_tests "TC-A-05*"` | **PASS** (1 assertion) |
| `unit_converter_tests "TC-A-01*"` | **PASS** (4 assertions) |
| `unit_converter_tests "TC-A-02*"` | **PASS** (1 assertion) |
| `unit_converter_tests "TC-A-03*"` | **PASS** (1 assertion) |
| `unit_converter_tests "TC-A-04*"` | **PASS** (1 assertion) |
| `unit_converter_tests "~[red]"` | **PASS** (45 test cases, 85 assertions) |
| `unit_converter_tests "[red]"` | 5 passed, **8 failed** (TC-A-06~07, TC-B-01~06 `FAIL("RED")`, 기대) |

## 5. 다음 단계

1. **TC-A-07** GREEN: `meter:0` → `std::invalid_argument`.
2. **TC-A-06** GREEN: 출력 포맷에 원 입력 단위·값 보존 (table/json).
3. Track B **TC-B-01~06** — `UnitConverterContract` 나머지 API.
