# 대화 프롬프트 기록 — 024-20260521-golden-master-approval-regression

- **보고서 번호**: 024
- **저장일**: 2026-05-21 12:58
- **출처**: agent-transcripts `fad4c86e-614c-4912-aef0-a766add70d59.jsonl`

---

## Turn 1

**User**

[P] 회귀 테스트(Approval/Golden Master) 설계 전문가입니다.
[C] C++17, CMake, Catch2
[T] UnitConverter 출력 기반 Golden Master 기준 파일을 생성해줘.

    1) 기준 출력(tests/golden_master_expected.txt) 생성/보관 전략
       입력 시나리오 4개:
         "meter:2.5" / "feet:1.0" / "yard:1.0" / "meter:0.0"
       캡처 방식: stdout 리디렉션: ./UnitConverter < input.txt > actual.txt
       생성 후: git add tests/golden_master_expected.txt  (버전 관리 필수)

    2) approve 패턴 적용:
       - 기준 파일 없으면 → 현재 출력을 기준으로 자동 생성
       - 기준 파일 있으면 → actual vs expected 문자열 비교
       - 불일치 시: diff 출력 후 테스트 FAIL

    3) 기준 파일 구조:
       [meter:2.5]
       2.5 meter = 8.202100 feet
       2.5 meter = 2.734025 yard
       ---
       [feet:1.0]
       ...

[F] tests/golden_master_expected.txt 파일 내용 + 생성 스크립트

**Assistant**

Golden Master 기준 파일과 승인 패턴 테스트를 추가하기 위해 프로젝트 구조와 UnitConverter 출력 형식을 확인합니다.

*(도구: Glob, Grep, Read requirements.md, CMakeLists.txt, UnitConverter.cpp, TableOutputSerializer, ErrorCodes, ConvertInputParser, LengthConversionService 등)*

---

## Turn 2–10

**Assistant** (중간 탐색·캡처)

- `build/UnitConverter.exe` 빌드 후 4 시나리오 stdin/stdout/stderr 캡처 (`cmd /c` 리디렉션)
- 실제 출력: half-up 1자리(8.2 feet, 2.7 yard 등), `meter:0.0` → stderr `ERR-INPUT_NEGATIVE: 0.0`
- 기존 integration 테스트·fixture 패턴 참고

---

## Turn 11

**Assistant**

Golden Master 기준 파일, 승인 패턴 Catch2 테스트, 생성 스크립트를 추가합니다. 실제 CLI 출력(half-up 1자리)을 기준으로 합니다.

*(도구: Write — golden_master_expected.txt, GoldenMasterApproval.hpp/cpp, test_golden_master.cpp, generate_golden_master.ps1/.sh; CMakeLists.txt 수정)*

---

## Turn 12–15

**Assistant**

- `diffLines` 시그니처 오타 수정 (`std::::string` → `std::string`)
- CMake: `UNIT_CONVERTER_SOURCE_DIR`, `UNIT_CONVERTER_EXE_PATH`, 헬퍼 include, `add_dependencies(unit_converter_tests UnitConverter)`
- 빌드·`golden_master_cli_stdout_approval` 실행 → CRLF/LF 불일치 발견

---

## Turn 16

**Assistant**

CRLF 정규화가 필요합니다. Windows CLI 캡처는 `\r\n`이고 기준 파일은 LF입니다.

`normalizeNewlines()` 추가, strip/read/write/비교 경로에 적용 후 재빌드·테스트 PASS.

---

## Turn 17

**Assistant**

- 전체 CTest: **69/69 passed**
- `tests/.gitignore`에 `.golden_master_scratch/` 추가
- golden master 관련 파일 `git add` 스테이징
- 임시 `tests/tmp_golden` 제거

**Assistant** (최종 요약)

Golden Master(Approval) 회귀 테스트 구성을 마쳤습니다. 전체 69개 테스트가 통과합니다.

## 기준 파일 `tests/golden_master_expected.txt`

실제 CLI 출력(half-up 1자리 표시)을 반영했습니다. 예시의 `8.202100`은 raw domain 값이고, 현재 구현은 README/TC-A-01과 동일하게 `8.2` / `2.7`입니다.

- 성공 시나리오: 프롬프트 제거 후 변환 줄만 기록
- `meter:0.0`: stderr `ERR-INPUT_NEGATIVE: 0.0` 기록 (exit 1)

## Approval 패턴 (Catch2)

| 조건 | 동작 |
|------|------|
| 기준 파일 없음 | 현재 CLI 출력으로 자동 생성 후 PASS |
| 기준 파일 있음 | `actual` vs `expected` 문자열 비교 |
| 불일치 | line diff 출력 후 **FAIL** |

캡처: `cmd /c UnitConverter < input.txt > stdout.txt 2> stderr.txt` (Windows), 프롬프트 제거 + CRLF→LF 정규화.

## 생성 스크립트

- `.\scripts\generate_golden_master.ps1` / `.\scripts\generate_golden_master.ps1 -GitAdd`
- `./scripts/generate_golden_master.sh build --git-add`

## Git

다음 파일을 스테이징했습니다. 커밋은 요청하시면 진행하겠습니다.

---

## Turn 18

**User**

보고서 작성 및 저장 Agent 실행해줘

**Assistant**

보고서 작성·저장 에이전트 규칙을 확인한 뒤 실행합니다.

*(report-github-manager 워크플로 시작)*

---

## Turn 19 (본 저장 세션)

**User** (report-github-manager Task)

보고서 작성 및 저장 — 024번 golden master 세션 전체 4단계 워크플로 실행 지시.

**Assistant** (report-github-manager)

Report/Prompting/Prompting_user 024 파일 작성 및 git commit·push 수행.
