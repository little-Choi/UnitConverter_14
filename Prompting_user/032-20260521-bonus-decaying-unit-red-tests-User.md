# User 프롬프트만 — 032-20260521-bonus-decaying-unit-red-tests

- **보고서 번호**: 032
- **저장일**: 2026-05-21

---

## User Prompt 1

신규 기능 RED 테스트 작성:

- `registerUnit("cubit", 0.4572)`, `convert`/`convertAll` 동작
- `Item` 구조체(`UnitConverter.cpp` 기존 변환 로직) 수정 금지
- 음수 비율 등록 시 `std::invalid_argument`
- 테스트 BT-01~06, `TEST_CASE("감쇠 단위 변환", "[bonus]")`
- 산출물: `src/DecayingUnit.cpp` + `tests/test_decaying_unit.cpp` (실패 상태)

## User Prompt 2

보고서 작성 및 저장 Agent 실행해줘
