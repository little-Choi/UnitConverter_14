# To-Do 리스트 — UnitConverter (C++)

**워크스페이스:** `UnitConverter_14`  
**기준:** [PRD.md](./PRD.md) §3 기능 요구 · §7.1 인수 기준 · §7.2 회귀 보호  
**검증 주체:** **학습자(L)** · **리뷰어(R)** · **자동화(A)=Catch2/커버리지 리포트**

---

## 🔴 필수 (Must-Have) — v1.0 릴리스 차단 항목

| # | 작업 | 연관 PRD | 완료 기준（누가 / 무엇 / 통과） |
|---|------|----------|--------------------------------|
| M-01 | [ ] CMake + Catch2 v3 프로젝트 골격 구성 | §4.1, F-04 | **L**가 `cmake --build`·`ctest` 실행 → **R** 확인: 테스트 타깃 1개 이상 존재且 실행 가능 |
| M-02 | [ ] Domain: `UnitRegistry` + meter 허브 `LengthConversionService` | F-03, §5.1, G-01, AC-01 | **A**: `R-01`~`R-05` Green; ε=1e-9; feet↔yard **meter 경유만**（NG-03） |
| M-03 | [ ] Domain: `PositiveLength` + Bootstrap（meter/feet/yard） | §3.3 BG, C-02, AC-01 | **A**: Bootstrap size=3; `meter` factor=1.0; drift TC 실패하도록 고정 |
| M-04 | [ ] Boundary: CONVERT 파싱 `unit:value` | F-01, F-02, C-01 | **A**: `meter:2.5` 성공; `meter2.5`·`meter:2.5.3` → `ERR-INPUT_FORMAT:`·exit 1·stdout 빈 |
| M-05 | [ ] Boundary: POL-NEG 음수·0 거부 | POL-NEG-01~03, C-03, AC-02 | **R**: POL 문서 선행 확인; **A**: `meter:-1`·`meter:0` → `ERR-INPUT_NEGATIVE:`·raw 토큰 포함·변환 미호출 |
| M-06 | [ ] Boundary: 미등록 단위 거부 | F-02, C-04, AC-02 | **A**: `cubit:1`（미등록）→ `ERR-INPUT_UNKNOWN_UNIT:`·`cubit` in stderr |
| M-07 | [ ] Boundary: table 기본 출력 + README 표시 | F-01, §6.4, G-02, AC-01 | **A**: `meter:2.5` → `2.5 meter = 8.2 feet`·`2.5 meter = 2.7 yard`; stderr 빈; exit 0 |
| M-08 | [ ] Control: `ConvertAllUnits` 핸들러（Domain만 호출） | §4.2 BCE, F-01 | **R**: Domain→Boundary 역참조 0; **A**: 통합 1건 Green |
| M-09 | [ ] BCE 레이어 디렉터리 분리 + SRP | §4.2, G-05, AC-07 | **R**: Parser/Registry/Conversion/Serializer 분리 표; cubit 추가 시 **Conversion Service 파일 diff 0** |
| M-10 | [ ] 계약 실패 시나리오 자동화 ≥5 | G-03, AC-02 | **A**: 형식·음수·unknown·이중소수·콜론누락 **≥5**건; stderr `^ERR-[A-Z_]+:` |
| M-11 | [ ] 인수 AC-01·AC-02 Gate | §7.1 | **R**: AC-01·AC-02 체크박스 **[x]**（Gherkin S1,S2,S3,S6,S7 매핑） |

---

## 🟡 권장 (Should-Have) — 품질 향상 항목

