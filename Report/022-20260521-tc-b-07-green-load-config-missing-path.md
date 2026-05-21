# 작업 보고서 — TC-B-07 GREEN (loadConfig 없는 경로 → 기본값 유지)

- **보고서 번호**: 022
- **작성일**: 2026-05-21
- **브랜치**: green
- **커밋(작성 시점)**: Step 7에서 커밋 예정

## 1. 작업 개요

Dual-Track TDD GREEN으로 Track B **TC-B-07**을 처리했다. `tests/red/test_track_b_logic_red.cpp`에 `ConfigLoader_load_config_missing_path_keeps_default_ratios` TEST_CASE를 추가했다. 비기본 픽스처 `units_non_default.json`(feet·yard `meters_per_unit` 0.5) 로드 후 없는 경로 `loadConfig` 시 기본 비율(3.28084 / 1.09361)로 복원되는지 검증한다. Step 2에서 `g_config_units`가 실패 시 초기화되지 않아 **FAIL**(feet 2.0 vs 3.28084)을 확인했다. `UnitConverterContract.cpp`의 `loadConfig`에서 Json/Yaml 모두 실패 시 `g_config_units.reset()`로 기본 레지스트리를 복원한다. README Track B To-Do TC-B-07을 `[x]`로 표시했다.

## 2. 변경·산출물 목록

| 구분 | 경로/항목 | 설명 |
|------|-----------|------|
| GREEN 테스트 | `tests/red/test_track_b_logic_red.cpp` | TC-B-07: custom config → missing path → default ratios |
| 픽스처 | `tests/fixtures/units_non_default.json` | 비기본 비율(1 m = 2 ft) 검증용 |
| 계약 구현 | `src/contract/UnitConverterContract.cpp` | `loadConfig` 실패 시 `g_config_units.reset()` |
| README | `README.md` | Track B TC-B-07 체크 `[x]` |
| 보고서 | `Report/022-20260521-tc-b-07-green-load-config-missing-path.md` | 본 문서 |
| 프롬프트 | `Prompting/022-*.md`, `Prompting_user/022-*.md` | 세션 대화·User 저장 |

## 3. 주요 결정·이슈

- **결정**: TC-B-07만 GREEN — `units_valid.json` 비율이 기본값과 수치상 동일해 단순 missing-path 검증만으로는 RED 재현 불가; `units_non_default.json`으로 선행 로드 후 복원 시나리오 명시.
- **결정**: `loadConfig` 실패 시 `g_config_units` 해제 — TC-B-06 이후 stale config 방지.
- **이슈(미해결)**: `meterToFeetRatio`/`meterToYardRatio` 계약 선언은 헤더에만 존재·미구현(DEF-017 일부).

## 4. 테스트·검증

| 명령 | 결과 |
|------|------|
| `cmake -S . -B build; cmake --build build` | 성공 |
| Step 2 `unit_converter_tests "TC-B-07*"` | **FAIL** (feet 2.0 vs Approx 3.28084) |
| Step 4 `unit_converter_tests "TC-B-07*"` | **PASS** (3 assertions) |
| `unit_converter_tests "TC-B-01*"` ~ `"TC-B-06*"` | **PASS** (회귀) |
| `unit_converter_tests "[red]"` | **PASS** (14 test cases, 23 assertions) |
| `unit_converter_tests "~[red]"` | **PASS** (BCE/GREEN 회귀) |

## 5. 다음 단계

1. Track B To-Do 7건 완료 — Domain 커버리지 Gate(95%+) 또는 Track A 후속 TC 검토.
2. Step 7 feature 커밋: TC-B-07 GREEN 소스 + README + 보고서 022·프롬프트.
