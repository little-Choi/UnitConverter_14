# User 프롬프트 기록 — 019-20260521-tc-b-04-green-convert-all-meter

- **보고서 번호**: 019
- **저장일**: 2026-05-21

---

당신은 Dual-Track UI(Boundary) + Logic(Domain) TDD 실무 전문가입니다.
프로젝트: @c:\DEV\UnitConverter_14\

아래 순서로 진행하라:

Step 1) 대상 TC 선정 : TC-B-04
Step 2) cmake -S . -B build && cmake --build build → 대상 TC가 FAIL인지 확인
Step 3) 대상 TC만 통과하는 최소 구현 작성
Step 4) cmake -S . -B build && cmake --build build 재실행 → 대상 TC PASS, 나머지 영향 없음 확인
Step 5) README.md 파일 Todolist에 해당 TC 체크하기
Step 6) 보고서 작성 및 저장 Agent 실행
Step 7) 커밋

출력 형식:
1) 이번 커밋 목표 (대상 TC PASS)
2) 추가/수정한 코드 범위
3) 테스트 결과 (PASS/FAIL 목록)
