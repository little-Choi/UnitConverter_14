# PRD — UnitConverter_14

**확장 가능한 C++ 단위 변환 학습 시스템**

| 항목 | 내용 |
|------|------|
| 버전 | 1.0（Phase 4 기준） |
| 범위 | README 기본·품질·추가 요구 + 6시간 Activities |
| 기준 문서 | Epic / User Journey / User Stories US-01~07 / Gherkin Feature（BG, S1~S8, POL-NEG） |
| 구현 | 본 PRD 범위 외（문서만） |

---

# 1. 프로젝트 개요

## 1.1 한 줄 목적문（What / Who / Why）

**C++/클린 아키텍처 학습자**가 **meter 기준 길이 단위 변환 CLI**를 Dual-Track TDD로 구현·검증함으로써, **환산 알고리즘 숙달이 아니라 계약·테스트·Domain/Boundary/Data 레이어 분리**를 6시간 실습 안에 달성한다.

## 1.2 배경 및 문제 정의（관찰）

레거시 단일 파일 변환기에서는 비율·파싱·출력이 한곳에 묶여, 단위 추가나 출력 포맷 변경 시 **변경 범위를 예측할 수 없고** 회귀를 수동 실행에 의존한다. README는 `meter:2.5` 입력에 대해 feet **8.2**·yard **2.7** 표시, OCP/SRP, 입력 검증, JSON/YAML 설정, 동적 등록 `1 cubit = 0.4572 meter`, table/json/csv 출력을 요구한다. 관찰상 학습 실패 패턴은 “돌아가는 코드”만 남고 **ERR-* 계약·ε 검증·golden 회귀**가 없어 Phase 5 이후 리팩토링에서 비율·표시가 조용히 깨지는 것이다.

## 1.3 목표（측정 가능）

| ID | 목표 | 측정 |
|----|------|------|
| G-01 | Domain 환산 정확도 | Catch2 `R-01`~`R-05` **100% Green**; ε = **1e-9** |
| G-02 | README 표시 일치 | `meter:2.5` → table/json/csv에서 feet **8.2**, yard **2.7**（1자리 half-up） |
| G-03 | 계약 테스트 | 자동화 실패 시나리오 **≥5**; stderr `^ERR-[A-Z_]+:` |
| G-04 | 커버리지 | Domain line **≥98%**, branch **≥95%**; Boundary line **≥90%**; Data line **≥90%**; 전체 line **≥85%** |
| G-05 | OCP | 신규 단위 추가 PR에서 **LengthConversionService（동등 Domain Service）파일 diff 0** |

## 1.4 비목표（Non-Goal）

| ID | 비목표 |
|----|--------|
| NG-01 | GUI·웹·모바일 클라이언트 |
| NG-02 | CI/CD 파이프라인·컨테이너 배포·상용 SLA |
| NG-03 | feet↔yard **직접** 고정 비율（meter 허브 경유만 in-scope） |

---

# 2. 사용자 및 이해관계자

## 2.1 타깃 사용자（페르소나 1）

| 필드 | 내용 |
|------|------|
| 이름（가칭） | **지훈** |
| 역할 | C++ 기초 보유, 클린 아키텍처·TDD 입문 학습자 |
| 목표 | 계약 고정 → RED → 레이어 분리 GREEN → 회귀 증명 |
| 제약 | 실습 **6시간**, README·Phase 4 Gherkin 준수, AI 보조 허용 |
| 성공 감각 | “단위 추가 시 변환 식 파일은 안 건드렸다” + “깨진 TC가 계약 위반을 가리킨다” |

**이해관계자（저장소 범위）**

| 이해관계자 | 관심 |
|------------|------|
| 학습자（지훈） | Activities 1~5 산출물·회고 |
| 강사/리뷰어 | Level 5 Gate·커버리지·Traceability |
| 자동화（Catch2） | Invariant·ERR-*·golden |

