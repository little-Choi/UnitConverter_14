# 작업 보고서 — README RED 단계 To-Do 체크리스트 추가

- **보고서 번호**: 004
- **작성일**: 2026-05-21
- **브랜치**: red
- **커밋(작성 시점)**: a9f1a56

## 1. 작업 개요

사용자 요청에 따라 `docs/test_plan.md`를 기준으로 한 **RED 단계 To-Do 체크리스트**를 `README.md`에 추가했다. 기존 본문은 유지하고 `## 테스트 실행` 직후에 새 섹션을 삽입했으며, 목차에 `[RED 단계 To-Do 리스트](#red-단계-to-do-리스트)` 링크를 추가했다. Track A(Boundary 7건), Track B(Domain 7건), 커버리지 목표, 결함 목록 연결 항목을 체크박스 형태로 문서화해 `red` 브랜치에서 Catch2 RED 작업 추적 기준을 README에서 바로 확인할 수 있게 했다. 이어 `report-github-manager` 워크플로에 따라 본 보고서(004)와 세션 프롬프트 아카이브를 생성한다.

## 2. 변경·산출물 목록

| 구분 | 경로/항목 | 설명 |
|------|-----------|------|
| 문서 수정 | `README.md` | +35 lines — RED To-Do 섹션·목차 항목 |
| 참조 | `docs/test_plan.md` | 체크리스트 출처(인용 문구) |
| 보고 아카이브 | `Report/004-*.md`, `Prompting/004-*`, `Prompting_user/004-*` | 본 세션 기록 |

## 3. 주요 결정·이슈

- **결정**: 삽입 위치는 `## 테스트 실행` 다음 — 테스트·TDD 흐름과 인접.
- **결정**: TC-A/B ID·기대값은 사용자 제공 초안 그대로 반영(std::invalid_argument 등 레거시 스타일).
- **이슈(미해결)**: PRD 목표 계약은 `ERR-*`·POL-NEG — README 체크리스트와 `test_plan.md` B-06/B-07 간 용어 정합은 RED 구현 시 통일 필요.
- **이슈**: 체크박스는 문서용 — Catch2 TC 파일·CMake(M-01) 미구축, 실제 RED 테스트 코드 없음.

## 4. 테스트·검증

해당 없음 (문서 편집만). `git diff --stat`: `README.md | 35 insertions(+)`. 빌드·ctest·lcov 미실행.

## 5. 다음 단계

1. `red` 브랜치에서 README TC-A-01~A-07, TC-B-01~B-07에 대응하는 Catch2 RED 테스트 추가(M-01 골격 선행).
2. TC-A-02~A-05 등 예외 기대를 PRD `ERR-*` 계약과 정합시킬지 결정 후 test_plan·README 동기화.
3. 커버리지 Gate 달성 후 README 체크리스트 항목 순차 체크.
