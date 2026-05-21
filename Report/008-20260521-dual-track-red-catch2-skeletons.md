# 작업 보고서 — Dual-Track RED Catch2 스켈레톤

- **보고서 번호**: 008
- **작성일**: 2026-05-21
- **브랜치**: red
- **커밋(작성 시점)**: 501688a

## 1. 작업 개요

사용자가 Unit Converter TDD 연습에서 **구현·GREEN·REFACTOR 없이 RED 테스트만** 작성하도록 요청했다. 에이전트는 `UnitConverter_14` 워크스페이스에 Track A(UI/Boundary 7건)·Track B(Domain/Logic 6건)에 대응하는 Catch2 RED를 추가했고, `include/contract/UnitConverterContract.hpp`에 GREEN 단계용 API 선언만 두었다. 1차 산출물은 Given/When/Then 본문과 계약 헤더 `#include`를 포함해 **링크 단계 undefined reference**로 RED가 유지되었다. 이후 사용자가 **TEST_CASE 이름 + `FAIL("RED")` 한 줄** 스켈레톤만 남기라고 지시했고, 두 `tests/red/*.cpp`를 13개 스켈레톤으로 교체·계약 include를 제거했다. 빌드는 성공하며 `unit_converter_tests "[red]"` 실행 시 13건이 메시지 `RED`로 실패한다.

## 2. 변경·산출물 목록

| 구분 | 경로/항목 | 설명 |
|------|-----------|------|
| RED 테스트 | `tests/red/test_track_a_ui_red.cpp` | TC-A-01~07, 태그 `[red][boundary]`, 본문 `FAIL("RED")` |
| RED 테스트 | `tests/red/test_track_b_logic_red.cpp` | TC-B-01~06, 태그 `[red][domain]`, 본문 `FAIL("RED")` |
| 계약 선언 | `include/contract/UnitConverterContract.hpp` | `convertFromInput`, `convert`, `convertAll`, `registerUnit`, `loadConfig` 등 선언만 (구현 없음) |
| 빌드 설정 | `CMakeLists.txt` | `unit_converter_tests`에 red 소스 2개 추가 (+2 lines) |
| 보고 아카이브 | `Report/008-*.md`, `Prompting_user/008-*` | 본 세션 기록 |
| 참조 | `docs/test_plan.md`, `README.md` RED To-Do | TC ID·시나리오 출처 |

**Git 상태(보고서 작성 시점, 미커밋):** `CMakeLists.txt` 수정, `include/contract/`, `tests/red/` 미추적.

## 3. 주요 결정·이슈

- **결정**: 1차 RED는 계약 헤더 + 풀 테스트 본문 — 구현 `.cpp` 없이 링크 실패로 RED 유지(런타임 전 단계 RED).
- **결정**: 2차 요청에 따라 스켈레톤만 유지 — 빌드 가능·`[red]` 필터로 13건 일괄 `FAIL("RED")` 확인.
- **결정**: Track B는 README To-Do 7건 중 **TC-B-06(설정 기본값)**·**TC-B-07(없는 경로)**를 스켈레톤 2건(B-05/B-06)으로 압축; 역변환(feet→meter) 단독 TC는 스켈레톤에 미포함(README B-03과 차이).
- **이슈(미해결)**: `std::invalid_argument` vs PRD `ERR-*`·`POL-NEG` 용어 — GREEN 시 test_plan·README와 정합 필요.
- **이슈**: `UnitConverterContract.hpp` 구현부 없음 — GREEN 시 `unit_converter_core` 또는 별도 구현 파일 연결 필요.
- **이슈**: 본 보고서·red 산출물은 **아직 git 커밋·push 없음**(사용자 지시: 문서 저장 우선).

## 4. 테스트·검증

| 단계 | 명령·결과 |
|------|-----------|
| 1차 RED | `cmake --build build` — `undefined reference to unit_converter::*` (계약 API 미구현, 기대된 링크 RED) |
| 2차 스켈레톤 | `cmake --build build --target unit_converter_tests` — **성공** |
| RED 실행 | `unit_converter_tests "[red]"` — **13 failed**, 메시지 `RED` |
| Git | `git diff --stat HEAD`: `CMakeLists.txt \| 2 ++` (red·contract는 untracked) |

기존 BCE/GREEN 테스트(`tests/domain`, `boundary` 등) 본 세션에서 재실행 기록 없음.

## 5. 다음 단계

1. README RED To-Do(TC-A/B)와 스켈레톤 ID·개수(7+6) 정합 검토 후, GREEN 단계에서 각 `FAIL("RED")`를 Given/When/Then 본문으로 교체.
2. `UnitConverterContract.hpp` API를 `unit_converter_core`에 구현하고 링크 — Track A/B 스켈레톤을 실패→통과 순으로 GREEN.
3. RED 13건 통과·커버리지 Gate 달성 후 `보고서 작성 및 저장` 및 `git add`/`commit`/`push`(red 산출물 + 보고서 008).