## 2.2 주요 사용 시나리오（Phase 4 Journey 기반）

| # | 시나리오 | Journey | 행동 요약 | 성공 신호 |
|---|----------|---------|-----------|-----------|
| SCN-01 | **계약 우선 변환** | J2→J4 | RED 제목 작성 → Domain GREEN | `meter:2.5` ε 통과 |
| SCN-02 | **실패 계약 CLI** | J5→J6 | 잘못된 입력·unknown·config 오류 | exit **1**, stdout **빈**, stderr `ERR-*` |
| SCN-03 | **확장·회귀** | J6→J7 | cubit 등록 → 3포맷 출력 → golden | 등록 후 변환 Green; 리팩토링 후 golden diff **0** |

---

# 3. 기능 요구사항

## 3.1 핵심 기능 목록

| ID | 기능 | 우선순위 | Story |
|----|------|----------|-------|
| F-01 | `unit:value` 변환（기본 3단위） | **필수** | US-03 |
| F-02 | 입력 검증（형식·음수·0·미등록） | **필수** | US-01 |
| F-03 | UnitRegistry + meter 허브 환산（OCP） | **필수** | US-02, US-03 |
| F-04 | Catch2 Domain/Boundary/통합 TC | **필수** | US-03, US-07 |
| F-05 | 출력 포맷 table / json / csv | **권장** | US-04 |
| F-06 | JSON（또는 YAML）설정 로드 | **권장** | US-05 |
| F-07 | 동적 단위 등록 `1 u = n meter` | **권장** | US-06 |
| F-08 | argv `--format`, `--config` | **선택** | US-04, US-05 |
| F-09 | 등록 영속（save/reload） | **선택** | US-06（통합 확장） |

## 3.2 기능별 입·출력 계약（문자열）

### F-01 변환（CONVERT）

| 항목 | 계약 |
|------|------|
| 입력（stdin） | `{symbol}:{positive_decimal}`；예: `meter:2.5` |
| 입력 정규식 | `^([a-z0-9_]+):(\d+(\.\d+)?)$` |
| 성공（exit） | **0** |
| 실패 | exit **1**；stdout **빈**；stderr `ERR-{CODE}: {message}` |

### F-02 검증

| 조건 | CODE | stderr 시작 |
|------|------|-------------|
| 정규식 불일치·콜론 누락·이중 소수점 `2.5.3` | `INPUT_FORMAT` | `ERR-INPUT_FORMAT:` |
| value ≤ 0 | `INPUT_NEGATIVE` | `ERR-INPUT_NEGATIVE:`（raw 숫자 토큰 포함） |
| 미등록 symbol | `INPUT_UNKNOWN_UNIT` | `ERR-INPUT_UNKNOWN_UNIT:`（symbol 포함） |

### F-07 동적 등록（REGISTER）

| 항목 | 계약 |
|------|------|
| 입력 | `1 {symbol} = {positive_decimal} meter` |
| 정규식 | `^1\s+([a-z0-9_]+)\s*=\s*(\d+(\.\d+)?)\s+meter$` |
| 성공 | exit **0**；이후 CONVERT에서 symbol 사용 가능 |
| factor ≤ 0 | `ERR-INPUT_INVALID_FACTOR` |
| 중복 symbol | `ERR-INPUT_DUPLICATE_REGISTER` |

### F-06 설정

| 항목 | 계약 |
|------|------|
| argv | `--config={path}` |
| 성공 | Registry가 파일 정의로 부트스트랩；US-03과 **동일 환산 결과** |
| 파일 없음/파싱 실패 | `ERR-CONFIG_LOAD` |
| meter 누락·`meters_per_unit` ≤ 0 | `ERR-CONFIG_SCHEMA` |

## 3.3 제약 사항（Gherkin Background와 일치）

### Canonical ratios（Background Given — 변경 시 Gherkin BG·PRD 동시 개정）

