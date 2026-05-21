# 작업 보고서 — 전체 테스트·커버리지 Gate 검증

- **보고서 번호**: 027
- **작성일**: 2026-05-21
- **브랜치**: refactoring
- **커밋(작성 시점)**: ae63871

## 1. 작업 개요

사용자 요청에 따라 `cmake -S . -B build`, `cmake --build build`, `ctest --test-dir build -V`로 전체 테스트를 실행하고, `build-cov`(`-DENABLE_COVERAGE=ON`)에서 lcov로 Domain·Boundary 커버리지 Gate를 재측정했다. TC-A-01~07, TC-B-01~07, Golden Master 회귀, if-else 제거(UnitRegistry), 매직 넘버 인라인 부재, Domain/Boundary 분리 여부를 코드·테스트 결과로 확인했다. `build` 및 `build-cov`(클린 재빌드 후) 모두 **70/70 PASS**였고, Domain line **95.5%**, Boundary line **92.9%**로 Gate(≥95% / ≥85%)를 충족했다.

## 2. 변경·산출물 목록

| 구분 | 경로/항목 | 설명 |
|------|-----------|------|
| 보고서 | `Report/027-20260521-full-test-coverage-verification.md` | 본 문서 |
| 프롬프트 | `Prompting/027-20260521-full-test-coverage-verification-Prompt.md` | 세션 전체 대화 |
| User | `Prompting_user/027-20260521-full-test-coverage-verification-User.md` | User 메시지만 |
| 검증(빌드) | `build/` | Release/Debug 빌드 — 70 tests PASS |
| 검증(커버리지) | `build-cov/` | MinGW + `--coverage` — lcov Gate PASS |

> 본 세션은 **검증·문서화**만 수행. 소스 코드 변경 없음.

## 3. 주요 결정·이슈

- **결정**: Gate 측정은 `lcov --extract`로 `src/domain/*`, `src/boundary/*`만 추출 (`test_plan.md` §7, Report 023과 동일 기준).
- **결정**: 비율 상수 `3.28084`/`1.09361`은 `src/domain/UnitRegistry.cpp`의 `kMeterToFeet`/`kMeterToYard`만 — `src/` 기타 `.cpp` 인라인 **0건**.
- **결정**: 변환 로직은 `LengthConversionService` + `UnitRegistry` lookup — 단위별 if-else 체인 **없음**; `UnitConverter.cpp`는 CLI·Handler 위임만.
- **이슈(참고)**: `build-cov`에서 `.gcda`/`.gcno` 불일치 시 Golden Master가 일시 FAIL할 수 있음 — `build-cov` 삭제 후 재빌드·전체 `ctest`로 해소 확인.
- **이슈(미해결)**: README **전체 TOTAL 90%+** 항목은 여전히 미체크.
- **이슈(참고)**: `UnitConverter.cpp` lcov line **66.7%** — CLI `main` 분기만, 변환 로직 없음.

## 4. 테스트·검증

| 명령 | 결과 |
|------|------|
| `cmake -S . -B build; cmake --build build` | 성공 |
| `ctest --test-dir build -V` | **70/70 PASS** |
| TC-A-01~07 (ctest #8~#14) | **PASS** |
| TC-B-01~07 (ctest #1~#7) | **PASS** |
| `golden_master_cli_stdout_approval` | **PASS** (`tests/golden_master_expected.txt` 일치) |
| `cmake -S . -B build-cov -G "MinGW Makefiles" -DENABLE_COVERAGE=ON` | 성공 (클린 재생성) |
| `ctest --test-dir build-cov` | **70/70 PASS** |
| `lcov --extract … '*/src/domain/*'` | **95.5%** line (42/44) — Gate **PASS** (≥95%) |
| `lcov --extract … '*/src/boundary/*'` | **92.9%** line (105/113) — Gate **PASS** (≥85%) |
| `lcov --extract … '*UnitConverter.cpp*'` | **66.7%** line (16/24) — 참고 |
| `grep 3.28084` in `src/*.cpp` | **UnitRegistry.cpp만** |
| Domain/Boundary 분리 | `src/domain/*`, `src/boundary/*`, `include/*` — **완료** |

### 체크리스트 (사용자 요청 항목)

| 확인 항목 | 결과 |
|-----------|------|
| TC-A-01~07 PASS | ✅ |
| TC-B-01~07 PASS | ✅ |
| Golden Master PASS | ✅ |
| if-else 체인 제거 (UnitRegistry) | ✅ |
| 매직 넘버 인라인 없음 | ✅ |
| Domain / Boundary 분리 | ✅ |
| Domain ≥ 95% | ✅ 95.5% |
| Boundary ≥ 85% | ✅ 92.9% |

## 5. 다음 단계

1. 선택: README **전체 TOTAL 90%+** Gate — core-only lcov extract 정의 후 측정·체크.
2. 선택: `build-cov` Golden Master 안정화 — gcov stderr 오염 시 CI에서 클린 빌드 정책 문서화.
3. Refactoring 브랜치 마무리 후 PR·머지 시 본 Gate 결과를 AC 증빙으로 첨부.
