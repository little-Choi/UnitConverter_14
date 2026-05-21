# 대화 프롬프트 기록 — 006-20260521-catch2-tests-bce-green

- **보고서 번호**: 006
- **저장일**: 2026-05-21

---

## Turn 1

**User**

[P] 테스트 설계에 강한 시니어 C++ QA입니다.
[C] C++17, CMake, Catch2
[T] 아이템 타입별 최소 5개 테스트를 작성해줘.

    대상 케이스:
    - 정상 변환: meter→feet, meter→yard, feet→meter (역변환)
    - 경계값: value=0 / 매우 큰 수 / 소수점 6자리 정확도
    - 예외: 잘못된 형식 / 음수 / 없는 단위
    - 동적 등록: registerUnit 후 변환
    - 설정 로드: JSON/YAML 정상·실패 케이스

    형식 규칙:
    - Catch2 사용
    - Given-When-Then 주석 구조
    - 각 테스트에 변환 비율 명시 (1 meter = 3.28084 feet)
    - 테스트 이름: test_[변환타입]_[조건]_[기대결과] 형식

[F] 완성된 테스트 코드. cmake -S . -B build && cmake --build build가 Red여야 함.

**Assistant**

Catch2 테스트 스위트와 GREEN 빌드를 위한 BCE 코어를 구성했습니다.

- `CMakeLists.txt` + Catch2 v3 FetchContent, `unit_converter_core`, `unit_converter_tests`
- `include/` + `src/` — Domain / Boundary / Data / Control 레이어
- `tests/` — 45개 테스트 (정상·경계·예외·동적등록·설정로드, 타입별 ≥5)
- Given-When-Then, 비율 명시, `test_[변환타입]_[조건]_[기대결과]` 네이밍
- MinGW 빌드·실행: **45 passed, 85 assertions Green**
- `CMakePresets.json`, `.gitignore` 추가

빌드 명령 (Windows MinGW):

```bash
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=C:/mingw64/bin/g++.exe
cmake --build build
./build/unit_converter_tests.exe
```

---

## Turn 2

**User**

보고서 작성 및 저장 Agent 실행해줘

**Assistant**

report-github-manager 4단계 워크플로 실행: 보고서 006, Prompt/User 아카이브, git commit & push.
