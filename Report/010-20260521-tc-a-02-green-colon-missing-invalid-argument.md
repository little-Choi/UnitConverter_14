# 작업 보고서 — TC-A-02 GREEN (colon missing → invalid_argument)

- **보고서 번호**: 010
- **작성일**: 2026-05-21
- **브랜치**: green
- **커밋(작성 시점)**: 75873a1 (feat), 1f9030f (docs)

## 1. 작업 개요

Dual-Track TDD GREEN 2차 커밋으로 README RED To-Do **TC-A-02**(콜론 없는 입력 `meter2.5` → `std::invalid_argument`)을 처리했다. RED 스켈레톤 `FAIL("RED")`를 `REQUIRE_THROWS_AS(convertFromInput("meter2.5"), std::invalid_argument)` 본문으로 교체했다. Boundary `ConvertInputParser` 정규식·`convertFromInput` 예외 매핑은 BCE `test_parse_no_colon_format_error` 단계에서 이미 구현되어 있어 **프로덕션 코드 변경 없음**. 기존 BCE 45건 회귀 유지, TC-A-01 PASS 유지, TC-A-03~07·Track B 11건 RED 스켈레톤은 계속 실패.

## 2. 변경·산출물 목록

| 구분 | 경로/항목 | 설명 |
|------|-----------|------|
| GREEN 테스트 | `tests/red/test_track_a_ui_red.cpp` | TC-A-02 Given/When/Then; `#include <stdexcept>` |
| README | `README.md` | RED To-Do TC-A-02 체크 |
| 프로덕션 | — | 변경 없음 (기존 파서·계약 예외 경로 재사용) |
| Git | `75873a1`, `1f9030f` | feat + docs report 010 |

## 3. 주요 결정·이슈

- **결정**: TC-A-02만 GREEN — 계약 API `convertFromInput` 실패 시 `std::invalid_argument` 검증만 추가.
- **결정**: 입력 샘플은 test_plan **B-03**·`test_parse_no_colon_format_error`와 동일한 `meter2.5`.
- **이슈(미해결)**: README TC-A-01 체크는 이전 커밋(009)에서 미반영 — 별도 정리 가능.
- **이슈(미해결)**: TC-A-03~07 GREEN 시 동일 패턴으로 `REQUIRE_THROWS_AS` 확장.

## 4. 테스트·검증

| 명령 | 결과 |
|------|------|
| `cmake -S . -B build && cmake --build build` | 성공 |
| Step 2 `unit_converter_tests "TC-A-02*"` | **FAIL** (`FAIL("RED")`, 기대) |
| Step 4 `unit_converter_tests "TC-A-02*"` | **PASS** (1 assertion) |
| `unit_converter_tests "TC-A-01*"` | **PASS** (4 assertions) |
| `unit_converter_tests "~[red]"` | **PASS** (45 test cases, 85 assertions) |
| `unit_converter_tests "[red]"` | 2 passed, **11 failed** (`FAIL("RED")`, 기대) |
| `ctest --test-dir build` | 47 passed, **11 failed** (red skeletons) |

## 5. 다음 단계

1. **TC-A-03** GREEN: `meter:-1.0` → `std::invalid_argument`.
2. README TC-A-01 체크(009 산출물과 동기화).
3. Track B TC-B-01~06 — `UnitConverterContract` 나머지 API.
