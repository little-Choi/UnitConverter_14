# 작업 보고서 — TC-B-05 GREEN (registerUnit cubit → convert)

- **보고서 번호**: 020
- **작성일**: 2026-05-21
- **브랜치**: green
- **커밋(작성 시점)**: Step 7에서 커밋 예정

## 1. 작업 개요

Dual-Track TDD GREEN으로 Track B **TC-B-05**를 처리했다. RED 스켈레톤 `FAIL("RED")`를 `unit_converter::registerUnit("cubit", 0.4572)` 후 `convert("cubit", 1.0, "meter")` 검증(`Catch::Approx(0.4572).margin(1e-5)`)으로 교체했다. TEST_CASE명을 README·DEF-015에 맞게 `UnitRegistry_register_unit_cubit_then_convert`로 정정했다. 계약 API `registerUnit`을 `UnitConverterContract.cpp`에 추가하고, `convert` 호출 시 pending 등록 단위를 `bootstrapDefault()` 레지스트리에 병합한 뒤 one-shot으로 소비한다. README Track B To-Do TC-B-05를 `[x]`로 표시했다. TC-B-06은 `FAIL("RED")` 유지.

## 2. 변경·산출물 목록

| 구분 | 경로/항목 | 설명 |
|------|-----------|------|
| GREEN 테스트 | `tests/red/test_track_b_logic_red.cpp` | TC-B-05: `registerUnit` + `convert` cubit→meter; TC-B-06 RED 유지 |
| 계약 구현 | `src/contract/UnitConverterContract.cpp` | `registerUnit`, `registryWithPending()` — pending 등록 후 `convert`에서 병합·clear |
| README | `README.md` | Track B TC-B-05 체크 `[x]` |
| 보고서 | `Report/020-20260521-tc-b-05-green-register-unit-cubit.md` | 본 문서 |
| 프롬프트 | `Prompting/020-20260521-tc-b-05-green-register-unit-cubit-Prompt.md`, `Prompting_user/020-20260521-tc-b-05-green-register-unit-cubit-User.md` | 세션 대화·User만 저장 |

## 3. 주요 결정·이슈

- **결정**: TC-B-05만 GREEN — `registerUnit` + `convert` pending 병합; `convertAll`/`convertFromInput`은 미변경(회귀·TC-B-04 size=3 유지).
- **결정**: pending 등록은 `convert` 1회 소비 후 clear — TC-B-04 등 후속 테스트에 cubit 잔류 방지.
- **결정**: TC-B-06은 스켈레톤 `FAIL("RED")` 유지 — Track B 순차 GREEN 정책.
- **이슈(미해결)**: TC-B-06 RED; README TC-B-06~07은 `loadConfig` 시나리오(테스트 스켈레톤명은 ConfigLoader).

## 4. 테스트·검증

| 명령 | 결과 |
|------|------|
| `cmake -S . -B build; cmake --build build` | 성공 |
| Step 2 `unit_converter_tests "TC-B-05*"` | **FAIL** (`FAIL("RED")`, 기대) |
| Step 4 `unit_converter_tests "TC-B-05*"` | **PASS** (1 assertion) |
| `unit_converter_tests "TC-B-01*"` ~ `"TC-B-04*"` | **PASS** (회귀) |
| `unit_converter_tests "TC-B-06*"` | **FAIL** (`FAIL("RED")`, 기대) |
| `unit_converter_tests "~[red]"` | **PASS** (45 test cases, 85 assertions) |
| `unit_converter_tests "[red]"` | 12 passed, **1 failed** (TC-B-06 RED, 기대) |

## 5. 다음 단계

1. Track B **TC-B-06** GREEN: `loadConfig` 유효 경로 또는 README/스켈레톤 정합 후 ConfigLoader 계약.
2. TC-B-07 — `loadConfig` 없는 경로 기본값 유지.
3. Step 7 feature 커밋: TC-B-05 GREEN 소스 + README + 보고서 020·프롬프트.