| # | 작업 | 연관 PRD | 완료 기준（누가 / 무엇 / 통과） |
|---|------|----------|--------------------------------|
| S-01 | [ ] JSON Serializer + Source preservation | F-05, §6.2, OUT-03, AC-03 | **A**: Gherkin S4 — `source.unit=meter`, `source.value=2.5`; conversions 길이=Registry.size() |
| S-02 | [ ] Table Source preservation（전 줄 접두） | §6.4, AC-03 | **A**: Gherkin S5 — 모든 stdout 줄 `2.5 meter =` 로 시작 |
| S-03 | [ ] CSV Serializer（고정 헤더） | F-05, §6.3 | **A**: 헤더 문자열 완전 일치; 데이터 행=Registry.size(); tgt 1자리 half-up |
| S-04 | [ ] `--format=table\|json\|csv` argv | F-05, OUT-06 | **A**: 3포맷 TC 각 ≥3 Green; 미지원 포맷 → `ERR-INPUT_FORMAT` |
| S-05 | [ ] Data: JSON 설정 로드 + InMemory 기본 | F-06, §5.2, AC-05 | **A**: 유효 JSON=US-03 동일 결과; missing/schema → `ERR-CONFIG_*`; stdout 0줄 |
| S-06 | [ ] REGISTER 동적 등록 `1 cubit = 0.4572 meter` | F-07, §5.3, AC-04 | **A**: Gherkin S8 Green; 등록 후 batch 줄 수=Registry.size() |
| S-07 | [ ] REGISTER 중복·0계수 거부 | F-07 | **A**: `ERR-INPUT_DUPLICATE_REGISTER`·`ERR-INPUT_INVALID_FACTOR` |
| S-08 | [ ] Domain 커버리지 Gate | G-04, §4.3 | **R**: 리포트 첨부; Domain line ≥98%, branch ≥95% |
| S-09 | [ ] Boundary·Data 커버리지 | G-04 | **R**: Boundary line ≥90%; Data line ≥90%; 전체 ≥85% |
| S-10 | [ ] golden 스냅샷（table/json/csv） | REG-03 | **L**가 golden 3종 커밋; **A**: 의도 변경 외 diff 0 |
| S-11 | [ ] Traceability Matrix（Concept→Test） | US-07 | **R**: US-01~06 핵심 행 누락 0 |
| S-12 | [ ] 인수 AC-03~AC-05 Gate | §7.1 | **R**: AC-03·04·05 **[x]** |

---

## 🟢 선택 (Nice-to-Have) — v2.0 후보

| # | 작업 | 기대 가치 |
|---|------|-----------|
| N-01 | [ ] `--config` + `--format` 단일 argv 통합 테스트 | F-08 — 실습 데모 1회 실행으로 전 기능 시연 |
| N-02 | [ ] YAML 설정 로더 | F-06 — README YAML 선택 요구 충족 |
| N-03 | [ ] 등록 영속（save_all / reload） | F-09 — 재시작 후 cubit 유지 |
| N-04 | [ ] symbol 대소문자 정규화 정책（lower-case） | 입력 관용성; 정책 TC 1종 추가 |
| N-05 | [ ] Activities 회고 템플릿 `docs/RETRO.md` | US-07 — AI·TC·리팩토링 3항목 기록 표준화 |

---

## 🔵 기술 부채 (Tech Debt)

| # | 문제 | 발생 원인 | 해결 방향 |
|---|------|-----------|-----------|
| TD-01 | [ ] 단일 `UnitConverter.cpp`에 전 책임 집중 | 레거시 실습 시작 코드 | BCE 폴더로 분리; PRD §4.2 의존 방향 준수 |
| TD-02 | [ ] `.cursorrules` 8키 값 비어 있음 | 뼈대만 생성 | `architecture`·`tdd_rules`·`forbidden`·`testing` PRD 수치 기입 |
| TD-03 | [ ] README는 g++ 한 줄, PRD는 CMake | 문서 시점 불일치 | README 빌드 절을 CMake+ctest로 갱신（REG 연동） |
| TD-04 | [ ] Catch2·golden·ERR 스냅샷 없음 | 구현 전 문서 단계 | M-01·S-10 완료 시 TD-04 해소 |
| TD-05 | [ ] 레이어 간 DomainError→ERR 매핑 분산 위험 | 초기 통합 시 급구현 | 단일 `ErrorMapper`（Boundary）; REG-02 |

---

## ✅ 완료 항목 (Done)

