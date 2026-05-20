# 작업 보고서 — Catch2 테스트 계획서 작성 (meter→feet)

- **보고서 번호**: 003
- **작성일**: 2026-05-21
- **브랜치**: red
- **커밋(작성 시점)**: 7687846

## 1. 작업 개요

시니어 QA 리드 관점에서 `meter:2.5` 샘플(meter→feet, yard 표시 8.2/2.7)을 기준으로 **Dual-Track TDD**용 테스트 계획서를 작성했다. Catch2 Domain/Boundary TC 우선순위(P0~P2), 사용자 요청 경계값 6종, 예외·특이 케이스, 커버리지 Gate(Domain ≥95%, Boundary ≥85%), `gcov`/`lcov`로 `UnitConverter.cpp` 및 분리 후 모듈 측정 전략을 `docs/test_plan.md`에 문서화했다. 레거시 `UnitConverter.cpp`와 PRD 목표 계약 간 갭(POL-NEG, ERR-* 형식)을 부록으로 명시했다.

## 2. 변경·산출물 목록

| 구분 | 경로/항목 | 설명 |
|------|-----------|------|
| 신규 문서 | `docs/test_plan.md` | 테스트 계획서 v1.0 (10절 + 부록 A/B) |
| 참조 | `docs/requirements.md`, `docs/PRD.md`, `docs/TODO.md` | 비율·계약·마일스톤 정합 |
| 기준 코드 | `UnitConverter.cpp` | 레거시 3단위·파싱 분기 분석 |
| 보고 아카이브 | `Report/003-*.md`, `Prompting/003-*`, `Prompting_user/003-*` | 본 세션 기록 |

## 3. 주요 결정·이슈

- **결정**: Golden 샘플 `meter:2.5` — Domain raw `8.2021`(ε=1e-9), Boundary 표시 `8.2`/`2.7`(half-up).
- **결정**: 경계값 TC ID 매핑 — B-03~B-08(P0), R-01~R-05 Domain P0.
- **결정**: 커버리지는 Catch2가 core library 링크 + E2E 실패 5건+; `main`만 subprocess 측정 시 Domain 0% 위험.
- **이슈(미해결)**: CMake/Catch2 골격(M-01) 미구축 — TC는 문서·RED 설계만, 실행 검증 없음.
- **이슈**: 레거시는 `meter:0`·음수 허용, stderr `ERR-*` 미준수 — B-06/B-07은 목표 계약 RED 대상.

## 4. 테스트·검증

해당 없음 (문서 작성만 수행). `git status` 기준 신규 `docs/test_plan.md` 1파일, 빌드·ctest·lcov 미실행.

## 5. 다음 단계

1. `red` 브랜치에서 M-01(CMake + Catch2 v3) 골격 구성 후 `test_plan.md` §3 TC ID별 RED 테스트 추가.
2. §4.1 경계값 six pack(B-03~B-08) GREEN 및 POL-NEG Boundary 구현.
3. §7 lcov 파이프라인으로 Domain ≥95%, Boundary ≥85% Gate 측정.
