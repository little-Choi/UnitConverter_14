# 대화 프롬프트 기록 — 003-20260521-test-plan-catch2-meter-feet

- **보고서 번호**: 003
- **저장일**: 2026-05-21

---

## Turn 1

**User**

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

**Assistant**

`docs/requirements.md`, `UnitConverter.cpp`, `docs/PRD.md`, `README.md`, `docs/TODO.md`를 조사한 뒤 `docs/test_plan.md`를 작성·저장했다.

**요약 응답:**

- Catch2 `[domain]` R-01~R-07, `[boundary]` B-01~B-10, 통합 I-01~I-02 및 P0/P1/P2 우선순위 정의.
- §4.1에 요청 경계값 6종 + PRD AC-02 매핑(B-03~B-08).
- §4.4 예외·특이 15+ 시나리오, §4.5 실패 계약 체크리스트.
- 커버리지 Gate: Domain line/branch ≥95%, Boundary ≥85%.
- §7 gcov/lcov, `UnitConverter.cpp` 분기 hit 표, library 분리 측정 전략.
- 부록 A: 레거시 vs 목표 계약 diff(POL-NEG, ERR-* 미구현).

---

## Turn 2

**User**

보고서 작성 및 저장 Agent 실행해줘

**Assistant**

`report-github-manager` 4단계 워크플로 실행 중: 보고서 003, Prompt/User 아카이브, git commit & push.

---
