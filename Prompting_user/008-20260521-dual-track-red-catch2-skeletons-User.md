# User 프롬프트만 — 008-20260521-dual-track-red-catch2-skeletons

- **보고서 번호**: 008
- **저장일**: 2026-05-21

---

## User Prompt 1

당신은 Dual-Track UI + Logic TDD 전문가입니다.
프로젝트: c:\DEV\UnitConverter_Cpp
현재 코드 상태: 단일 main() 함수, if-else 체인, 예외 처리 없음

중요: 구현 코드 작성 금지 / GREEN 단계 금지 / REFACTOR 금지
오직 RED 테스트만 작성하십시오.

프로젝트 조건:
- 입력: std::string (단위:값) (예: "meter:2.5")
- 변환: 1 meter = 3.28084 feet, 1 meter = 1.09361 yard
- 출력: "2.5 meter = 8.202100 feet" 형식
- 예외: std::invalid_argument

TRACK A — UI / Boundary RED:
1. "meter:2.5" 정상 입력 → 변환 결과 반환
2. ":" 없는 입력 → 예외 발생 (잘못된 형식)
3. 음수 값 입력 ("meter:-1.0") → 예외 발생
4. 없는 단위 ("parsec:1.0") → 예외 발생
5. 반환 포맷에 원 입력 단위·값 보존 확인
6. JSON 출력 요청 시 올바른 스키마 반환
각 테스트에: 테스트 이름 / Given / When / Then / 보호하는 계약

TRACK B — Domain / Logic RED:
1. convert(fromUnit, value, toUnit) — meter↔feet 정확도 (1e-5 이내)
2. convert(fromUnit, value, toUnit) — meter↔yard 정확도
3. convertAll(fromUnit, value) — 모든 등록 단위로 변환 반환
4. registerUnit(name, ratio_to_meter) — 새 단위 등록 후 변환 가능
5. loadConfig(path) — JSON/YAML 설정 파일 로드 후 비율 적용
6. loadConfig(invalid_path) — 파일 없을 때 기본값 유지
각 테스트: 실패 상태 명확히 설명 / 보호 Invariant 명시

출력 형식:
# UI RED Tests — Test ID / Given/When/Then / Invariant
# Logic RED Tests — Test ID / Scenario / Invariant

## User Prompt 2

Catch2 테스트 스켈레톤을 작성하라.
파일/클래스 이름만 적고, 메서드 본문은 FAIL("RED") 한 줄만.
RED 원칙으로만 작성하십시오.

예시:
TEST_CASE("convert_meter_to_feet_returns_correct_ratio","[domain]") {   FAIL("RED"); }

## User Prompt 3

You are the report-github-manager agent. Write and save a session work report for the UnitConverter_14 project at c:\DEV\UnitConverter_14.

(Session work completed summary: Dual-Track RED → full tests + contract → linker RED; then Catch2 skeletons only, 13 FAIL("RED"), build OK. Files: tests/red/*, include/contract/UnitConverterContract.hpp, CMakeLists.txt. Do NOT commit unless explicitly needed.)