| # | 완료 내용 | 완료일 | 관련 |
|---|-----------|--------|------|
| D-01 | [x] Phase 5 PRD 초안（Epic/Story/Gherkin 정합） | 2026-05-20 | `docs/PRD.md` |
| D-02 | [x] `.cursorrules` YAML 뼈대（8키） | 2026-05-20 | `.cursorrules` |
| D-03 | [x] README 기본 요구·비율·Activities 정의 | （기존） | `README.md` |
| D-04 | [x] To-Do 리스트（본 문서） | 2026-05-20 | `docs/TODO.md` |

---

## 📋 회귀 방지 체크리스트（PRD §7.2）

**v1.0 태그 / 리뷰어 merge 전 — R가 체크, A가 증빙**

| # | 확인 항목 | 통과 조건 | PRD |
|---|-----------|-----------|-----|
| RG-01 | [ ] 계약 테스트 전부 Green | `ctest` 실패 0; AC-01~05 해당 TC Green | G-03, §7.1 |
| RG-02 | [ ] 실패 stderr 계약 | ≥5건 `ERR-{CODE}:`; exit 1; stdout 빈 | REG-02, AC-02 |
| RG-03 | [ ] Background 비율 동결 | 3.28084 / 1.09361 drift TC **실패**하도록 유지 | REG-01 |
| RG-04 | [ ] POL-NEG 유지 | S3 TC Green; POL 문서 존재 | REG-04 |
| RG-05 | [ ] Source preservation | S4·S5 TC Green | REG-05 |
| RG-06 | [ ] golden diff 0 | table/json/csv 스냅샷 의도 외 변경 없음 | REG-03 |
| RG-07 | [ ] 커버리지 임계 | Domain ≥98/95%; Boundary ≥90%; Data ≥90%; 전체 ≥85% | G-04, AC-06 |
| RG-08 | [ ] README 갱신 | 빌드（CMake）·실행 예·`docs/PRD.md` 링크 반영 | TD-03 해소 |
| RG-09 | [ ] OCP 증빙 | cubit 추가 PR: Conversion Service **diff 0** | G-05, AC-07 |

---

## 🗓️ 마일스톤

| 마일스톤 | 포함 항목（PRD） | 목표일 | 상태 | Gate（누가 통과 선언） |
|----------|------------------|--------|------|------------------------|
| **MS-0 문서·계약** | PRD, POL-NEG, Gherkin 매핑, TODO | 2026-05-20 | **Done** | **R**: D-01~D-04 존재 |
| **MS-1 Domain GREEN** | F-03, §5.1, G-01, M-02~03 | +0.5일（실습 Act.2 전반） | Planned | **A**: R-* Green; **R**: BCE Domain 분리 |
| **MS-2 Boundary 필수** | F-01, F-02, §6.4, M-04~07, M-10~11 | +1.5일（Act.2~3） | Planned | **A**: AC-01·02; table 8.2/2.7 |
| **MS-3 품질·확장** | F-05~07, S-01~12, G-02~04 | +2일（Act.4） | Planned | **A**: AC-03~05; **R**: 커버리지 리포트 |
| **MS-4 v1.0 릴리스** | M-* 전부, RG-01~09, §7.1 전 AC | +0.5일（Act.5·회고） | Planned | **R**: Level 5 Gate 100%; **L**: 회고 3항목 |
| **MS-5 v2.0 후보** | F-08, F-09, N-01~05 | TBD | Backlog | **R**: Nice-to-Have 우선순위 합의 |

---

## 작업 순서（권장）

```
MS-1: M-01 → M-02 → M-03
MS-2: M-04 → M-05 → M-06 → M-07 → M-08 → M-09 → M-10 → M-11
MS-3: S-01 → S-02 → S-03 → S-04 → S-05 → S-06 → S-07 → S-08~12
MS-4: RG-01~09 + README(TD-03)
```

---

## 변경 이력

| 버전 | 날짜 | 변경 |
|------|------|------|
| 1.0 | 2026-05-20 | PRD §7 기반 초안 |
