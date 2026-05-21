# 대화 프롬프트 기록 — 021-20260521-tc-b-06-green-load-config-valid-path

- **보고서 번호**: 021
- **저장일**: 2026-05-21

---

## Turn 1

**User**

당신은 Dual-Track UI(Boundary) + Logic(Domain) TDD 실무 전문가입니다.
프로젝트: @UnitConverter_14

아래 순서로 진행하라:

Step 1) 대상 TC 선정 : TC-B-06
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

**Assistant** (TC-B-06 GREEN 세션 요약)

1. **TC 선정**: README Track B TC-B-06 — `loadConfig(유효한 경로)` → 비율 정상 로드.
2. **Step 2 (RED 확인)**: `unit_converter_tests "TC-B-06*"` → `FAIL("RED")`.
3. **최소 구현 (GREEN)**:
   - `tests/red/test_track_b_logic_red.cpp`: `loadConfig(units_valid.json)` + `convert("meter",2.5,"feet")` → `2.5/0.3048`; TEST_CASE명 `ConfigLoader_load_config_valid_path_applies_ratios`.
   - `src/contract/UnitConverterContract.cpp`: `loadConfig` (Json/Yaml), `g_config_units`, `registryWithPending()` config 병합.
4. **Step 4**: TC-B-06 PASS; TC-B-01~05 회귀 PASS; `~[red]` 45 PASS; `[red]` 13 PASS (전체 GREEN).
5. **README**: TC-B-06 `[x]`; TC-B-07 미체크.
6. **보고서**: `Report/021-20260521-tc-b-06-green-load-config-valid-path.md` 및 프롬프트 021.
