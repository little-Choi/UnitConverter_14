# 작업 보고서 — Golden Master Approval 회귀 테스트

- **보고서 번호**: 024
- **작성일**: 2026-05-21
- **브랜치**: refactoring
- **커밋(작성 시점)**: 1a67b3f (HEAD, golden master 변경은 스테이징됨·미커밋)

## 1. 작업 개요

UnitConverter CLI stdout/stderr 기반 Golden Master(Approval) 회귀 테스트를 설계·구현했다. 입력 시나리오 4개(`meter:2.5`, `feet:1.0`, `yard:1.0`, `meter:0.0`)에 대해 기준 파일 `tests/golden_master_expected.txt`를 버전 관리하고, Catch2 통합 테스트 `golden_master_cli_stdout_approval`에서 기준 없으면 자동 생성·있으면 문자열 비교·불일치 시 line diff 후 FAIL 하도록 했다. Windows `cmd` 리디렉션 캡처, CLI 프롬프트 제거, CRLF→LF 정규화를 적용했으며, 기준 값은 프롬프트 예시의 6자리 raw 값이 아니라 현재 구현의 half-up 1자리(예: 8.2 feet, 2.7 yard)로 맞췄다. 전체 CTest 69개 통과를 확인했고, golden master 관련 파일은 스테이징된 상태에서 본 보고서·프롬프트 저장 및 커밋·push를 진행한다.

## 2. 변경·산출물 목록

| 구분 | 경로/항목 | 설명 |
|------|-----------|------|
| 기준 파일 | `tests/golden_master_expected.txt` | 4 시나리오 블록 + `---` 구분자 |
| 헬퍼 | `tests/helpers/GoldenMasterApproval.{hpp,cpp}` | CLI 실행, 프롬프트 제거, LF 정규화, diff |
| 통합 테스트 | `tests/integration/test_golden_master.cpp` | Approval 패턴 Catch2 테스트 |
| 스크립트 | `scripts/generate_golden_master.ps1`, `.sh` | 기준 파일 재생성·선택적 git add |
| 빌드 | `CMakeLists.txt` | 소스/실행 경로 define, 헬퍼·테스트 소스, UnitConverter 의존 |
| gitignore | `tests/.gitignore` | `.golden_master_scratch/` 제외 |
| 문서 | `Report/024-20260521-golden-master-approval-regression.md` | 본 보고서 |
| 프롬프트 | `Prompting/024-...-Prompt.md`, `Prompting_user/024-...-User.md` | 대화·User 프롬프트 저장 |

**스테이징 통계 (커밋 전)**: 8 files, +466 lines (`CMakeLists.txt`, scripts, tests/*)

## 3. 주요 결정·이슈

- **결정**: 기준 출력은 실제 CLI half-up 1자리 표시 사용(README/TC-A-01과 일치). `meter:0.0`은 stderr `ERR-INPUT_NEGATIVE: 0.0`만 기록.
- **결정**: Windows에서 `cmd /c UnitConverter < input > stdout 2> stderr` 캡처; 비교 전 `normalizeNewlines`로 CRLF→LF 통일.
- **결정**: 기준 파일 없을 때 테스트가 자동 생성(PASS) — 이후 `git add`로 버전 관리 권장.
- **미해결**: golden master 구현 커밋은 사용자 요청 전까지 스테이징만 되어 있었음 → 본 워크플로에서 보고서·프롬프트와 함께 커밋 예정.

## 4. 테스트·검증

| 명령 | 결과 요약 |
|------|-----------|
| `cmake --build build --target unit_converter_tests` | 빌드 성공 |
| `unit_converter_tests.exe "golden_master_cli_stdout_approval"` | PASS (CRLF 정규화 후) |
| `cmake --build build --target test` | 69/69 tests passed |
| `scripts/generate_golden_master.ps1` | `tests/golden_master_expected.txt` 재생성 확인 |

## 5. 다음 단계

1. CLI 출력 형식 변경 시 `generate_golden_master.ps1`로 기준 재생성 후 diff 검토.
2. Linux CI에서 `.sh` 스크립트 및 golden master 테스트 동작 확인.
3. 필요 시 JSON 모드 등 추가 시나리오를 `kGoldenScenarios`에 확장.
