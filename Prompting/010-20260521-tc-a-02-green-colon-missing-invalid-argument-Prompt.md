# 대화 프롬프트 기록 — 010-20260521-tc-a-02-green-colon-missing-invalid-argument

- **보고서 번호**: 010
- **저장일**: 2026-05-21

---

## Turn 1

**User**

당신은 Dual-Track UI(Boundary) + Logic(Domain) TDD 실무 전문가입니다.
프로젝트: @c:\DEV\UnitConverter_14\ 

이번 커밋에서 처리할 묶음을 1개 선택하고 아래 순서로 진행하라:

Step 1) 대상 TC 선정 : TC-A-02
Step 2) cmake -S . -B build && cmake --build build → 대상 TC가 FAIL인지 확인
Step 3) 대상 TC만 통과하는 최소 구현 작성
Step 4) cmake -S . -B build && cmake --build build 재실행 → 대상 TC PASS, 나머지 영향 없음 확인
Step 5) 커밋

출력 형식:
1) 이번 커밋 목표 (대상 TC PASS)
2) 추가/수정한 코드 범위
3) 테스트 결과 (PASS/FAIL 목록)
4) README.md 파일 Todolist에 해당 TC 체크하기
5) 보고서 작성 및 저장 Agent 실행

**Assistant**

TC-A-02(README RED To-Do: `meter2.5` → `std::invalid_argument`) GREEN 처리.

- Step 1: `tests/red/test_track_a_ui_red.cpp` TC-A-02, BCE `test_parse_no_colon_format_error`·`convertFromInput` 예외 매핑 확인.
- Step 2: 빌드 후 `unit_converter_tests "TC-A-02*"` → `FAIL("RED")` 확인.
- Step 3: TC-A-02 `REQUIRE_THROWS_AS` 본문만 추가(프로덕션 변경 없음).
- Step 4: TC-A-02 PASS; TC-A-01·`~[red]` 45건 PASS; `[red]` 11건 RED 유지.
- Step 5: `feat(boundary): TC-A-02 GREEN colon-missing throws invalid_argument` + Report/Prompting 010.
- README RED To-Do TC-A-02 체크.

(도구: Read test_plan/contract/parser, Shell cmake/ctest, StrReplace test+README, Write report)
