# 작업 보고서 — Bonus DecayingUnit GREEN (registerUnit OCP registry)

- **보고서 번호**: 033
- **작성일**: 2026-05-21
- **브랜치**: `feature`
- **커밋(작성 시점)**: `4f4b0aa`

## 1. 작업 개요

TDD **GREEN** 단계로 Bonus `DecayingUnit` 모듈에 `registerUnit`·meter 허브 기반 `convert`/`convertAll` 최소 구현을 추가했다. OCP 접근: `UnitConverter.cpp`의 `Item` 구조체 및 기존 if-else 변환 로직은 **수정하지 않음**. 내부 `units_` 벡터 레지스트리에 기본 3단위(meter/feet/yard)를 생성자에서 등록하고, `registerUnit`으로 cubit 등 신규 단위만 추가한다. RED 스텁(`convert`→0.0, `convertAll`→빈 벡터)을 제거해 BT-01~06 SECTION 전부 통과시켰다. Windows CTest 한글 `TEST_CASE` 인코딩 이슈로 테스트 케이스명을 `DecayingUnit_bonus_register_and_convert`로 변경했다( SECTION BT-01~06 라벨 유지). REFACTOR는 수행하지 않았다.

## 2. 변경·산출물 목록

| 구분 | 경로/항목 | 설명 |
|------|-----------|------|
| 구현 | `include/DecayingUnit.hpp` | `findUnit()` private 조회 헬퍼 추가 |
| 구현 | `src/DecayingUnit.cpp` | `registerUnit`·meter 허브 `convert`·`convertAll` GREEN 구현 |
| 테스트 | `tests/test_decaying_unit.cpp` | `TEST_CASE`명 ASCII 변경(CTest 호환); SECTION BT-01~06 유지 |
| 제외 | `UnitConverter.cpp`, `Item` | 수정 없음(요구사항 준수) |
| 커밋 | `4f4b0aa` | `feat(feature): add registerUnit with OCP registry` |
| 보고서 | `Report/033-20260521-bonus-decaying-unit-green-register-unit.md` | 본 문서 |
| 프롬프트 | `Prompting/033-…-Prompt.md`, `Prompting_user/033-…-User.md` | 세션 기록 |

## 3. 주요 결정·이슈

- **결정**: 변환 공식 `meter_value = value × source.meters_per_unit`, 결과 `meter_value / target.meters_per_unit` — `LengthConversionService`·`UnitRegistry`와 동일 허브 패턴.
- **결정**: `registerUnit` 음수·0 비율 → `std::invalid_argument` (BT-04); 중복 심볼은 무시(silent return).
- **결정**: 기본 단위는 생성자 등록, 동적 단위만 `registerUnit` — 기존 if-else 체인 확장 없이 레지스트리 push만.
- **이슈(해결)**: CTest가 한글 `TEST_CASE("감쇠 단위 변환")` 필터를 깨뜨려 “No test cases matched” → ASCII `TEST_CASE`명으로 변경 후 `cmake -S . -B build` 재구성.

## 4. 테스트·검증

| 단계 | 명령 | 결과 |
|------|------|------|
| RED 확인 | `cmake --build build` 후 `ctest --test-dir build` | BT-01~06(1 test case) **FAIL** — 스텁 0.0/빈 벡터 |
| GREEN | 동일 빌드·`ctest --test-dir build` | **71/71 PASS** (100%) |
| 회귀 | `cmake -S . -B build && cmake --build build` | 빌드·전체 ctest **PASS** |
| 필터 | `unit_converter_tests.exe "[bonus]"` | 11 assertions, 1 test case **PASS** |

| BT | SECTION 요약 | 검증 내용 |
|----|--------------|-----------|
| BT-01 | cubit → meter | `0.4572` (ε=1e-5) |
| BT-02 | meter → cubit | 역변환 `1/0.4572` |
| BT-03 | cubit → feet | `0.4572 × 3.28084` |
| BT-04 | 음수 비율 | `invalid_argument` |
| BT-05 | convertAll | 4단위 일괄 변환 |
| BT-06 | meter → feet | cubit 등록 후에도 `3.28084` 유지 |

TC-A·TC-B 포함 기존 70건 회귀 **PASS** 유지.

## 5. 다음 단계

1. Bonus **REFACTOR** (요청 시): `DecayingUnit`과 `domain::UnitRegistry` 중복 상수·로직 통합 검토(본 GREEN에서는 미수행).
2. README Bonus To-Do `[x]` 반영 여부 확인(필요 시 별도 문서 커밋).
3. `origin/feature` push — 원격 동기화 필요 시.
