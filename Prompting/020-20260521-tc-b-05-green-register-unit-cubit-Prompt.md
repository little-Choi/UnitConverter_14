# 대화 프롬프트 기록 — 020-20260521-tc-b-05-green-register-unit-cubit

- **보고서 번호**: 020
- **저장일**: 2026-05-21

---

## Turn 1

**User**

당신은 Dual-Track UI(Boundary) + Logic(Domain) TDD 실무 전문가입니다.
프로젝트: @UnitConverter_14

아래 순서로 진행하라:

Step 1) 대상 TC 선정 : TC-B-05
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

**Assistant** (TC-B-05 GREEN 세션 요약)

1. **TC 선정**: README Track B TC-B-05 — `registerUnit("cubit", 0.4572)` 후 변환 가능.
2. **Step 2 (RED 확인)**: `unit_converter_tests "TC-B-05*"` → `FAIL("RED")`.
3. **최소 구현 (GREEN)**:
   - `tests/red/test_track_b_logic_red.cpp`: `registerUnit` + `convert("cubit",1.0,"meter")` ε=1e-5; TEST_CASE명 `UnitRegistry_register_unit_cubit_then_convert`.
   - `src/contract/UnitConverterContract.cpp`: `registerUnit`, `g_pending_registrations` + `registryWithPending()` — `convert`에서 병합 후 clear.
   - TC-B-06: `FAIL("RED")` 유지.
4. **Step 4**: TC-B-05 PASS; TC-B-01~04 회귀 PASS; `~[red]` 45 PASS; `[red]` 12 passed / 1 failed (TC-B-06 RED 기대).
5. **README**: TC-B-05 `[x]`.
6. **보고서**: `Report/020-20260521-tc-b-05-green-register-unit-cubit.md` 및 프롬프트 020.
