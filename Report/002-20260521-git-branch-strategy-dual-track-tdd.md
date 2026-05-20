# 작업 보고서 — Dual-Track TDD Git 브랜치 전략 안내 및 2차 아카이브

- **보고서 번호**: 002
- **작성일**: 2026-05-21
- **브랜치**: red
- **커밋(작성 시점)**: 2cd5743

## 1. 작업 개요

사용자가 UnitConverter_14 프로젝트의 Dual-Track TDD(RED → GREEN → Refactoring) 흐름에 맞는 Git 브랜치 전략을 요청했습니다. PRD, TODO, README, requirements 및 저장소 브랜치 상태(`main`, `spec`, `red`, `C_14`)를 조사한 뒤, 장기 브랜치(`spec` → `red` → `green` → `refactor` → `main`)와 Logic/UI 트랙(Domain/Boundary) 매핑, 마일스톤(MS-0~4)별 사용법, 커밋 type 규칙을 문서화해 답변했습니다. 이어서 `report-github-manager` 워크플로에 따라 본 보고서(002)와 세션 프롬프트 아카이브를 생성하고 `origin/red`에 push했습니다.

## 2. 변경·산출물 목록

| 구분 | 경로/항목 | 설명 |
|------|-----------|------|
| 보고서 | `Report/002-20260521-git-branch-strategy-dual-track-tdd.md` | 본 문서 |
| 프롬프트 | `Prompting/002-20260521-git-branch-strategy-dual-track-tdd-Prompt.md` | 세션 전체 대화 |
| User | `Prompting_user/002-20260521-git-branch-strategy-dual-track-tdd-User.md` | User 메시지만 |
| (참고) | 소스 코드 변경 없음 | `git status` clean — 문서·아카이브만 추가 |

## 3. 주요 결정·이슈

- **브랜치 전략 핵심:** `red` → `main` 직접 병합 금지; `red` → `green` → `refactor` → `main`(PR, RG Gate) 순.
- **Dual-Track 매핑:** Logic = Domain(`tests/domain/`, M-02~03), UI = Boundary(`tests/boundary/`, M-04~07, M-10).
- **GREEN 구현 순서:** Domain GREEN → Boundary(Mock Control) GREEN → Control 통합(M-08) — PRD §8 Dual-Track TDD와 정합.
- **현재 저장소:** `red` 브랜치, HEAD `2cd5743`, 구현 코드·Catch2 골격 미착수(M-01 Planned).
- `git merge`는 수행하지 않음.

## 4. 테스트·검증

| 명령 | 결과 |
|------|------|
| `git status` | clean (보고서 커밋 전) |
| `git branch -a` | `main`, `spec`, `red`(현재), `C_14`; remote `origin/red` 동기 |
| `git log -3 --oneline` | `2cd5743`, `d1c01de`, `f0690c8` |
| `next-report-id.ps1` | `002` |

코드 빌드·`ctest` 해당 없음(이번 세션은 전략 안내·문서 저장만).

## 5. 다음 단계

1. `red`에서 M-01(CMake + Catch2 v3) 골격 구성 후 Dual-Track RED 테스트 커밋.
2. RED 완료 시 `git checkout -b green red` 분기, Domain → Boundary GREEN 순 구현.
3. (선택) `docs/TODO.md`에 Git 브랜치 전략 절 추가 — 사용자 요청 시.
