# 대화 프롬프트 기록 — 011-20260521-tc-a-03-green-negative-invalid-argument

- **보고서 번호**: 011
- **저장일**: 2026-05-21

---

## Turn 1

**User**

당신은 Dual-Track UI(Boundary) + Logic(Domain) TDD 실무 전문가입니다.
프로젝트: @c:\DEV\UnitConverter_14\ 

이번 커밋에서 처리할 묶음을 1개 선택하고 아래 순서로 진행하라:

Step 1) 대상 TC 선정 : TC-A-03
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

TC-A-03(README RED To-Do: 음수 입력 `meter:-1.0` → `std::invalid_argument`) GREEN 처리.

- Step 1: `tests/red/test_track_a_ui_red.cpp` TC-A-03, BCE `test_parse_negative_value_rejected`·`ConvertInputParser` POL-NEG·`convertFromInput` 예외 매핑 확인.
- Step 2: 빌드 후 `unit_converter_tests "TC-A-03*"` → `FAIL("RED")` 확인.
- Step 3: TC-A-03 `REQUIRE_THROWS_AS(convertFromInput("meter:-1.0"), std::invalid_argument)` 본문만 추가(프로덕션 변경 없음).
- Step 4: TC-A-03 PASS; TC-A-01·TC-A-02·`~[red]` 45건 PASS; `[red]` 3 passed / 10 failed RED 유지.
- Step 5: `571da76` feat + `3847502` docs(report 011, README TC-A-03 체크); `report-github-manager` 백그라운드 실행.

(도구: Grep/Read test·parser·report 010, Shell cmake/ctest, StrReplace test+README, Write report 011, git commit×2, Task report-github-manager)

## Turn 2

**User**

(report-github-manager 서브에이전트) Session context TC-A-03 GREEN — Report 011 갱신, Prompting/Prompting_user 011 생성, 커밋·`origin/green` push. 테스트·프로덕션 코드 수정 금지.

**Assistant**

보고서 011 커밋 해시 반영, 프롬프트 아카이브 2종 생성, docs 커밋 후 push 완료 보고.
