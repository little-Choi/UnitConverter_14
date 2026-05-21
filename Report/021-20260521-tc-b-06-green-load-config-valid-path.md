# 작업 보고서 — TC-B-06 GREEN (loadConfig 유효 경로 → 비율 적용)

- **보고서 번호**: 021
- **작성일**: 2026-05-21
- **브랜치**: green
- **커밋(작성 시점)**: Step 7에서 커밋 예정

## 1. 작업 개요

Dual-Track TDD GREEN으로 Track B **TC-B-06**을 처리했다. RED 스켈레톤 `FAIL("RED")`를 `unit_converter::loadConfig(units_valid.json)` 후 `convert("meter", 2.5, "feet")` 검증(설정 비율 `2.5/0.3048`, ε=1e-5)으로 교체했다. TEST_CASE명을 README·DEF-016에 맞게 `ConfigLoader_load_config_valid_path_applies_ratios`로 정정했다. 계약 API `loadConfig`를 `UnitConverterContract.cpp`에 추가하고, `JsonConfigLoader`/`YamlConfigLoader` 성공 시 `g_config_units`에 스냅샷을 보관한 뒤 `convert`의 `registryWithPending()`에서 로드된 레지스트리를 사용한다. README Track B To-Do TC-B-06을 `[x]`로 표시했다. TC-B-07(없는 경로 기본값)은 README 미체크·별도 TC 미포함.

## 2. 변경·산출물 목록

| 구분 | 경로/항목 | 설명 |
|------|-----------|------|
| GREEN 테스트 | `tests/red/test_track_b_logic_red.cpp` | TC-B-06: `loadConfig` + config 기반 `convert`; TEST_CASE명 정정 |
| 계약 구현 | `src/contract/UnitConverterContract.cpp` | `loadConfig`, `g_config_units`, `registryWithPending()` config 병합 |
| README | `README.md` | Track B TC-B-06 체크 `[x]` |
| 보고서 | `Report/021-20260521-tc-b-06-green-load-config-valid-path.md` | 본 문서 |
| 프롬프트 | `Prompting/021-20260521-tc-b-06-green-load-config-valid-path-Prompt.md`, `Prompting_user/021-20260521-tc-b-06-green-load-config-valid-path-User.md` | 세션 대화·User만 저장 |

**Git diff (작성 시점, 3 files, +40 / −3)**

```
 README.md                              |  2 +-
 src/contract/UnitConverterContract.cpp | 25 +++++++++++++++++++++++++
 tests/red/test_track_b_logic_red.cpp   | 16 ++++++++++++++--
 3 files changed, 40 insertions(+), 3 deletions(-)
```

**최근 커밋 (git log -3)**

```
0e93004 feat(domain): TC-B-05 GREEN registerUnit cubit then convert and report 020
9543dea feat(domain): TC-B-04 GREEN convertAll meter to all registered units and report 019
f3bd0b9 feat(domain): TC-B-03 GREEN feet to meter reverse convert and report 018
```

## 3. 주요 결정·이슈

- **결정**: TC-B-06만 GREEN — README 시나리오(유효 경로) 우선; RED 스켈레톤명(`missing_path`)은 TEST_CASE명 정정으로 정합.
- **결정**: `loadConfig` 실패(없는/잘못된 경로) 시 `g_config_units` 미설정 — 기본 레지스트리 유지(TC-B-07은 후속 GREEN).
- **결정**: `convertAll`/`convertFromInput`은 미변경 — TC-B-04 등 회귀·BCE 경로 유지.
- **이슈(미해결)**: TC-B-07 RED(README); `meterToFeetRatio`/`meterToYardRatio` 계약 선언은 미구현.

## 4. 테스트·검증

| 명령 | 결과 |
|------|------|
| `cmake -S . -B build; cmake --build build` | 성공 |
| Step 2 `unit_converter_tests "TC-B-06*"` | **FAIL** (`FAIL("RED")`, 기대) |
| Step 4 `unit_converter_tests "TC-B-06*"` | **PASS** (1 assertion) |
| `unit_converter_tests "TC-B-01*"` ~ `"TC-B-05*"` | **PASS** (회귀) |
| `unit_converter_tests "~[red]"` | **PASS** (45 test cases, 85 assertions) |
| `unit_converter_tests "[red]"` | **PASS** (13 test cases, 20 assertions) |

## 5. 다음 단계

1. Track B **TC-B-07** GREEN: `loadConfig(없는 경로)` → 기본값(3.28084/1.09361) 유지.
2. Step 7 feature 커밋: TC-B-06 GREEN 소스 + README + 보고서 021·프롬프트.
