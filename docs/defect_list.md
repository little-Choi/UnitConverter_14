# 결함 목록 (defect_list.md)

| 항목 | 내용 |
|------|------|
| **작성일** | 2026-05-21 |
| **기준 브랜치** | `red` |
| **검증** | `ctest --test-dir build --output-on-failure` → **45 passed**, 0 failed (85 assertions) |
| **근거** | Catch2 RED→GREEN 세션, `docs/test_plan.md` 부록 A(레거시 갭), Report 003·006 이슈 |

> **상태 범례** (본 문서 하단 §2): **Fixed** = 회귀 TC Green · **Mitigated** = 문서/프리셋으로 우회 · **Open** = 미해결(Info/인프라)

---

## §1 발견 결함 목록

| ID | Severity | 변환 타입 | 재현 절차 | 기대값 | 실제값 | 근본 원인 | 수정 요약 |
|----|----------|-----------|-----------|--------|--------|-----------|-----------|
| DEF-001 | Critical | meter→feet | `LengthConversionService::convert("meter", 2.5, "feet")` (TC `test_meter_to_feet_normal_returns_82021`) | 8.202100 (`2.5×3.28084`, ε=1e-9) | 0.000000 | Domain 환산 스텁·허브식 미구현 (`return 0` 또는 빈 구현) | `src/domain/LengthConversionService.cpp`에 `meter_value = source×mpu(source)`; `return meter_value/mpu(target)` |
| DEF-002 | Critical | meter→yard | `convert("meter", 2.5, "yard")` (TC `test_meter_to_yard_normal_returns_2734025`) | 2.734025 | 0.000000 | DEF-001과 동일 — 모든 타깃 환산 실패 | DEF-001과 동일 허브식 한 경로로 전 단위 복구 |
| DEF-003 | Critical | feet→meter (역변환) | `convert("feet", 8.2021, "meter")` (TC `test_feet_to_meter_reverse_returns_25`) | 2.500000 | 0.000000 | 역환산 미구현 또는 factor 역수 오적용 | 허브식으로 meter 경유 역산 (feet `mpu=1/3.28084`) |
| DEF-004 | Critical | convertAll | `convertAll("meter", 1.0)` (TC `test_convert_all_returns_registry_size`) | batch.size()==3 | 0 또는 미구현 | `convertAll` 루프·reserve 미구현 | `registry_.units()` 순회하며 `convert` 결과 push |
| DEF-005 | Major | meter→feet (표시) | `TableOutputSerializer` + `meter:2.5` (TC `test_table_meter_25_golden_lines`) | `"2.5 meter = 8.2 feet"` | `"2.5 meter = 8.2021 feet"` (raw 그대로) | Domain raw를 Boundary 표시에 그대로 사용 — half-up 1자리 미적용 | `formatDisplayValue`에 소수 1자리 half-up; Domain 값은 변경 없음 |
| DEF-006 | Major | meter→yard (표시) | 동일 golden TC 3번째 줄 | `"2.5 meter = 2.7 yard"` | `"2.5 meter = 2.734 yard"` 등 | DEF-005와 동일 | DEF-005와 동일 포맷터 |
| DEF-007 | Major | POL-NEG (입력) | CLI/stdin `meter:0` (레거시·TC-B-07 / `test_parse_zero_value_rejected`) | `ERR-INPUT_NEGATIVE:`·exit 1·stdout 빈 | 0 허용·0 출력 | 레거시 `UnitConverter.cpp`에 value≤0 검증 없음 | `ConvertInputParser`에서 `value<=0` → `ErrorCode::InputNegative` |
| DEF-008 | Major | POL-NEG (입력) | `meter:-1` (`test_parse_negative_value_rejected`) | `ERR-INPUT_NEGATIVE:`·message `-1` | 음수 환산 허용 | DEF-007과 동일 | DEF-007과 동일 파서 정책 |
| DEF-009 | Major | 입력 형식 | `meter2.5` (`test_parse_no_colon_format_error`) | `ERR-INPUT_FORMAT:` | 파싱 성공 또는 비계약 예외 | 콜론·정규식 검증 없음 | `unit:value` 형식 검증 및 `InputFormat` 매핑 |
| DEF-010 | Major | 입력 형식 | `meter:abc` (`test_parse_abc_number_format_error`) | `ERR-INPUT_FORMAT:` | `Invalid number: abc` (자유 텍스트) | stderr 계약 미정립 | `stod` 실패 시 `InputFormat` + `errorCodeToPrefix` |
| DEF-011 | Major | unknown unit | `parsec:1.0` (`test_handler_unknown_unit_parsec`) | `ERR-INPUT_UNKNOWN_UNIT:`·`parsec` 포함 | `Unknown unit: parsec` | Registry lookup 실패 메시지 비표준 | Handler에서 `InputUnknownUnit`·symbol in message |
| DEF-012 | Major | feet↔yard | `convert("feet", 10, "yard")` (TC `test_feet_to_yard_hub_only_returns_via_meter`) | `meter_hub` 경로 값 (ε=1e-9) | 직접 상수 `3.28084/1.09361` 사용 시 drift | feet-yard 직접 비율 하드코딩 (NG-03 위반) | 오직 `×mpu(source)/mpu(target)` 허브만 사용 |
| DEF-013 | Minor | meter→feet (표시 경계) | `formatDisplayValue(5.05)` (`test_display_rounds_half_up_at_five`) | `"5.1"` | `"5.0"` 또는 `"5.05"` | half-up 미구현·truncate | 1자리 half-up 반올림 로직 |
| DEF-014 | Minor | meter→feet (정수 표시) | `formatDisplayValue(5.0)` (`test_display_integer_no_trailing_zero`) | `"5"` | `"5.0"` | 고정 소수 자릿수 출력 | 정수면 소수부 생략 |
| DEF-015 | Major | 동적 등록 | `1 cubit 0.4572 meter` 후 `cubit:1`→`meter` (integration TC) | 0.4572 m | 등록 무시·unknown | `registerUnit`·Handler 미연동 | `RegisterUnitHandler` + Registry `registerUnit` |
| DEF-016 | Major | config JSON | `JsonConfigLoader.loadFromFile(valid)` (TC `test_json_config_valid_*`) | 3 units 로드 | load 실패·empty registry | ConfigLoader·Handler 미구현 | `data/JsonConfigLoader` + `main --config=` 경로 |
| DEF-017 | Major | config 실패 | missing file / invalid schema TC | `ERR-CONFIG_LOAD` / `ERR-CONFIG_SCHEMA` | silent default 또는 crash | 설정 실패 계약 없음 | `AppError` + stderr prefix·exit 1 |
| DEF-018 | Info | (빌드) | Windows `cmake -S . -B build` (NMake, 컴파일러 미지정) | configure 성공 | `No CMAKE_CXX_COMPILER` / NMake 실패 | 기본 Generator·PATH | `CMakePresets.json` MinGW 프리셋·README 빌드 절 |
| DEF-019 | Info | (빌드) | `#include <catch2/catch_test_macros.hpp>` + `Approx` | 컴파일 성공 | `Approx` 미선언 | Catch2 v3에서 Approx 헤더 분리 | `#include <catch2/catch_approx.hpp>` |
| DEF-020 | Info | (빌드) | PowerShell `cmake -S . -B build && cmake --build build` | 빌드 성공 | `ParserError: '&&' 토큰` | PS 5.x `&&` 미지원 | `;` 구분 또는 줄 단위 명령 (README) |
| DEF-021 | Info | config JSON | `units_valid.json` feet `mpu=0.3048` vs canonical `1/3.28084` | 문서 drift TC 실패 | (설계) 파일 비율로 환산 통과 | README canonical과 파일 상수 혼동 | Config TC는 **파일 값** 검증; drift TC로 3.28084 동결 (REG-01) |
| DEF-022 | Info | (커버리지) | `lcov` Gate Domain≥95%, Boundary≥85% | 측정 리포트 | 미측정 | M-01 이후 lcov 파이프라인 미실행 | §7 `test_plan.md` lcov 스크립트·CI 연동 (Open) |
| DEF-023 | Info | (CLI) | `--format=json\|csv` argv | 3포맷 출력 | table만 | Serializer·argv 미구현 (S-04) | JSON/CSV Serializer + TC (Should, v1.0+) |

