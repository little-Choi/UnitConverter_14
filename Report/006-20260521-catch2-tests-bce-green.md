# 작업 보고서 — Catch2 테스트 스위트 및 BCE 코어 GREEN 빌드

- **보고서 번호**: 006
- **작성일**: 2026-05-21
- **브랜치**: red
- **커밋(작성 시점)**: dd2ad32

## 1. 작업 개요

시니어 QA 관점 요청에 따라 Catch2 v3 기반 단위·통합 테스트 45건과 BCE 레이어(`domain` / `boundary` / `data` / `control`) 코어 라이브러리를 구현했다. Given-When-Then 주석, 변환 비율 명시, `test_[타입]_[조건]_[기대결과]` 네이밍 규칙을 적용했으며, 정상 변환·경계값·예외·동적 등록·JSON/YAML 설정 로드 항목별 최소 5개 이상 TC를 포함한다. MinGW로 `cmake --build build` 및 `unit_converter_tests.exe` 실행 결과 **45 test cases, 85 assertions 전부 Green**을 확인했다.

## 2. 변경·산출물 목록

| 구분 | 경로/항목 | 설명 |
|------|-----------|------|
| 신규 | `CMakeLists.txt` | Catch2 FetchContent, `unit_converter_core`, `unit_converter_tests`, CTest |
| 신규 | `CMakePresets.json` | MinGW Debug 프리셋 |
| 신규 | `include/`, `src/` | UnitRegistry, LengthConversionService, Parser, Serializer, ConfigLoader, Handler |
| 신규 | `tests/` | domain/boundary/data/integration 테스트 7파일 |
| 신규 | `tests/fixtures/` | `units_valid.json`, `units_invalid_schema.json`, `units_valid.yaml` |
| 수정 | `UnitConverter.cpp` | thin main, `--config`, REGISTER 라인 처리 |
| 신규 | `.gitignore` | `build/` 등 빌드 산출물 제외 |
| 보고 아카이브 | `Report/006-*.md`, `Prompting/006-*`, `Prompting_user/006-*` | 본 세션 기록 |

## 3. 주요 결정·이슈

- **결정**: meter 허브 환산식 `target = source × mpu(source) / mpu(target)`, Domain ε=1e-9, Boundary 표시 1자리 half-up.
- **결정**: 실패 계약 `ERR-INPUT_*`, `ERR-CONFIG_*` prefix; POL-NEG(value > 0) Boundary 선차단.
- **결정**: JSON 설정 feet `meters_per_unit=0.3048` — config TC는 파일 비율 기준 검증(README canonical 3.28084와 구분).
- **이슈(해결)**: Windows 기본 NMake 생성기는 컴파일러 미설정 시 configure 실패 → MinGW Makefiles + `CMakePresets.json` 제공.
- **이슈(해결)**: Catch2 v3 `Approx`는 `catch_approx.hpp` 별도 include 필요.
- **미해결**: MSVC/기본 `cmake -S . -B build`만으로는 환경별 generator 선택 필요; lcov Gate 측정 미실행.

## 4. 테스트·검증

```bash
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=C:/mingw64/bin/g++.exe
cmake --build build
./build/unit_converter_tests.exe
```

| 결과 | 내용 |
|------|------|
| 빌드 | **성공** (MinGW g++ 15.2.0) |
| 테스트 | **45 passed**, 0 failed, 85 assertions |
| 대표 Golden | `test_table_meter_25_golden_lines` — 8.2 feet / 2.7 yard |

## 5. 다음 단계

1. `ctest --test-dir build` CI 연동 및 README 빌드 절 MinGW/VS 분기 문서화.
2. §7 lcov 파이프라인으로 Domain ≥95%, Boundary ≥85% Gate 측정.
3. JSON/CSV Serializer 및 `--format` argv TC 확장(S-01~S-04).