| unit | definition |
|------|------------|
| meter | 1 meter = 1 meter |
| feet | 1 meter = **3.28084** feet |
| yard | 1 meter = **1.09361** yard |

**환산 규칙:** 모든 쌍은 **meter 허브만** 사용。feet↔yard 직접 상수 **금지**（NG-03）。

### 입력·단위·음수

| 제약 ID | 규칙 | 검증 |
|---------|------|------|
| C-01 | symbol charset: `[a-z0-9_]+` | 파싱 TC |
| C-02 | 기본 Registry: meter, feet, yard | Bootstrap size = 3 |
| C-03 | **POL-NEG-01:** length value **> 0** only | `meter:-1`, `meter:0` → `ERR-INPUT_NEGATIVE` |
| C-04 | 미등록 symbol CONVERT → 변환 **미호출** | Gherkin S6 |
| C-05 | Domain 계산: 반올림 **없음**（raw double） | ε TC |
| C-06 | Boundary 표시: target **소수 1자리 half-up** | 8.2 / 2.7 |

### POL-NEG（음수 입력 정책）

| Policy ID | Rule | Verifiable outcome |
|-----------|------|-------------------|
| POL-NEG-01 | Parsed length value must be **strictly greater than 0** | Violations never invoke conversion |
| POL-NEG-02 | Zero and negative inputs rejected at Boundary before Control/Domain | Exit **1**; stderr `ERR-INPUT_NEGATIVE:`; stdout empty |
| POL-NEG-03 | Error message includes the raw numeric token from input | Regex on stderr content |

---

# 4. 비기능 요구사항

## 4.1 기술 스택

| 항목 | 버전/도구 |
|------|-----------|
| 언어 | **C++17** |
| 빌드 | **CMake**（실습 산출물 표준；README g++ 한 줄은 로컬 대안） |
| 테스트 | **Catch2 v3** |
| 실행 형태 | 콘솔 CLI（stdin/stdout/stderr） |

## 4.2 아키텍처 원칙

| 원칙 | 규칙 | 검증 |
|------|------|------|
| BCE | Boundary（파싱·직렬화） / Control（유스케이스） / Entity（Registry·환산） / Data（설정 로드） | 의존 방향 단방향 |
| 의존성 | Boundary → Control → Domain；Control → Data 포트；**Domain → Boundary/Data 참조 금지** | 리뷰·정적 구조 |
| OCP | 신규 단위 = Registry 등록（+ 설정/REGISTER）；**Conversion 알고리즘 변경 0** | G-05 |
| SRP | Parser / Registry / Conversion / Serializer / Repository **분리** | Traceability |

## 4.3 테스트 커버리지 목표

| 레이어 | line | branch |
|--------|------|--------|
| Domain | ≥ **98%** | ≥ **95%** |
| Boundary | ≥ **90%** | ≥ **85%** |
| Data | ≥ **90%** | — |
| 전체 | ≥ **85%** | — |

**미달:** Domain 미달 → **인수 불가**；Boundary/Data는 통합 TC 전부 Green 시 1회 예외（문서화 필수）。

## 4.4 확장성 원칙

| 규칙 | 측정 |
|------|------|
| 단위 추가 시 변경 허용 파일 | Registry 등록·설정·REGISTER 파서·Serializer 목록（필요 시） |
| 변경 금지 | meter 허브 환산식（한 곳） |
| 동적 등록 후 | `ConversionBatch` 줄 수 = `Registry.size()`（D-INV-04） |

---

# 5. 데이터 요구사항

## 5.1 단위 비율 상수（meter 허브）

내부 표현: **`meters_per_unit`** = “1 `{unit}` = N meter”。

| symbol | meters_per_unit（정의） | 산출 |
|--------|-------------------------|------|
| meter | **1.0** | 기준 |
| feet | **1 / 3.28084** ≈ 0.3048（파일은 명시 상수 허용） | 1 m = 3.28084 ft |
| yard | **1 / 1.09361** ≈ 0.9144 | 1 m = 1.09361 yd |

