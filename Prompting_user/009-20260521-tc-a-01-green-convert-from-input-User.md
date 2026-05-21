# User 프롬프트만 — 009-20260521-tc-a-01-green-convert-from-input

- **보고서 번호**: 009
- **저장일**: 2026-05-21

---

## User Prompt 1

당신은 Dual-Track UI(Boundary) + Logic(Domain) TDD 실무 전문가입니다.
프로젝트: @c:\DEV\UnitConverter_14\ 

이번 커밋에서 처리할 묶음을 1개 선택하고 아래 순서로 진행하라:

Step 1) TC-A-01 확인 (위 커밋 순서표 참고)
Step 2) cmake -S . -B build && cmake --build build → TC-A-01가 FAIL인지 확인
Step 3) 대상 TC만 통과하는 최소 구현 작성
Step 4) cmake -S . -B build && cmake --build build 재실행 → TC-A-01 PASS, 나머지 영향 없음 확인
Step 5) 커밋

출력 형식:
1) 이번 커밋 목표 (TC-A-01)
2) 추가/수정한 코드 범위
3) 테스트 결과 (PASS/FAIL 목록)
4) 보고서 작성 및 저장 Agent 실행
