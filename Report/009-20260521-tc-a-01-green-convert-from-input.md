# 작업 보고서 — TC-A-01 GREEN (convertFromInput)

- **보고서 번호**: 009
- **작성일**: 2026-05-21
- **브랜치**: green
- **커밋(작성 시점)**: 1dde74c

## 1. 작업 개요

Dual-Track TDD GREEN 1차 커밋으로 README RED To-Do **TC-A-01**(정상 입력 `meter:2.5` → 변환 결과 반환)을 처리했다. RED 스켈레톤 `FAIL("RED")`를 Given/When/Then 본문으로 교체하고, `unit_converter::convertFromInput` 계약 API를 `ConvertAllUnitsHandler` 파사드로 최소 구현했다. 기존 BCE 45건 회귀는 유지하며, TC-A-02~07·Track B 12건 RED 스켈레톤은 그대로 실패한다.

## 2. 변경·산출물 목록

| 구분 | 경로/항목 | 설명 |
|------|-----------|------|
| 계약 구현 | `src/contract/UnitConverterContract.cpp` | `convertFromInput` — bootstrap registry + handler + table lines |
| 빌드 | `CMakeLists.txt` | `unit_converter_core`에 contract 소스 1건 추가 |
| GREEN 테스트 | `tests/red/test_track_a_ui_red.cpp` | TC-A-01만 golden 3줄 검증; TC-A-02~07 `FAIL("RED")` 유지 |
| Git | `1dde74c` | `feat(boundary): TC-A-01 GREEN convertFromInput happy path` |

## 3. 주요 결정·이슈

- **결정**: TC-A-01만 GREEN — `convertFromInput` 단일 API만 구현, `convert`/`convertAll`/`loadConfig` 등은 미구현(Track B RED 유지).
- **결정**: 출력 검증은 `test_table_meter_25_golden_lines`와 동일한 table half-up 1자리(`8.2 feet`, `2.7 yard`).
- **이슈(미해결)**: 계약 헤더 주석(6 decimals) vs PRD/README(1자리 half-up) — TC-A-06 JSON GREEN 시 정합 필요.
- **이슈(미해결)**: 실패 경로는 `std::invalid_argument` — TC-A-02~07 GREEN 시 ERR-* 매핑 검토.

## 4. 테스트·검증

| 명령 | 결과 |
|------|------|
| `cmake -S . -B build && cmake --build build` | 성공 |
| `unit_converter_tests "TC-A-01*"` | **PASS** (4 assertions) |
| `unit_converter_tests "~[red]"` | **PASS** (45 test cases, 85 assertions) |
| `unit_converter_tests "[red]"` | 1 passed, **12 failed** (`FAIL("RED")`, 기대) |
| `ctest --test-dir build` | 46 passed, 12 failed (red skeletons) |

## 5. 다음 단계

1. **TC-A-02** GREEN: `convertFromInput` 실패 시 `std::invalid_argument` (콜론 누락).
2. README RED To-Do TC-A-01 체크 및 순차 TC-A-03~07 GREEN.
3. Track B TC-B-01~06 — `UnitConverterContract` 나머지 API 구현.