**환산식（Domain）:** `target = source × meters_per_unit(source) / meters_per_unit(target)`（ε = 1e-9）。

## 5.2 설정 외부화

| 항목 | 규칙 |
|------|------|
| 형식 | **JSON 필수 지원**；YAML **선택**（README 허용） |
| 부트스트랩 | `--config` 없으면 **InMemory 기본값**（위 3단위） |
| 최소 JSON 필드 | `base_unit`（문자열 `"meter"`）, `units[]` with `symbol`, `meters_per_unit` |
| 실패 | `ERR-CONFIG_LOAD` / `ERR-CONFIG_SCHEMA`；**stdout 변환 줄 0** |

**최소 JSON 예시**

```json
{
  "base_unit": "meter",
  "units": [
    { "symbol": "meter", "meters_per_unit": 1.0 },
    { "symbol": "feet", "meters_per_unit": 0.3048 },
    { "symbol": "yard", "meters_per_unit": 0.9144 }
  ]
}
```

## 5.3 동적 단위 등록 계약

| 항목 | 값 |
|------|-----|
| 명령 형식 | stdin 한 줄: `1 {unit} = {factor} meter`（`register:` 접두사 **없음**） |
| 의미 | 1 `{unit}` = `{factor}` meter → `meters_per_unit(unit) = factor` |
| 예시（README） | `1 cubit = 0.4572 meter` |
| meter 재정의 | **거부** |
| 세션 | 기본: **프로세스 메모리 Registry**（F-09 영속은 선택） |

---

# 6. 출력 요구사항

## 6.1 공통 정책

| ID | 규칙 |
|----|------|
| OUT-01 | 성공: exit **0**；실패: exit **1** |
| OUT-02 | 성공 시 stderr **빈** |
| OUT-03 | **Source preservation:** 출발 `unit`·`value`는 모든 포맷에서 **입력과 동일** |
| OUT-04 | target 값 **표시만** 소수 **1자리 half-up** |
| OUT-05 | 줄/행 순서 = Registry **삽입 순** |
| OUT-06 | argv `--format=table|json|csv`（기본 **table**） |

## 6.2 JSON 스키마（F-05）

| 필드 | 타입 | 규칙 |
|------|------|------|
| `source.unit` | string | 입력 symbol와 **동일** |
| `source.value` | number | 입력 파싱값（예: 2.5） |
| `conversions[]` | array | 길이 = Registry.size() |
| `conversions[].unit` | string | target symbol |
| `conversions[].value` | number | **1자리 half-up** |

## 6.3 CSV 스키마（F-05）

| 행 | 내용 |
|----|------|
| 1（헤더） | `source_unit,source_value,target_unit,target_value`（고정 문자열） |
| 2+ | `{src_unit},{src_val},{tgt_unit},{tgt_val}`；`tgt_val` **1자리 half-up** |

## 6.4 Table 스키마（F-05, 기본）

| 항목 | 규칙 |
|------|------|
| 한 줄 패턴 | `{source_value} {source_unit} = {target_value} {target_unit}` |
| 예 | `2.5 meter = 8.2 feet` |
| 줄 수 | Registry.size() |

---

# 7. 성공 지표

## 7.1 인수 기준（US / Gherkin 대조）

