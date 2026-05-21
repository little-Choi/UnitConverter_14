# 작업 보고서 — TC-B-03 GREEN (feet → meter 역변환)

- **보고서 번호**: 018
- **작성일**: 2026-05-21
- **브랜치**: green
- **커밋(작성 시점)**: a3142f2 (TC-B-03 GREEN·README 변경은 Step 7에서 커밋 예정)

## 1. 작업 개요

Dual-Track TDD GREEN으로 Track B **TC-B-03**을 처리했다. RED 스켈레톤 `FAIL("RED")`를 `unit_converter::convert("feet", 1.0, "meter")` 검증(`Catch::Approx(0.30480).margin(1e-5)`)으로 교체했다. TEST_CASE 이름을 README·요구사항(역변환)에 맞게 `convert_feet_to_meter_within_1e_5`로 정정했다. 프로덕션 코드는 변경하지 않았다 — `feet`는 `UnitRegistry::bootstrapDefault()`에 등록되어 있으며, hub 경로 `convert()`는 016에서 구현 완료. README Track B To-Do TC-B-03을 `[x]`로 표시했다. TC-B-04~06은 `FAIL("RED")` 유지.

## 2. 변경·산출물 목록

| 구분 | 경로/항목 | 설명 |
|------|-----------|------|
| GREEN 테스트 | `tests/red/test_track_b_logic_red.cpp` | TC-B-03: contract `convert` feet→meter + ε=1e-5; TC-B-04~06 RED 유지 |
| README | `README.md` | Track B TC-B-03 체크 `[x]` |
| 보고서 | `Report/018-20260521-tc-b-03-green-feet-to-meter-convert.md` | 본 문서 |
| 프롬프트 | `Prompting/018-20260521-tc-b-03-green-feet-to-meter-convert-Prompt.md`, `Prompting_user/018-20260521-tc-b-03-green-feet-to-meter-convert-User.md` | 세션 대화·User만 저장 |

**Git diff (작성 시점, 2 files, +8 / −3)**

```
 README.md                            | 2 +-
 tests/red/test_track_b_logic_red.cpp | 9 +++++++--
 2 files changed, 8 insertions(+), 3 deletions(-)
```

**최근 커밋 (git log -3)**

```
a3142f2 feat(domain): TC-B-02 GREEN meter to yard convert and report 017
0896f20 docs: 보고서 017 및 프롬프트 저장 (tc-b-02-green-meter-to-yard-convert)
8de1014 feat(domain): TC-B-01 GREEN meter to feet convert and report 016
```

## 3. 주요 결정·이슈

- **결정**: TC-B-03만 GREEN — 테스트만 교체; `1.0 feet → meter`는 `meters_per_unit(feet)=1/3.28084`로 0.30480 (ε=1e-5).
- **결정**: TC-B-04~06은 스켈레톤 `FAIL("RED")` 유지 — Track B 순차 GREEN 정책.
- **결정**: 잘못된 스켈레톤명 `convert_all_returns_every_registered_unit` → `convert_feet_to_meter_within_1e_5` (README TC-B-03·DEF-003 정합).
- **이슈(미해결)**: TC-B-04~06 RED; TC-B-04는 README상 `convertAll` 시나리오.

## 4. 테스트·검증

| 명령 | 결과 |
|------|------|
| `cmake -S . -B build; cmake --build build` | 성공 |
| Step 2 `unit_converter_tests "TC-B-03*"` | **FAIL** (`FAIL("RED")`, 기대) |
| Step 4 `unit_converter_tests "TC-B-03*"` | **PASS** (1 assertion) |
| `unit_converter_tests "TC-B-01*"` / `"TC-B-02*"` | **PASS** (회귀) |
| `unit_converter_tests "~[red]"` | **PASS** (45 test cases, 85 assertions) |
| `unit_converter_tests "[red]"` | 10 passed, **3 failed** (TC-B-04~06 `FAIL("RED")`, 기대) |

## 5. 다음 단계

1. Track B **TC-B-04** GREEN: `convertAll("meter", 1.0)` — 모든 등록 단위 반환.
2. TC-B-05~07 — registry·ConfigLoader 순차 GREEN.
3. Step 7 feature 커밋: TC-B-03 GREEN 소스 + README + 보고서 018·프롬프트.
