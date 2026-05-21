# 대화 프롬프트 기록 — 026-20260521-refactor-application-bootstrap-console-error-writer

- **보고서 번호**: 026
- **저장일**: 2026-05-21
- **출처**: Cursor Agent 세션 (UnitConverter_14 REFACTOR)

---

## Turn 1 — 분석 (Ask)

**User**

`UnitConverter.cpp` 분석: (1) `test_*.cpp` 존재 여부 (2) 테스트 없이 리팩토링하면 안 되는 이유 한 줄.

**Assistant**

- `tests/`에 `test_*.cpp` 다수 존재; **`UnitConverter.cpp` 전용 테스트 없음** — golden master가 CLI 일부만 간접 검증.
- 테스트 없이 리팩토링 시 CLI/`--config=`/분기 회귀를 즉시 감지할 수 없음.

---

## Turn 2 — 코드 스멜 (Ask)

**User**

코드 스멜 표: SRP, if-else/OCP, 매직 넘버, 예외, 긴 함수, 미사용.

**Assistant**

- `main`/`loadRegistry` SRP·OCP·긴 함수·불완전 오류 처리 해당.
- `3.28084`/`1.09361`은 **이 파일에 없음** (`UnitRegistry.cpp`).

---

## Turn 3 — ECB 분석 (Ask)

**User**

ECB 패턴: main 혼재, 이동 대상, 신규 단위 최소 변경 구조.

**Assistant**

- 환산·파싱·비율은 이미 `src/` 분리; main에 CLI·bootstrap·`"1 "` 라우팅 잔존.
- `ApplicationBootstrap`, `CommandDispatcher`, Console Boundary 제안.

---

## Turn 4 — 리팩토링 계획서 (Ask)

**User**

리팩토링 계획서(대상 목록, R-U1~R-L4, 테스트 선행, 검증 명령).

**Assistant**

- Phase 0: golden + CLI E2E 선행.
- R-U1~R-L4 대부분 **완료**; 남은 작업은 thin main·CLI 테스트.

---

## Turn 5 — Dual-Track REFACTOR (Agent)

**User**

커밋 1개 Dual-Track REFACTOR: 기능/계약 변경 금지, 테스트 GREEN 유지, 출력 형식 1~7.

**Assistant**

**목표**: 계획 #2 `ApplicationBootstrap`, #7 `ConsoleErrorWriter`.

**실행**

1. Step 0: ctest **69/69 PASS**
2. 신규 `ApplicationBootstrap`, `ConsoleErrorWriter`; `UnitConverter.cpp` 슬림화
3. `test_write_app_error_format_matches_cli_contract` 추가
4. Step 4: ctest **70/70 PASS**, golden PASS

**산출**: refactor(bce) 커밋 메시지 제안; 커밋은 사용자 요청 시.

---

## Turn 6 — 보고서 저장

**User**

보고서 작성 및 저장 Agent 실행해줘.

**Assistant**

`Report/026-...`, `Prompting/026-...`, `Prompting_user/026-...` 저장.
