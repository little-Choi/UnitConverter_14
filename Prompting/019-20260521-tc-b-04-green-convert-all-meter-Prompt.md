# 대화 프롬프트 기록 — 019-20260521-tc-b-04-green-convert-all-meter

- **보고서 번호**: 019
- **저장일**: 2026-05-21

---

## Turn 1

**User**

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

**Assistant** (TC-B-04 GREEN 세션 요약)

1. **TC 선정**: README Track B TC-B-04 — `convertAll("meter", 1.0)` → 모든 등록 단위 변환 반환 (3건, ε=1e-5).
2. **Step 2 (RED 확인)**: `unit_converter_tests "TC-B-04*"` → `FAIL("RED")`.
3. **최소 구현 (GREEN)**:
   - `tests/red/test_track_b_logic_red.cpp`: `unit_converter::convertAll("meter", 1.0)` — size==3, meter/feet/yard 값 검증; TEST_CASE명 `convertAll_meter_returns_all_registered_units`로 정정.
   - `src/contract/UnitConverterContract.cpp`: `convertAll(...)` — `UnitRegistry::bootstrapDefault()` + `LengthConversionService::convertAll` → `ConvertAllEntry` 매핑.
   - TC-B-05~06: `FAIL("RED")` 유지.
4. **Step 4**: TC-B-04 PASS; TC-B-01~03 회귀 PASS; `~[red]` 45 PASS; `[red]` 11 passed / 2 failed (TC-B-05~06 RED 기대).
5. **README**: TC-B-04 `[x]`.
6. **보고서**: `Report/019-20260521-tc-b-04-green-convert-all-meter.md` 및 프롬프트 019.
