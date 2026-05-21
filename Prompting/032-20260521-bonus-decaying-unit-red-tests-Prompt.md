# 대화 프롬프트 기록 — 032-20260521-bonus-decaying-unit-red-tests

- **보고서 번호**: 032
- **저장일**: 2026-05-21

---

## Turn 1

**User**

신규 기능 RED 테스트 작성 요청:

- `registerUnit("cubit", 0.4572)`, `convert`/`convertAll` 동작 검증
- `Item` 구조체(`UnitConverter.cpp` 기존 변환 로직) 수정 금지
- 음수 비율 등록 시 `std::invalid_argument`
- 테스트 BT-01~06, `TEST_CASE("감쇠 단위 변환", "[bonus]")`
- 산출물: `src/DecayingUnit.cpp` + `tests/test_decaying_unit.cpp` (실패 상태)

**Assistant**

`DecayingUnit` 모듈·RED 테스트 추가 완료.

- `include/DecayingUnit.hpp`, `src/DecayingUnit.cpp` — Item 미사용 독립 모듈; RED 스텁(`registerUnit` 미구현, `convert`→0.0, `convertAll`→{})
- `tests/test_decaying_unit.cpp` — BT-01~06 SECTION, `[bonus]` 태그
- `CMakeLists.txt` — `decaying_unit` 라이브러리 및 테스트 링크

검증:

```
cmake --build build-cov --target unit_converter_tests
build-cov\unit_converter_tests.exe "[bonus]"
```

결과: test cases 1 failed, assertions 6 failed (RED 의도).

GREEN 방향: `registerUnit` 동적 등록·음수 throw, meter 허브 `convert`/`convertAll` 구현.

(도구: Write DecayingUnit.hpp/cpp, test_decaying_unit.cpp, CMakeLists.txt, cmake build, ctest filter `[bonus]`)

---

## Turn 2

**User**

보고서 작성 및 저장 Agent 실행해줘

**Assistant**

report-github-manager 4단계: Report/Prompting/Prompting_user **032** 작성, DecayingUnit 소스·테스트·CMakeLists 및 docs 커밋, `origin` push.

(도구: git status/diff/log, Write 3 archive files, git add, commit, push)
