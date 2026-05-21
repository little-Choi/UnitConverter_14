# 작업 보고서 — TC-B-02 GREEN (meter → yard convert)

- **보고서 번호**: 017
- **작성일**: 2026-05-21
- **브랜치**: green
- **커밋(작성 시점)**: 8de1014 (TC-B-02 GREEN·README 변경은 미커밋 — Step 7에서 부모 일괄 커밋 예정)

## 1. 작업 개요

Dual-Track TDD GREEN으로 Track B **TC-B-02**를 처리했다. RED 스켈레톤 `FAIL("RED")`를 `unit_converter::convert("meter", 1.0, "yard")` 검증(`Catch::Approx(1.09361).margin(1e-5)`)으로 교체했다. 프로덕션 코드는 변경하지 않았다 — `yard` 단위는 TC-B-01 시대 `UnitRegistry::bootstrapDefault()`에 이미 등록되어 있으며, contract `convert()`는 016에서 구현 완료. README Track B To-Do TC-B-02를 `[x]`로 표시했다. TC-B-03~06은 `FAIL("RED")` 유지.

## 2. 변경·산출물 목록

| 구분 | 경로/항목 | 설명 |
|------|-----------|------|
| GREEN 테스트 | `tests/red/test_track_b_logic_red.cpp` | TC-B-02: contract `convert` meter→yard + ε=1e-5; TC-B-03~06 RED 유지 |
| README | `README.md` | Track B TC-B-02 체크 `[x]` |
| 보고서 | `Report/017-20260521-tc-b-02-green-meter-to-yard-convert.md` | 본 문서 |
| 프롬프트 | `Prompting/017-20260521-tc-b-02-green-meter-to-yard-convert-Prompt.md`, `Prompting_user/017-20260521-tc-b-02-green-meter-to-yard-convert-User.md` | 세션 대화·User만 저장 |

**Git diff (작성 시점, 2 files, +7 / −2)**

```
 README.md                            | 2 +-
 tests/red/test_track_b_logic_red.cpp | 7 ++++++-
 2 files changed, 7 insertions(+), 2 deletions(-)
```

**최근 커밋 (git log -3)**

```
8de1014 feat(domain): TC-B-01 GREEN meter to feet convert and report 016
7b0ef07 feat(boundary): TC-A-07 GREEN zero value throws invalid_argument
b30586b feat(boundary): TC-A-06 GREEN JSON output schema and report 014
```

## 3. 주요 결정·이슈

- **결정**: TC-B-02만 GREEN — 테스트만 교체; 도메인·계약 API는 016·기존 registry로 충분.
- **결정**: TC-B-03~06은 스켈레톤 `FAIL("RED")` 유지 — Track B 순차 GREEN 정책.
- **결정**: 기대값 1.09361 (1 m → yd, ε=1e-5)는 README·요구사항과 정합.
- **이슈(미해결)**: TC-B-03~06 RED; GREEN 소스·README는 부모 Step 7 feature 커밋 예정.

## 4. 테스트·검증

| 명령 | 결과 |
|------|------|
| `cmake -S . -B build; cmake --build build` | 성공 (세션 기준) |
| Step 2 `unit_converter_tests "TC-B-02*"` | **FAIL** (`FAIL("RED")`, 기대) |
| Step 4 `unit_converter_tests "TC-B-02*"` | **PASS** (1 assertion) |
| `unit_converter_tests "TC-B-01*"` | **PASS** (회귀) |
| `unit_converter_tests "~[red]"` | **PASS** (45 test cases, 85 assertions) |
| `unit_converter_tests "[red]"` | 9 passed, **4 failed** (TC-B-03~06 `FAIL("RED")`, 기대) |

## 5. 다음 단계

1. Track B **TC-B-03** GREEN: `convert("feet", 1.0, "meter")` ≈ 0.30480 (역변환, ε=1e-5).
2. Step 7: TC-B-02 GREEN 소스 + README + 보고서 017·프롬프트 3종 일괄 `git commit` 및 `push`.
3. TC-B-04~06 — `convertAll`, registry, ConfigLoader 순차 GREEN.
