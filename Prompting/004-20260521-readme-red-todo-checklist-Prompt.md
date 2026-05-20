# 대화 프롬프트 기록 — 004-20260521-readme-red-todo-checklist

- **보고서 번호**: 004
- **저장일**: 2026-05-21

---

## Turn 1

**User**

@README.md 파일에 아래 섹션을 추가해줘.
기존 내용은 유지하고, "## RED 단계 To-Do 리스트" 섹션만 새로 삽입.

(Track A 7건, Track B 7건, 커버리지 목표, 결함 목록 연결 — test_plan.md 기반 체크리스트 전문)

**Assistant**

README.md를 확인한 뒤 요청하신 RED 단계 To-Do 섹션을 삽입합니다.

(도구: Read README.md, Read test_plan.md limit 30; StrReplace 목차 + 본문 섹션)

`README.md`에 **RED 단계 To-Do 리스트** 섹션을 추가했습니다.

**변경 사항**
- **목차**: `[RED 단계 To-Do 리스트](#red-단계-to-do-리스트)` 항목 추가
- **본문**: `## 테스트 실행` 바로 다음에 요청하신 섹션 전체 삽입 (Track A/B, 커버리지 목표, 결함 목록 연결)
- 기존 내용은 그대로 두었습니다.

---

## Turn 2

**User**

보고서 작성 및 저장 Agent 실행해줘

**Assistant**

`report-github-manager` 4단계 워크플로 실행:

1. `next-report-id.ps1` → `004`
2. `git status` — `README.md` 수정(+35), 브랜치 `red`, HEAD `a9f1a56`
3. [1] `Report/004-20260521-readme-red-todo-checklist.md` 작성
4. [2] `Prompting/004-20260521-readme-red-todo-checklist-Prompt.md` 작성
5. [3] `Prompting_user/004-20260521-readme-red-todo-checklist-User.md` 작성
6. [4] git commit & push `origin/red`

(도구: Read report-github-manager.md, Shell next-report-id/git, Write Report/Prompting/Prompting_user; transcript `474483dd`)

---
