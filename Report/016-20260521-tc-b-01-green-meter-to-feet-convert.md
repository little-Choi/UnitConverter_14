# 작업 보고서 — TC-B-01 GREEN (meter → feet convert)

- **보고서 번호**: 016
- **작성일**: 2026-05-21
- **브랜치**: green
- **커밋(작성 시점)**: 7b0ef07 (미커밋 — GREEN·보고서는 Step 7에서 일괄 커밋 예정)

## 1. 작업 개요

Dual-Track TDD GREEN으로 Track B **TC-B-01**을 처리했다. RED 스켈레톤 `FAIL("RED")`를 `unit_converter::convert("meter", 2.5, "feet")` 검증(`Catch::Approx(8.20210).margin(1e-5)`)으로 교체했다. 계약 API `double convert(from, value, to)`를 `UnitConverterContract.cpp`에 추가해 `UnitRegistry::bootstrapDefault()`와 `LengthConversionService::convert`에 위임한다. README Track B To-Do TC-B-01을 `[x]`로 표시했다. TC-B-02~06은 `FAIL("RED")` 유지.

## 2. 변경·산출물 목록

| 구분 | 경로/항목 | 설명 |
|------|-----------|------|
| GREEN 테스트 | `tests/red/test_track_b_logic_red.cpp` | TC-B-01: contract `convert` + ε=1e-5; TC-B-02~06 RED 유지 |
| 프로덕션 | `src/contract/UnitConverterContract.cpp` | `convert()` 구현 추가 (registry bootstrap + domain convert) |
| README | `README.md` | Track B TC-B-01 체크 `[x]` |
| 보고서 | `Report/016-20260521-tc-b-01-green-meter-to-feet-convert.md` | 본 문서 |
| 프롬프트 | `Prompting/016-20260521-tc-b-01-green-meter-to-feet-convert-Prompt.md`, `Prompting_user/016-20260521-tc-b-01-green-meter-to-feet-convert-User.md` | 세션 대화·User만 저장 |

**Git diff (작성 시점, 3 files, +16 / −2)**

```
 README.md                              |  2 +-
 src/contract/UnitConverterContract.cpp |  6 ++++++
 tests/red/test_track_b_logic_red.cpp   | 10 +++++++++-
```

## 3. 주요 결정·이슈

- **결정**: TC-B-01만 GREEN — Domain raw `double` 경로를 contract `convert`로 노출, 테스트는 README·test_plan D-01(2.5 m → ft)와 정합.
- **결정**: TC-B-02~06은 스켈레톤 `FAIL("RED")` 유지 — Track B 순차 GREEN 정책.
- **결정**: 헤더 `UnitConverterContract.hpp`의 `convert` 선언은 기존 유지, 이번 세션에서 `.cpp` 구현만 추가.
- **이슈(미해결)**: TC-B-02~06 RED; GitHub push는 본 에이전트에서 수행하지 않음(부모 Step 7 일괄 커밋).

## 4. 테스트·검증

| 명령 | 결과 |
|------|------|
| `cmake -S . -B build; cmake --build build` | 성공 |
| Step 2 `unit_converter_tests "TC-B-01*"` | **FAIL** (`FAIL("RED")`, 기대) |
| Step 4 `unit_converter_tests "TC-B-01*"` | **PASS** (1 assertion) |
| `unit_converter_tests "~[red]"` | **PASS** (45 test cases, 85 assertions) |
| `unit_converter_tests "[red]"` | 8 passed, **5 failed** (TC-B-02~06 `FAIL("RED")`, 기대) |
| `unit_converter_tests "TC-A-01*"` | **PASS** (회귀) |
| `unit_converter_tests "TC-A-07*"` | **PASS** (회귀) |

## 5. 다음 단계

1. Track B **TC-B-02** GREEN: `convert("meter", 1.0, "yard")` ≈ 1.09361 (ε=1e-5).
2. Step 7: GREEN 소스 + 보고서 016·프롬프트 3종 일괄 `git commit` 및 `push`.
3. TC-B-03~06 — `convertAll`, registry, ConfigLoader 순차 GREEN.
