# User 프롬프트만 — 003-20260521-test-plan-catch2-meter-feet

- **보고서 번호**: 003
- **저장일**: 2026-05-21

---

## User Prompt 1

[P] 시니어 QA 리드입니다.
[C] C++17, CMake, Catch2
[T] 선택한 샘플 예제(meter→feet 변환)를 기반으로 테스트 계획서를 작성해줘.

    포함 항목:
    - Catch2 기반 단위 테스트 범위/우선순위
    - 경계값 케이스 목록:
        · value = 0 (영값 변환)
        · value = 매우 큰 수 (오버플로 위험)
        · value < 0 (음수 입력 정책)
        · 소수점 파싱 실패 ("meter:abc")
        · ":"없는 입력 (형식 오류)
        · 없는 단위 ("parsec:1.0")
    - 예외/특이 케이스 목록
    - 커버리지 목표 (Domain 95%+ / Boundary 85%+)
    - # gcov / lcov / gcov UnitConverter.cpp 측정 전략

[F] Markdown 문서. docs 폴더에 test_plan.md로 저장.

## User Prompt 2

보고서 작성 및 저장 Agent 실행해줘