---

## §2 상태 요약

| 상태 | ID | 비고 |
|------|-----|------|
| **Fixed** | DEF-001 ~ DEF-017 | 2026-05-21 `ctest` 45/45 Green |
| **Mitigated** | DEF-018, DEF-020 | `CMakePresets.json`·README 명령 분기 |
| **Open** | DEF-021, DEF-022, DEF-023 | 설계 문서화·Should 항목; 제품 회귀 차단 아님 |

---

## §3 TC·RED 체크리스트 추적

| defect_list ID | test_plan / README | Catch2 (대표) |
|----------------|-------------------|---------------|
| DEF-001, DEF-002 | TC-B-01, TC-B-02 | `test_meter_to_feet_normal_*`, `test_meter_to_yard_*` |
| DEF-003 | TC-B-03 | `test_feet_to_meter_reverse_*` |
| DEF-004 | TC-B-04 | `test_convert_all_returns_registry_size` |
| DEF-005, DEF-006 | TC-A-01, TC-A-06 | `test_table_meter_25_golden_lines` |
| DEF-007, DEF-008 | TC-A-07, TC-A-03 | `test_parse_zero_*`, `test_parse_negative_*` |
| DEF-009 ~ DEF-011 | TC-A-02, TC-A-05, TC-A-04 | `test_parse_no_colon_*`, `test_parse_abc_*`, `test_handler_unknown_*` |
| DEF-012 | R-03 (hub) | `test_feet_to_yard_hub_only_*` |
| DEF-013, DEF-014 | 표시 경계 | `test_display_rounds_*`, `test_display_integer_*` |
| DEF-015 | TC-B-05 | `test_register_cubit_*` (integration) |
| DEF-016, DEF-017 | TC-B-06, TC-B-07 | `test_json_config_*`, `test_yaml_config_*` |

---

## §4 회귀 확인 절차

```powershell
Set-Location c:\DEV\UnitConverter_14
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

**기대:** `100% tests passed, 0 tests failed out of 45`

---

## 관련 문서

- [test_plan.md](test_plan.md) — TC ID·레거시 갭(부록 A)
- [PRD.md](PRD.md) — ERR-*·POL-NEG 계약
- [README.md](../README.md) — RED 단계 To-Do
