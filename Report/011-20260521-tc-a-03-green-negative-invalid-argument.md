# 작업 보고서 — TC-A-03 GREEN (negative value → invalid_argument)

- **보고서 번호**: 011
- **작성일**: 2026-05-21
- **브랜치**: green
- **커밋(작성 시점)**: 571da76 (feat), 3847502 (docs)

## 1. 작업 개요

Dual-Track TDD GREEN 3차 커밋으로 README RED To-Do **TC-A-03**(음수 입력 `meter:-1.0` → `std::invalid_argument`)을 처리했다. RED 스켈레톤 `FAIL("RED")`를 `REQUIRE_THROWS_AS(convertFromInput("meter:-1.0"), std::invalid_argument)` 본문으로 교체했다. Boundary `ConvertInputParser` POL-NEG(`value <= 0` → `ERR-INPUT_NEGATIVE`) 및 `convertFromInput` 예외 매핑은 BCE `test_parse_negative_value_rejected` 단계에서 이미 구현되어 있어 **프로덕션 코드 변경 없음**. 기존 BCE 45건 회귀 유지, TC-A-01·TC-A-02 PASS 유지, TC-A-04~07·Track B 10건 RED 스켈레톤은 계속 실패.

## 2. 변경·산출물 목록

| 구분 | 경로/항목 | 설명 |
|------|-----------|------|
| GREEN 테스트 | `tests/red/test_track_a_ui_red.cpp` | TC-A-03 Given/When/Then; 입력 `meter:-1.0` |
| README | `README.md` | RED To-Do TC-A-03 체크 |
| 프로덕션 | — | 변경 없음 (기존 파서·계약 예외 경로 재사용) |
| Git | `571da76`, `3847502` | feat: TC-A-03 GREEN test; docs: README + report 011 |

## 3. 주요 결정·이슈

- **결정**: TC-A-03만 GREEN — 계약 API `convertFromInput` 실패 시 `std::invalid_argument` 검증만 추가.
- **결정**: 입력 샘플은 README·test_plan **B-07**과 정합한 `meter:-1.0` (BCE는 `meter:-1`로 동일 정책 검증).
- **이슈(미해결)**: TC-A-04~07 GREEN 시 동일 패턴으로 `REQUIRE_THROWS_AS` 또는 golden 검증 확장.

## 4. 테스트·검증

| 명령 | 결과 |
|------|------|
| `cmake -S . -B build && cmake --build build` | 성공 |
| Step 2 `unit_converter_tests "TC-A-03*"` | **FAIL** (`FAIL("RED")`, 기대) |
| Step 4 `unit_converter_tests "TC-A-03*"` | **PASS** (1 assertion) |
| `unit_converter_tests "TC-A-01*"` | **PASS** (4 assertions) |
| `unit_converter_tests "TC-A-02*"` | **PASS** (1 assertion) |
| `unit_converter_tests "~[red]"` | **PASS** (45 test cases, 85 assertions) |
| `unit_converter_tests "[red]"` | 3 passed, **10 failed** (`FAIL("RED")`, 기대) |

## 5. 다음 단계

1. **TC-A-04** GREEN: `parsec:1.0` → `std::invalid_argument`.
2. **TC-A-07** GREEN: `meter:0` → `std::invalid_argument` (POL-NEG zero).
3. Track B TC-B-01~06 — `UnitConverterContract` 나머지 API.
