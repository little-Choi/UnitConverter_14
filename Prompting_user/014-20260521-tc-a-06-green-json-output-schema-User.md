# User 프롬프트만 — 014-20260521-tc-a-06-green-json-output-schema

- **보고서 번호**: 014
- **저장일**: 2026-05-21

---

## User Prompt 1

당신은 Dual-Track UI(Boundary) + Logic(Domain) TDD 실무 전문가입니다.
프로젝트: UnitConverter_14

이번 커밋에서 처리할 묶음을 1개 선택하고 아래 순서로 진행하라:

Step 1) 대상 TC 선정 : TC-A-06
Step 2) cmake -S . -B build && cmake --build build → 대상 TC가 FAIL인지 확인
Step 3) 대상 TC만 통과하는 최소 구현 작성
Step 4) cmake -S . -B build && cmake --build build 재실행 → 대상 TC PASS, 나머지 영향 없음 확인
Step 5) README.md 파일 Todolist에 해당 TC 체크하기
Step 6) 보고서 작성 및 저장 Agent 실행

출력 형식:
1) 이번 커밋 목표 (대상 TC PASS)
2) 추가/수정한 코드 범위
3) 테스트 결과 (PASS/FAIL 목록)
