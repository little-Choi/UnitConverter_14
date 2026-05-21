# 작업 보고서 — Bonus DecayingUnit RED 테스트

- **보고서 번호**: 032
- **작성일**: 2026-05-21
- **브랜치**: `feature`
- **커밋(작성 시점)**: `49f94cc`

## 1. 작업 개요

사용자 요청에 따라 기존 `Item` 구조체·`UnitConverter.cpp` 변환 로직을 수정하지 않고, 독립 모듈 `DecayingUnit`과 `[bonus]` 태그 Catch2 RED 테스트(BT-01~06)를 추가했다. `registerUnit("cubit", 0.4572)`·`convert`/`convertAll`·음수 비율 `std::invalid_argument` 시나리오를 검증하도록 테스트를 작성했고, 구현은 RED 스텁(미구현 `registerUnit`, `convert`→0.0, `convertAll`→빈 벡터)으로 의도적으로 실패 상태를 유지했다. CMake에 `decaying_unit` 라이브러리 및 테스트 링크를 반영했으며, `[bonus]` 필터 실행 시 1 test case·6 assertion 실패를 확인했다.

## 2. 변경·산출물 목록

| 구분 | 경로/항목 | 설명 |
|------|-----------|------|
| 신규 | `include/DecayingUnit.hpp` | `DecayingUnit` API (Item 미사용, 독립 모듈) |
| 신규 | `src/DecayingUnit.cpp` | RED 스텁: 기본 3단위 초기화, `registerUnit`/`convert`/`convertAll` 미구현 |
| 신규 | `tests/test_decaying_unit.cpp` | BT-01~06 SECTION, `TEST_CASE("감쇠 단위 변환", "[bonus]")` |
| 수정 | `CMakeLists.txt` | `decaying_unit` 라이브러리 + `unit_converter_tests`에 테스트·링크 추가 (+7 lines) |
| 보고서 | `Report/032-20260521-bonus-decaying-unit-red-tests.md` | 본 문서 |
| 프롬프트 | `Prompting/032-…-Prompt.md`, `Prompting_user/032-…-User.md` | 세션 기록 |
| 제외 | `build-cov/` | 빌드 산출물 — 커밋 대상 아님 |

## 3. 주요 결정·이슈

- **결정**: `DecayingUnit`을 `Item`·기존 `UnitConverter`와 분리 — 요구사항의 “Item 수정 금지” 준수.
- **결정**: 구현은 RED 스텁만 제공 — GREEN 단계에서 `registerUnit`·허브(meter) 기반 `convert`/`convertAll` 구현 예정.
- **결정**: 테스트 태그 `[bonus]` — 기본 회귀와 분리 실행 가능.
- **미해결**: BT-01~06 전부 실패(RED 의도) — GREEN 구현 후 `[bonus]` 재실행 필요.

## 4. 테스트·검증

| 명령 | 결과 |
|------|------|
| `cmake --build build-cov --target unit_converter_tests` | 빌드 성공 |
| `build-cov\unit_converter_tests.exe "[bonus]"` | **RED 의도**: test cases **1 failed**, assertions **6 failed** |

`git diff --stat` (보고서 작성 시점): `CMakeLists.txt` 7 insertions; 신규 3파일 untracked.

## 5. 다음 단계

1. `DecayingUnit::registerUnit` — 중복·음수 비율 시 `std::invalid_argument`, cubit 등 동적 등록.
2. `convert` / `convertAll` — meter 허브 기반 변환 및 BT-01~06 GREEN 통과.
3. `[bonus]` 외 전체 `unit_converter_tests` 회귀 확인 후 커밋 메시지에 GREEN 단계 반영.
