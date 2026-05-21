# 작업 보고서 — 커버리지 Gate (Domain 95% / Boundary 85%)

- **보고서 번호**: 023
- **작성일**: 2026-05-21
- **브랜치**: green
- **커밋(작성 시점)**: bd55815 (선행); 본 세션 소스·문서는 Step 7 커밋 예정

## 1. 작업 개요

TC-A-01~07·TC-B-01~07 및 전체 `ctest` 59건 PASS를 확인한 뒤, `build-cov`(`-DENABLE_COVERAGE=ON`)에서 lcov로 레이어별 커버리지를 측정했다. 초기 Gate 결과는 Domain **81.8%**, Boundary **73.8%**로 미달이었다. 미커버 분기(레지스트리 실패·`clear`/`loadFromDefinitions`, Domain unknown-unit throw, `ErrorCodes` 전 ERR prefix, 파서 empty/trim·등록 포맷)를 채우는 단위 테스트 9건을 추가해 Domain **95.5%**, Boundary **92.5%**로 Gate를 충족했다. 비율 상수 3.28084/1.09361은 `UnitRegistry.cpp` named constant만 사용·`main()`에 변환 로직 없음을 재확인했고, README 커버리지 To-Do Domain·Boundary 항목을 `[x]`로 갱신했다.

## 2. 변경·산출물 목록

| 구분 | 경로/항목 | 설명 |
|------|-----------|------|
| Domain 테스트 | `tests/domain/test_unit_registry.cpp` | `registerUnit` 거부, `clear`/`loadFromDefinitions` |
| Domain 테스트 | `tests/domain/test_length_conversion.cpp` | unknown unit → `invalid_argument` |
| Boundary 테스트 | `tests/boundary/test_error_codes.cpp` | **신규** — 모든 `ErrorCode` prefix + default |
| Boundary 테스트 | `tests/boundary/test_convert_parser.cpp` | empty input, whitespace trim |
| Boundary 테스트 | `tests/boundary/test_validation_errors.cpp` | 등록 포맷·meter 재정의·파서 성공 |
| 빌드 | `CMakeLists.txt` | `test_error_codes.cpp` 등록 |
| README | `README.md` | Domain 95.5% / Boundary 92.5% Gate 체크 `[x]` |
| 보고서 | `Report/023-20260521-coverage-gate-domain-boundary.md` | 본 문서 |
| 프롬프트 | `Prompting/023-*.md`, `Prompting_user/023-*.md` | 세션 대화·User 저장 |

## 3. 주요 결정·이슈

- **결정**: Gate 달성은 `src/domain/*`, `src/boundary/*` lcov extract 기준 — Catch2·`tests/*` 제외(`test_plan.md` §7).
- **결정**: `ErrorCodes.cpp` 전 switch 분기는 단일 테스트로 일괄 hit — Boundary 73.8% → 92.5%에 기여.
- **결정**: 비율 상수는 Domain `UnitRegistry`에만 정의(NG-03·README) — Boundary/`UnitConverter.cpp` 인라인 없음.
- **이슈(미해결)**: README **전체 TOTAL 90%+** 미체크; `UnitConverter.cpp` CLI 분기는 E2E 미실행으로 line ~36% (`build-cov` gcov).
- **이슈(미해결)**: `RegisterInputParser.cpp` 80.0% — `stod` catch 분기 등 일부 잔여.

## 4. 테스트·검증

| 명령 | 결과 |
|------|------|
| `cmake -S . -B build; cmake --build build; ctest --test-dir build -V` | **68/68 PASS** (0 failures) |
| TC-A-01~07 (ctest #8~#14) | **PASS** |
| TC-B-01~07 (ctest #1~#7) | **PASS** |
| `cmake -S . -B build-cov -G "MinGW Makefiles" -DENABLE_COVERAGE=ON` | 성공 |
| `ctest --test-dir build-cov` | **68/68 PASS** |
| `lcov --extract … '*/src/domain/*'` | **95.5%** line (42/44) — Gate **PASS** (≥95%) |
| `lcov --extract … '*/src/boundary/*'` | **92.5%** line (99/107) — Gate **PASS** (≥85%) |
| `gcov` on `UnitConverter.cpp` (exe 1회) | 36.0% line — CLI·`--config=` 미커버(참고) |
| `grep 3.28084` in `src/` (excl. registry) | **0** — 인라인 magic 없음 |
| `main()` 변환 로직 | **없음** — Handler 위임만 |

## 5. 다음 단계

1. Step 7: `test:` 커버리지 보강 커밋 + `docs:` 보고서 023·프롬프트 push.
2. 선택: CLI E2E 또는 통합 테스트로 `UnitConverter.cpp` 분기 커버리지 보강.
3. 선택: README **전체 TOTAL 90%+** Gate — core-only lcov extract 정의 후 측정.
