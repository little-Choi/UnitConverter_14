# 작업 보고서 — Dual-Track REFACTOR (ApplicationBootstrap · ConsoleErrorWriter)

- **보고서 번호**: 026
- **작성일**: 2026-05-21
- **브랜치**: refactoring
- **커밋(작성 시점)**: 229f868 (HEAD) — 리팩토링 변경은 워킹 트리·미커밋

## 1. 작업 개요

Dual-Track TDD 규칙에 따라 **기능 추가·외부 계약 변경 없이** `UnitConverter.cpp` thin main 리팩토링 1커밋 분량을 수행했다.

| 목표 ID | 내용 |
|---------|------|
| 계획 #2 | anonymous `loadRegistry()` → **Control** `ApplicationBootstrap::loadRegistryFromArgv` |
| 계획 #7 | 중복 `stderr` 에러 출력 → **Boundary** `ConsoleErrorWriter` |

리팩토링 전 **69/69** GREEN → 보호 테스트 1건 추가 → 리팩토링 후 **70/70** GREEN 및 `golden_master_cli_stdout_approval` PASS를 확인했다. Domain(Logic Track) 소스는 변경하지 않았다.

## 2. 변경·산출물 목록

| 구분 | 경로/항목 | Track | 설명 |
|------|-----------|-------|------|
| 신규 | `include/control/ApplicationBootstrap.hpp` | Control | argv/`--config=` 레지스트리 부트스트랩 API |
| 신규 | `src/control/ApplicationBootstrap.cpp` | Control | Json→Yaml 로드 순서, 실패 시 `exit(1)` (기존과 동일) |
| 신규 | `include/boundary/ConsoleErrorWriter.hpp` | Boundary | `writeAppError` / `writeAppErrorToStderr` |
| 신규 | `src/boundary/ConsoleErrorWriter.cpp` | Boundary | `ERR-*:` + message + `\n` 포맷 단일화 |
| 수정 | `UnitConverter.cpp` | Composition root | `loadRegistry` 제거, writer·bootstrap 호출만 |
| 수정 | `CMakeLists.txt` | 빌드 | core에 신규 2 `.cpp` 등록 |
| 수정 | `tests/boundary/test_error_codes.cpp` | Boundary 테스트 | `test_write_app_error_format_matches_cli_contract` |
| 문서 | `Report/026-20260521-refactor-application-bootstrap-console-error-writer.md` | — | 본 보고서 |
| 대화 기록 | `Prompting/026-...-Prompt.md` | — | 세션 대화 요약 |
| User 프롬프트 | `Prompting_user/026-...-User.md` | — | User 메시지 |

**워킹 트리 통계 (대략)**: 수정 3 + 신규 4 소스/헤더 (+ 보고서·프롬프트)

## 3. Dual-Track 분리 요약

| Track | 변경 전 문제 | 변경 후 |
|-------|--------------|---------|
| **Boundary (UI)** | main에 `cerr` 포맷 코드 2회 중복 | `ConsoleErrorWriter`가 CLI stderr 계약 담당 |
| **Control** | `loadRegistry`가 main anonymous namespace에 혼재 | `ApplicationBootstrap`이 argv·config 로드 정책 담당 |
| **Domain (Logic)** | — | **변경 없음** (`UnitRegistry`, `LengthConversionService` 유지) |

### 계약·금지 사항 준수

| 규칙 | 준수 |
|------|------|
| 입력 `단위:값` / 출력 `값 단위 = 변환값 단위` | golden master PASS |
| 예외 타입 (contract `invalid_argument` 등) | Track A/B RED PASS, contract 미변경 |
| 테스트 삭제·완화 | 없음 (+1 boundary 테스트) |
| `3.28084` / `1.09361` main 인라인 | 추가 없음 (Domain `UnitRegistry` 유지) |

## 4. 주요 결정·이슈

- **결정**: `std::exit(1)` on config load failure는 `ApplicationBootstrap`에 그대로 유지(동작 동등).
- **결정**: `writeAppError(std::ostream&)` + `writeAppErrorToStderr` — 단위 테스트는 `ostringstream`으로 stderr 계약 고정.
- **결정**: `"1 "` 라우팅·프롬프트·`getline`은 이번 커밋 범위 외(다음 REFACTOR 후보).
- **미해결**: `--config=` / 등록 분기 CLI E2E 단위 테스트는 golden·data TC로 간접 보호 — `test_unit_converter_cli` 후속 권장.

## 5. 테스트·검증

| 단계 | 명령 | 결과 |
|------|------|------|
| Step 0 | `ctest --test-dir build --output-on-failure` | **69/69 PASS** |
| Step 4 | 동일 | **70/70 PASS** |
| Golden | `golden_master_cli_stdout_approval` | **PASS** |
| Track A | TC-A-01~07 | **PASS** |
| Track B | TC-B-01~07 | **PASS** |
| Boundary 신규 | `test_write_app_error_format_matches_cli_contract` | **PASS** |

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```

## 6. 위험·롤백

| 위험 | 완화 |
|------|------|
| stderr 한 줄 포맷 변경 | boundary 테스트 + golden |
| bootstrap 로직 drift | TC-B-06/07, `test_config_loader` + golden |

**롤백**: 본 REFACTOR 커밋 1개 `git revert` 또는 워킹 트리 discard.

## 7. 커밋 메시지 제안

```
refactor(bce): extract ApplicationBootstrap and ConsoleErrorWriter from main

Move argv/--config= registry bootstrap to control layer and consolidate
CLI stderr error formatting in boundary ConsoleErrorWriter. Thin main
unchanged in behavior; add boundary test for ERR-* output contract.
```

## 8. 다음 단계

1. 위 REFACTOR 산출물 커밋(코드 + 보고서 026).
2. 다음 REFACTOR: `CommandDispatcher`(`"1 "` 분기) 또는 `ConsoleSession`(프롬프트/getline).
3. CLI E2E 테스트(`--config=`, 등록·실패 exit code) 추가 후 main 추가 슬림화.
