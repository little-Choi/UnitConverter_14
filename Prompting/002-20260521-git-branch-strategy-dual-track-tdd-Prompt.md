# 대화 프롬프트 기록 — 002-20260521-git-branch-strategy-dual-track-tdd

- **보고서 번호**: 002
- **저장일**: 2026-05-21

---

## Turn 1

**User**

@c:\DEV\UnitConverter_14\ 프로젝트를 구현하기 위한 깃 브랜치 전략을 알려줘.
개발방법론은 Dual-Track TDD 이고, 다음의 순서로 진행할 거야.

- Dual-Track UI + Logic TDD (RED 단계)
- GREEN 단계 (테스트 통과)
- Dual-Track Refactoring

**Assistant**

프로젝트 구조와 요구사항을 확인한 뒤 Dual-Track TDD 흐름에 맞는 Git 브랜치 전략을 제안합니다.

(도구: Read requirements.md, Glob, Grep; Read PRD.md, README.md, .cursorrules; Shell git branch/log; Read TODO.md, README Contributing)

저장소에는 이미 `main`, `spec`, `red`(현재), `C_14` 브랜치가 있고, PRD·TODO는 **MS-1 Domain → MS-2 Boundary → MS-3 확장 → MS-4 RG Gate** 순을 권장합니다. Dual-Track TDD 3단계(RED → GREEN → REFACTOR)에 맞춘 브랜치 전략을 정리했습니다.

**요약:** `spec`(계약) → `red`(Logic+UI 테스트 RED) → `green`(Domain→Boundary→통합 GREEN) → `refactor`(구조·OCP, 테스트 유지) → `main`(RG Gate PR). UI 트랙 = Boundary, Logic 트랙 = Domain. `red` → `main` 직접 병합 금지.

---

## Turn 2

**User**

보고서 작성 및 저장 Agent 실행해줘

**Assistant**

`report-github-manager` 4단계 워크플로 실행:

1. `next-report-id.ps1` → `002`
2. `git status` — 브랜치 `red`, HEAD `2cd5743`, working tree clean
3. [1] `Report/002-20260521-git-branch-strategy-dual-track-tdd.md` 작성
4. [2] `Prompting/002-20260521-git-branch-strategy-dual-track-tdd-Prompt.md` 작성
5. [3] `Prompting_user/002-20260521-git-branch-strategy-dual-track-tdd-User.md` 작성
6. [4] `git add` → commit → `git push -u origin HEAD`

(도구: Read report-github-manager.md, Shell git, Write Report/Prompting/Prompting_user, transcript `9ef1eb2c` 참조)
