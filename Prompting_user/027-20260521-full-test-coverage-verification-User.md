# User 프롬프트만 — 027-20260521-full-test-coverage-verification

- **보고서 번호**: 027
- **저장일**: 2026-05-21

---

## User Prompt 1

전체 테스트와 커버리지를 확인하라.

cmake -S . -B build && cmake --build build ctest --test-dir build -V

# gcov / lcov gcov UnitConverter.cpp

확인 항목:
- 모든 TC PASS (TC-A-01~07, TC-B-01~07)
- Golden Master 테스트도 PASS (출력 불변 확인)
- if-else 체인 제거 완료 (UnitRegistry 교체)
- 매직 넘버 3.28084/1.09361 인라인 없음
- Domain(변환 로직)과 Boundary(파싱·출력)가 분리됨
- Domain 커버리지 ≥ 95% / Boundary ≥ 85%

## User Prompt 2

보고서 작성 및 저장 Agent 실행해줘
