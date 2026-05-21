# 작업 보고서 — TC-B-04 GREEN (convertAll meter → all units)

- **보고서 번호**: 019
- **작성일**: 2026-05-21
- **브랜치**: green
- **커밋(작성 시점)**: f3bd0b9 (TC-B-04 GREEN·README 변경은 Step 7에서 커밋 예정)

## 1. 작업 개요

Dual-Track TDD GREEN으로 Track B **TC-B-04**를 처리했다. RED 스켈레톤 `FAIL("RED")`를 `unit_converter::convertAll("meter", 1.0)` 검증(등록 단위 3건, meter/feet/yard 값·ε=1e-5)으로 교체했다. 계약 API `std::vector<ConvertAllEntry> convertAll(...)`를 `UnitConverterContract.cpp`에 추가해 `UnitRegistry::bootstrapDefault()`와 `LengthConversionService::convertAll`에 위임한다. README Track B To-Do TC-B-04를 `[x]`로 표시했다. TC-B-05~06은 `FAIL("RED")` 유지.

## 2. 변경·산출물 목록

| 구분 | 경로/항목 | 설명 |
|------|-----------|------|
| GREEN 테스트 | `tests/red/test_track_b_logic_red.cpp` | TC-B-04: contract `convertAll` meter:1.0 → 3 entries; TC-B-05~06 RED 유지 |
| 계약 구현 | `src/contract/UnitConverterContract.cpp` | `convertAll` — domain `convertAll` 결과를 `ConvertAllEntry`로 매핑 |
| README | `README.md` | Track B TC-B-04 체크 `[x]` |
| 보고서 | `Report/019-20260521-tc-b-04-green-convert-all-meter.md` | 본 문서 |
| 프롬프트 | `Prompting/019-20260521-tc-b-04-green-convert-all-meter-Prompt.md`, `Prompting_user/019-20260521-tc-b-04-green-convert-all-meter-User.md` | 세션 대화·User만 저장 |

**Git diff (작성 시점, 3 files, +35 / −3)**

```
 README.md                              |  2 +-
 src/contract/UnitConverterContract.cpp | 12 ++++++++++++
 tests/red/test_track_b_logic_red.cpp   | 24 ++++++++++++++++++++++--
 3 files changed, 35 insertions(+), 3 deletions(-)
```

**최근 커밋 (git log -3)**

```
f3bd0b9 feat(domain): TC-B-03 GREEN feet to meter reverse convert and report 018
a3142f2 feat(domain): TC-B-02 GREEN meter to yard convert and report 017
0896f20 docs: 보고서 017 및 프롬프트 저장 (tc-b-02-green-meter-to-yard-convert)
```

## 3. 주요 결정·이슈

- **결정**: TC-B-04만 GREEN — `convertAll` 계약 구현 + 테스트; domain `LengthConversionService::convertAll`은 BCE 단계에서 이미 구현(DEF-004 해소).
- **결정**: TEST_CASE명 `UnitRegistry_register_unit_then_convert` → `convertAll_meter_returns_all_registered_units` (README·DEF-004 정합).
- **결정**: TC-B-05~06은 스켈레톤 `FAIL("RED")` 유지 — Track B 순차 GREEN 정책.
- **이슈(미해결)**: TC-B-05~06 RED; TC-B-05는 README상 `registerUnit("cubit")` 시나리오.

## 4. 테스트·검증

| 명령 | 결과 |
|------|------|
| `cmake -S . -B build; cmake --build build` | 성공 |
| Step 2 `unit_converter_tests "TC-B-04*"` | **FAIL** (`FAIL("RED")`, 기대) |
| Step 4 `unit_converter_tests "TC-B-04*"` | **PASS** (5 assertions) |
| `unit_converter_tests "TC-B-01*"` / `"TC-B-02*"` / `"TC-B-03*"` | **PASS** (회귀) |
| `unit_converter_tests "~[red]"` | **PASS** (45 test cases, 85 assertions) |
| `unit_converter_tests "[red]"` | 11 passed, **2 failed** (TC-B-05~06 `FAIL("RED")`, 기대) |

## 5. 다음 단계

1. Track B **TC-B-05** GREEN: `registerUnit("cubit", 0.4572)` 후 변환 가능.
2. TC-B-06~07 — ConfigLoader 순차 GREEN.
3. Step 7 feature 커밋: TC-B-04 GREEN 소스 + README + 보고서 019·프롬프트.
