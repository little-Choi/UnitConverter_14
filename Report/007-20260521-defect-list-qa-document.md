# 작업 보고서 — 결함 목록 문서화 및 QA 분석

- **보고서 번호**: 007
- **작성일**: 2026-05-21
- **브랜치**: red
- **커밋(작성 시점)**: f6220aa

## 1. 작업 개요

사용자 요청에 따라 C++ QA 관점에서 빌드·테스트 실패를 분석했고(실패 로그 미첨부 시 로컬 `ctest` 실행), RED→GREEN 과정에서 발견된 결함 **23건**을 `docs/defect_list.md`에 8열 표 형식(DEF-001~DEF-023)으로 정리했다. 제품 결함(DEF-001~017)은 회귀 **45/45 Green**으로 Fixed 처리했고, 빌드·커버리지·Should 항목은 Mitigated/Open으로 구분했다. README **RED 단계 To-Do > 결함 목록 연결** 체크박스를 완료 처리하고 관련 문서 표에 `defect_list.md`·`test_plan.md` 링크를 추가했다.

## 2. 변경·산출물 목록

| 구분 | 경로/항목 | 설명 |
|------|-----------|------|
| 신규 | `docs/defect_list.md` | DEF-001~023, 상태 요약, TC 추적, 회귀 절차 |
| 수정 | `README.md` | 결함 목록 체크박스 [x], 관련 문서 2행 |
| 보고 아카이브 | `Report/007-*`, `Prompting/007-*`, `Prompting_user/007-*` | 본 세션 기록 |
| 참조(기존) | `Report/006-*`, `docs/test_plan.md` 부록 A | 레거시 갭·GREEN 빌드 |

## 3. 주요 결정·이슈

- **결정**: 결함 표는 사용자 지정 8열(ID·Severity·변환 타입·재현·기대·실제·근본원인·수정요약) 유지; §2에 Fixed/Mitigated/Open 범례 추가.
- **결정**: DEF-001~004는 Domain RED 스텁(0 반환) 대표; DEF-005~006은 Boundary half-up golden; DEF-007~011은 레거시→ERR-* 계약(부록 A).
- **이슈(해결)**: 실패 로그 미첨부 — 로컬 `cmake`/`ctest`로 GREEN 확인 후 문서화.
- **이슈(Open)**: DEF-022 lcov Gate, DEF-023 `--format` json/csv — v1.0 Should.

## 4. 테스트·검증

| 명령 | 결과 |
|------|------|
| `cmake -S . -B build` / `cmake --build build` | 성공 |
| `ctest --test-dir build --output-on-failure` | **45 passed**, 0 failed |
| `git diff --stat` (보고서 작성 전) | `README.md` +4/-2, `docs/defect_list.md` 신규 |

## 5. 다음 단계

1. README Track A/B 체크박스를 Catch2 TC 완료에 맞춰 순차 [x] 반영.
2. `lcov` 파이프라인(DEF-022) 및 Domain≥95% Gate 측정.
3. JSON/CSV 출력(DEF-023) Should 구현 후 defect_list Open 항목 갱신.