- [ ] **AC-01（US-03, Gherkin S1, BG）:** `meter:2.5` table → `2.5 meter = 8.2 feet`, `2.5 meter = 2.7 yard`；stderr 빈。
- [ ] **AC-02（US-01, Gherkin S2,S3,S6,S7）:** `meter:2.5.3` / `meter:-1` / `cubit:1`（미등록）/ `meter2.5` → exit 1, `ERR-*`, stdout 빈；POL-NEG 문서 **선행**。
- [ ] **AC-03（US-04, Gherkin S4,S5）:** JSON `source.unit=meter`, `source.value=2.5`；table **모든 줄** `2.5 meter =` 접두。
- [ ] **AC-04（US-06, Gherkin S8）:** `1 cubit = 0.4572 meter` 후 `cubit:1` → feet·yard 줄 존재；meter-chain **ε 통과**。
- [ ] **AC-05（US-05）:** `bad_schema.json`（meter 없음）→ `ERR-CONFIG_SCHEMA`；stdout 0줄。
- [ ] **AC-06（G-04）:** 커버리지 임계 **수치 충족**（리포트 첨부）。
- [ ] **AC-07（G-05, US-02）:** cubit 추가 PR에서 Conversion Service **diff 0**。

## 7.2 회귀 보호 규칙

| ID | 정책 | 검증 |
|----|------|------|
| REG-01 | Background 비율（3.28084, 1.09361）**변경 금지** | drift TC **실패** |
| REG-02 | `ERR-{CODE}` 집합 **동결** | stderr 스냅샷 |
| REG-03 | table/json/csv **golden file**；의도 외 diff → merge 차단 | 로컬 pre-merge 필수 |
| REG-04 | POL-NEG-01~03 **삭제·완화 금지** | S3 TC Green 유지 |
| REG-05 | Source preservation（OUT-03）**삭제 금지** | S4,S5 TC |

---

# 8. 용어 정의（Glossary）

| 용어 | 정의 |
|------|------|
| **meter 허브** | 모든 환산이 `meters_per_unit`를 통해서만 수행되는 단일 기준 모델。 |
| **UnitRegistry** | 등록된 단위 정의 집합；중복·meter=1.0 불변 유지。 |
| **ConversionBatch** | 한 번의 CONVERT에 대한 전 단위 결과 줄 집합；줄 수 = Registry.size()。 |
| **Boundary** | stdin/argv 파싱, ERR-* 매핑, table/json/csv 직렬화；Domain 계산 없음。 |
| **POL-NEG** | value ≤ 0 거부；`ERR-INPUT_NEGATIVE`；변환 미호출。 |
| **Source preservation** | 출력 전 포맷에서 입력 `unit`·`value` 변형 없음（표시 반올림은 target만）。 |
| **Dual-Track TDD** | Domain RED→GREEN 후 Boundary（Mock Control）→ Data → 통합 순。 |
| **ε（epsilon）** | Domain raw 비교 허용 오차 **1e-9**。 |
| **golden** | 고정 입출력 스냅샷；REG-03 회귀 기준。 |
| **OCP（실습 정의）** | 신규 단위 추가 시 Conversion 알고리즘 파일 **변경 0**。 |

---

# 부록 A — Gherkin 시나리오 매핑

| Scenario | PRD |
|----------|-----|
| S1 Happy table | §6.4, AC-01 |
| S2 Decimal fail | §3.2 F-02 |
| S3 Negative POL-NEG | §3.3 C-03, AC-02 |
| S4 JSON source | §6.2, AC-03 |
| S5 Table prefix | §6.4, AC-03 |
| S6 Unknown | §3.2, AC-02 |
| S7 No colon | §3.2, AC-02 |
| S8 Register cubit | §5.3, AC-04 |

---

# 부록 B — User Story 추적

| Story | PRD 절 |
|-------|--------|
| US-01 | §3.2 F-02, §3.3 C-01,C-03,C-04, AC-02 |
| US-02 | §4.4, AC-07 |
| US-03 | §3.3 BG, §5.1, AC-01 |
| US-04 | §6, AC-03 |
| US-05 | §5.2, AC-05 |
| US-06 | §5.3, AC-04 |
| US-07 | §7, §4.3 |

---

# 변경 이력

| 버전 | 날짜 | 변경 |
|------|------|------|
| 1.0 | 2026-05-20 | Phase 4 기준 초안（Epic/Journey/Story/Gherkin 정합） |
