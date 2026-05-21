# 작업 보고서 — 전체 테스트·커버리지·Bonus·Golden Master 검증

- **보고서 번호**: 034
- **작성일**: 2026-05-21
- **브랜치**: `feature`
- **커밋(작성 시점)**: `4f4b0aa`

## 1. 작업 개요

Report 033(Bonus `DecayingUnit` GREEN) 이후, 사용자 요청에 따라 **전체 테스트·lcov 커버리지 Gate·Golden Master·Bonus BT-01~06**를 일괄 재검증했다. `build`에서 `ctest` **71/71 PASS**, `build-cov`(`-DENABLE_COVERAGE=ON`)에서 동일 **71/71 PASS** 및 Domain **95.5%**·Boundary **92.9%** Gate 충족을 확인했다. `meter:2.5` 출력은 Golden Master·TC-A-01·CLI 직접 실행에서 **8.2 feet / 2.7 yard** 불변을 확인했다. `registerUnit("cubit", -1.0)`은 BT-04(음수 비율) 및 단독 실행으로 `std::invalid_argument` throw를 확인했다. Report 032(RED) 대비 Bonus는 **GREEN 완료** 상태이다.

## 2. 변경·산출물 목록

| 구분 | 경로/항목 | 설명 |
|------|-----------|------|
| 검증 | `build/` | 기본 Debug 빌드·전체 ctest |
| 검증 | `build-cov/` | `-DENABLE_COVERAGE=ON` 빌드·lcov 측정 |
| 소스 | (변경 없음) | 본 세션은 검증·문서만 — 코드 diff 없음 |
| 보고서 | `Report/034-20260521-full-test-coverage-bonus-verification.md` | 본 문서 |
| 프롬프트 | `Prompting/034-…-Prompt.md`, `Prompting_user/034-…-User.md` | 세션 기록 |
| 선행 | `Report/032` (RED), `Report/033` (GREEN) | Bonus DecayingUnit 이력 |

## 3. 주요 결정·이슈

- **결정**: Gate 기준은 Report 023·`test_plan.md` §7과 동일 — `src/domain/*` line ≥95%, `src/boundary/*` line ≥85%, Catch2·`tests/*` 제외.
- **결정**: Bonus 검증은 ctest `#1 DecayingUnit_bonus_register_and_convert` 및 `[bonus]` 필터(6 SECTION·11 assertions)로 수행.
- **이슈(해결)**: `UnitConverter.exe`를 stdin 없이 실행 시 대화형 입력 대기로 hang → `echo meter:2.5 \| UnitConverter.exe`로 CLI 출력 확인.
- **이슈(해결)**: 루트에서 `gcov -c UnitConverter.cpp`는 `.gcno` 경로 불일치로 실패 → `build-cov`에서 `lcov --extract '*UnitConverter.cpp*'`로 **66.7%** line 측정(참고용).
- **참고**: BT-04는 `registerUnit("bad", -0.4572)`이나, 구현상 `meters_per_unit <= 0.0` 검사로 `("cubit", -1.0)`도 동일하게 throw.

## 4. 테스트·검증

### 4.1 전체 테스트 (`build`)

| 명령 | 결과 |
|------|------|
| `cmake -S . -B build -G "MinGW Makefiles"` | 성공 |
| `cmake --build build` | 성공 |
| `ctest --test-dir build -V` | **71/71 PASS** (0 failures, ~2.9s) |

### 4.2 핵심 TC·Bonus·Golden Master

| 확인 항목 | ctest / 실행 | 결과 |
|-----------|--------------|------|
| **BT-01~06** | `#1 DecayingUnit_bonus_register_and_convert` | **PASS** (11 assertions) |
| **TC-A-01~07** | `#9`~`#15` | **PASS** |
| **TC-B-01~07** | `#2`~`#8` | **PASS** |
| **Golden Master** | `#16 golden_master_cli_stdout_approval` | **PASS** |
| **meter:2.5 출력** | TC-A-01, `golden_master_expected.txt`, CLI | **8.2 feet / 2.7 yard** 불변 |
| **`registerUnit("cubit", -1.0)`** | BT-04 + 단독 실행 | **`std::invalid_argument`** |

BT-01~06 SECTION 요약:

| BT | 검증 내용 |
|----|-----------|
| BT-01 | cubit → meter ≈ 0.4572 |
| BT-02 | meter → cubit 역변환 |
| BT-03 | cubit → feet 교차 변환 |
| BT-04 | 음수 비율 → `invalid_argument` |
| BT-05 | `convertAll` 4단위 |
| BT-06 | cubit 등록 후 meter→feet 3.28084 유지 |

### 4.3 커버리지 (`build-cov`)

| 명령 | 결과 |
|------|------|
| `cmake -S . -B build-cov -G "MinGW Makefiles" -DENABLE_COVERAGE=ON` | 성공 |
| `cmake --build build-cov` | 성공 |
| `ctest --test-dir build-cov` | **71/71 PASS** |
| `lcov --extract … '*/src/domain/*'` | **95.5%** line (42/44) — Gate **PASS** (≥95%) |
| `lcov --extract … '*/src/boundary/*'` | **92.9%** line (105/113) — Gate **PASS** (≥85%) |
| `lcov --extract … '*UnitConverter.cpp*'` | **66.7%** line (16/24) — 참고 |

### 4.4 체크리스트 종합

| 항목 | 결과 |
|------|------|
| BT-01~06 PASS (신규 Bonus) | **PASS** |
| TC-A-01~07, TC-B-01~07 PASS (회귀) | **PASS** |
| Golden Master PASS (meter/feet/yard 불변) | **PASS** |
| `registerUnit("cubit", -1.0)` → `invalid_argument` | **PASS** |
| Domain 커버리지 ≥ 95% | **95.5% PASS** |
| Boundary 커버리지 ≥ 85% | **92.9% PASS** |

## 5. 다음 단계

1. README Bonus·검증 To-Do `[x]` 반영 여부 확인(필요 시 문서 커밋).
2. `origin/feature` push — 원격 동기화 필요 시.
3. 선택: CLI E2E로 `UnitConverter.cpp` 미커버 분기 보강(현재 lcov 66.7%).
