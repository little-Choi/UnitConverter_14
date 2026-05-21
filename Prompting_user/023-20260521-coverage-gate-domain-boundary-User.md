# User 프롬프트만 — 023-20260521-coverage-gate-domain-boundary

- **보고서 번호**: 023
- **저장일**: 2026-05-21

---

## User Prompt 1

모든 TC(TC-A-01~07, TC-B-01~07)가 통과한 후 전체 테스트를 실행하라.

cmake -S . -B build && cmake --build build ctest --test-dir build -V

커버리지 측정:
# gcov / lcov gcov @UnitConverter.cpp 

확인 항목:
- 모든 TC PASS (0 failures)
- Domain Logic 커버리지 ≥ 95%
- Boundary Layer 커버리지 ≥ 85%
- 비율 상수 3.28084 / 1.09361이 인라인으로 남아 있지 않음
- main() 함수에 변환 로직이 남아 있지 않음 (Domain으로 분리됨)

## User Prompt 2

진행해줘.

## User Prompt 3

보고서 작성 및 저장 Agent 실행해줘.
