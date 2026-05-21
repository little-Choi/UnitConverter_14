# 대화 프롬프트 기록 — 012-20260521-tc-a-04-green-unknown-unit-invalid-argument

- **보고서 번호**: 012
- **저장일**: 2026-05-21

---

## Turn 1

**User**

당신은 Dual-Track UI(Boundary) + Logic(Domain) TDD 실무 전문가입니다.
프로젝트: UnitConverter_14
이번 커밋에서 처리할 묶음: TC-A-04
Step 1~6 (TC 선정, build fail 확인, 최소 구현, rebuild pass, README 체크, 보고서 Agent)

**Assistant** (TC-A-04 GREEN 세션 요약)

1. **TC 선정**: README RED To-Do TC-A-04 — 없는 단위 `parsec:1.0` → `std::invalid_argument`.
2. **Step 2 (RED 확인)**: `test_track_a_ui_red.cpp` TC-A-04가 `FAIL("RED")`일 때 `unit_converter_tests "TC-A-04*"` FAIL 확인.
3. **최소 구현 (GREEN)**: `FAIL("RED")` → `REQUIRE_THROWS_AS(unit_converter::convertFromInput("parsec:1.0"), std::invalid_argument)` + Given 주석 (test_plan B-04, `test_handler_unknown_unit_parsec`). **프로덕션 코드 변경 없음** — BCE·핸들러·`convertFromInput` 예외 매핑 기존 구현 재사용.
4. **Step 4**: `unit_converter_tests "TC-A-04*"` PASS (1 assertion). TC-A-01~03 PASS, `~[red]` 45건 PASS, `[red]` 4 passed / 9 failed (TC-A-05~07, TC-B-01~06 RED 기대).
5. **README**: TC-A-04 체크 `[x]`.
6. **보고서 Agent**: report-github-manager로 보고서 012·프롬프트 저장·GitHub push (feat + docs 2커밋).

---

## Turn 2

**User**

UnitConverter_14 프로젝트 — TC-A-04 GREEN 세션 보고서·프롬프트 저장·GitHub push (4단계 전부).

(부모 에이전트 컨텍스트: 변경 파일, 테스트 검증 표, next-report-id 012, slug `tc-a-04-green-unknown-unit-invalid-argument`, HEAD `1e09869`, 두 커밋 feat→docs, push 지시)

**Assistant**

report-github-manager 4단계 수행: `Report/012-…md`, `Prompting/012-…-Prompt.md`, `Prompting_user/012-…-User.md` 작성; `feat: TC-A-04 GREEN` (tests+README) 후 `docs: 보고서 012…` 커밋; `git push -u origin HEAD`.
