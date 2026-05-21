# 대화 프롬프트 기록 — 033-20260521-bonus-decaying-unit-green-register-unit

- **보고서 번호**: 033
- **저장일**: 2026-05-21

---

## Turn 1

**User**

TDD GREEN만 수행 (REFACTOR 금지). OCP: `UnitRegistry`에 새 항목만 등록, `Item`/if-else 수정 금지.

할 일:

1. `cmake --build build && ctest --test-dir build` → BT-01~06 FAIL 확인
2. `registerUnit` 최소 구현 — 내부 레지스트리, meter 허브 `convert`/`convertAll`
3. 재빌드·ctest → BT-01~06 PASS
4. 전체 회귀 PASS (`cmake -S . -B build && cmake --build build`)
5. 커밋: `feat(feature): add registerUnit with OCP registry`

**Assistant**

`DecayingUnit` GREEN 구현 완료.

- `registerUnit`: `units_`에 push, `meters_per_unit <= 0` → `invalid_argument`
- `convert` / `convertAll`: `findUnit` + meter 허브 (`LengthConversionService` 동일 패턴)
- `UnitConverter.cpp` / `Item` 미수정
- CTest 한글 `TEST_CASE` 인코딩 이슈 → `DecayingUnit_bonus_register_and_convert`로 변경
- `ctest`: 71/71 PASS; 커밋 `4f4b0aa`

(도구: Read/Glob, Write DecayingUnit.cpp/hpp, cmake build, ctest, git commit)

---

## Turn 2

**User**

보고서 작성 및 저장 Agent 실행해줘

**Assistant**

Report/Prompting/Prompting_user **033** 작성·저장 (본 GREEN 세션 아카이브).

(도구: Read Report 032·020, Write 033 보고서·프롬프트 3종)
