# 대화 프롬프트 기록 — 022-20260521-tc-b-07-green-load-config-missing-path

- **보고서 번호**: 022
- **저장일**: 2026-05-21

---

## Turn 1

**User**

당신은 Dual-Track UI(Boundary) + Logic(Domain) TDD 실무 전문가입니다.
프로젝트: @UnitConverter_14

아래 순서로 진행하라:

Step 1) 대상 TC 선정 : TC-B-07
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

**Assistant** (TC-B-07 GREEN 세션 요약)

1. **TC 선정**: README Track B TC-B-07 — `loadConfig(없는 경로)` → 기본값(3.28084/1.09361) 유지.
2. **Step 2 (RED 확인)**: `units_non_default.json` 선행 로드 후 missing path — `unit_converter_tests "TC-B-07*"` **FAIL** (feet 2.0 vs 3.28084).
3. **최소 구현 (GREEN)**:
   - `tests/red/test_track_b_logic_red.cpp`: TC-B-07 TEST_CASE 추가.
   - `tests/fixtures/units_non_default.json`: 비기본 비율 픽스처.
   - `src/contract/UnitConverterContract.cpp`: `loadConfig` 실패 시 `g_config_units.reset()`.
4. **Step 4**: TC-B-07 PASS; TC-B-01~06 회귀 PASS; `[red]` 14 PASS.
5. **README**: TC-B-07 `[x]`.
6. **보고서**: `Report/022-20260521-tc-b-07-green-load-config-missing-path.md` 및 프롬프트 022.
