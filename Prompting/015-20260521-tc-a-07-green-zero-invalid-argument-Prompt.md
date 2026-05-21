# 대화 프롬프트 기록 — 015-20260521-tc-a-07-green-zero-invalid-argument

- **보고서 번호**: 015
- **저장일**: 2026-05-21

---

## Turn 1

**User**

Dual-Track TDD expert workflow: Steps 1-6 for TC-A-07 (select TC, build verify FAIL, minimal GREEN, rebuild verify PASS, README check, report agent).

**Assistant** (TC-A-07 GREEN 세션 요약)

1. **TC 선정**: README RED To-Do TC-A-07 — value=0 경계값 (`meter:0` → `std::invalid_argument`).
2. **Step 2 (RED 확인)**: `unit_converter_tests "TC-A-07*"` → `FAIL("RED")`.
3. **최소 구현 (GREEN)**: `REQUIRE_THROWS_AS(convertFromInput("meter:0"), std::invalid_argument)`; 프로덕션 변경 없음 (POL-NEG `value <= 0` 기존 구현).
4. **Step 4**: TC-A-07 PASS; TC-A-01~06·BCE 45 PASS; `[red]` 7 passed / 6 failed (TC-B-01~06 RED 기대).
5. **README**: TC-A-07 체크 `[x]`.
6. **보고서**: `Report/015-…md` 저장.
