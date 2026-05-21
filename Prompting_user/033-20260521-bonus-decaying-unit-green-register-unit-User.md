# User 프롬프트만 — 033-20260521-bonus-decaying-unit-green-register-unit

- **보고서 번호**: 033
- **저장일**: 2026-05-21

---

## User Prompt 1

[단계] TDD GREEN만 수행. REFACTOR는 하지 않는다.
프로젝트: UnitConverter_14

구현 접근법: OCP: 기존 if-else 수정 없이 UnitRegistry에 새 항목만 등록

할 일:

1. cmake --build build && ctest --test-dir build 실행 → BT-01~06 FAIL 확인
2. registerUnit() 메서드/함수 최소 구현:
   - 내부 UnitRegistry(Map/Dict)에 단위명·비율 저장
   - convert()는 Registry를 조회하여 meter 허브 경유 변환
   - Item 구조체(UnitConverter.cpp의 기존 변환 로직) 수정 금지
3. cmake --build build && ctest --test-dir build 재실행 → BT-01~06 PASS 확인
4. 기존 회귀 테스트 전체 PASS 확인:
   cmake -S . -B build && cmake --build build

산출물:

- BT-01~06이 통과하는 최소 구현 코드
- 기존 TC-A/TC-B 전체 PASS 유지 확인
- 커밋 메시지: feat(feature): add registerUnit with OCP registry

## User Prompt 2

보고서 작성 및 저장 Agent 실행해줘
