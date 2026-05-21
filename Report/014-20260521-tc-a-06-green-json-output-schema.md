# 작업 보고서 — TC-A-06 GREEN (JSON 출력 스키마·Source preservation)

- **보고서 번호**: 014
- **작성일**: 2026-05-21
- **브랜치**: green
- **커밋(작성 시점)**: 70f9dc5 (TC-A-06 변경 미커밋)

## 1. 작업 개요

Dual-Track TDD GREEN 6차 커밋으로 README RED To-Do **TC-A-06**(출력 포맷에 원 입력 단위·값 보존, JSON 스키마)을 처리했다. RED 스켈레톤 `FAIL("RED")`를 `convertFromInputAsJson("meter:2.5")` golden JSON 검증 본문으로 교체하고, `JsonOutputSerializer` 및 계약 API `convertFromInputAsJson`을 최소 구현했다. `source.unit`/`source.value`는 입력과 동일하고, `conversions[]` 길이는 Registry.size()(3), target 값은 `TableOutputSerializer::formatDisplayValue` half-up 1자리(`8.2`, `2.7`)를 재사용한다. TC-A-01~05 PASS·BCE 45건 회귀 유지, TC-A-07·Track B 7건 RED 스켈레톤은 계속 실패한다.

## 2. 변경·산출물 목록

| 구분 | 경로/항목 | 설명 |
|------|-----------|------|
| Boundary | `include/boundary/JsonOutputSerializer.hpp`, `src/boundary/JsonOutputSerializer.cpp` | PRD §6.2 JSON 직렬화 |
| 계약 구현 | `src/contract/UnitConverterContract.cpp` | `convertFromInputAsJson` — parser + service + JSON |
| 계약 주석 | `include/contract/UnitConverterContract.hpp` | 표시 규칙 1자리 half-up으로 정합 |
| 빌드 | `CMakeLists.txt` | `JsonOutputSerializer.cpp` core에 추가 |
| GREEN 테스트 | `tests/red/test_track_a_ui_red.cpp` | TC-A-06 golden JSON 1 assertion |
| README | `README.md` | RED To-Do TC-A-06 체크 `[x]` |
| 보고서 | `Report/014-20260521-tc-a-06-green-json-output-schema.md` | 본 문서 |
| 프롬프트 | `Prompting/014-20260521-tc-a-06-green-json-output-schema-Prompt.md`, `Prompting_user/014-20260521-tc-a-06-green-json-output-schema-User.md` | 세션 대화·User만 저장 |

## 3. 주요 결정·이슈

- **결정**: TC-A-06만 GREEN — `convertFromInputAsJson` 단일 API; table 경로(`convertFromInput`)는 기존 handler 유지.
- **결정**: `conversions[]`는 PRD §6.2대로 **Registry.size()=3**(meter/feet/yard); README 예시 2항목보다 PRD·OUT-03·AC-03 우선.
- **결정**: target 표시는 `TableOutputSerializer::formatDisplayValue` 재사용 — BCE golden과 동일 half-up.
- **이슈(미해결)**: CLI `--format=json` argv(S-04) 미구현 — 계약 API만 GREEN.
- **이슈(미해결)**: TC-A-07·Track B TC-B-01~06은 아직 `FAIL("RED")` 스켈레톤.

## 4. 테스트·검증

| 명령 | 결과 |
|------|------|
| `cmake -S . -B build; cmake --build build` | 성공 |
| Step 2 `unit_converter_tests "TC-A-06*"` | **FAIL** (`FAIL("RED")`, 기대) |
| Step 4 `unit_converter_tests "TC-A-06*"` | **PASS** (1 assertion) |
| `unit_converter_tests "TC-A-01*"` ~ `"TC-A-05*"` | **PASS** (각 1~4 assertions) |
| `unit_converter_tests "~[red]"` | **PASS** (45 test cases, 85 assertions) |
| `unit_converter_tests "[red]"` | 6 passed, **7 failed** (TC-A-07, TC-B-01~06 `FAIL("RED")`, 기대) |

## 5. 다음 단계

1. **TC-A-07** GREEN: `meter:0` → `std::invalid_argument`.
2. Track B **TC-B-01~06** — `UnitConverterContract` Domain API.
3. golden fixture `tests/fixtures/golden/meter_2_5.json` 커밋(S-10).
