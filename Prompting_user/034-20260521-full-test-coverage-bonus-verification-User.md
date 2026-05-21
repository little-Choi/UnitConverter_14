# User 프롬프트만 — 034-20260521-full-test-coverage-bonus-verification

- **보고서 번호**: 034
- **저장일**: 2026-05-21

---

## User Prompt 1

전체 테스트, 커버리지, Golden Master를 확인하라.

1) 전체 테스트:
cmake -S . -B build && cmake --build build ctest --test-dir build -V

2) 커버리지:
# gcov / lcov gcov UnitConverter.cpp

3) Golden Master (출력 불변 확인):
cmake --build build && ctest --test-dir build 또는: ctest -R bonus

확인 항목:
- BT-01~06 PASS (신규 기능)
- TC-A-01~07, TC-B-01~07 PASS (기존 회귀)
- Golden Master PASS (meter/feet/yard 출력 불변)
- registerUnit("cubit", -1.0) → std::invalid_argument 발생 확인
- Domain 커버리지 ≥ 95% / Boundary ≥ 85%

## User Prompt 2

보고서 작성 및 저장 Agent 실행해줘
