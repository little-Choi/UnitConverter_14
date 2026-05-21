# User 프롬프트만 — 007-20260521-defect-list-qa-document

- **보고서 번호**: 007
- **저장일**: 2026-05-21

---

## User Prompt 1

[P] 디버깅과 결함 분석에 능한 C++ QA 엔지니어입니다.
[T] (여기에 cmake -S . -B build && cmake --build build 실패 로그를 붙여넣을 것)

    1) 테스트 실패의 기대/실제 차이 요약
       예: expected 8.202100 but got 0.000000
    2) 버그 위치 특정 (파일명:줄번호)
       예: UnitConverter.cpp:27
    3) 결함 심각도 분류 및 근거:
       Critical   — 변환 결과가 완전히 틀린 경우
       Major      — 경계값에서 오차 초과
       Minor      — 출력 포맷 불일치
       Info       — 코드 스타일/주석 문제
    4) 최소 변경 수정 방안 (C++ 스타일)
       - if-else 체인 유지 최소 수정 (GREEN 통과 우선)
       - Item/기본 구조체 수정 금지

[F] 수정 diff 제안 + cmake -S . -B build && cmake --build build Green 확인 절차

## User Prompt 2

[P] QA 리드입니다.
[C] 현재까지 발견된 테스트 실패/결함들을 문서화합니다.
[T] 발견된 결함을 defect_list.md에 정리해줘.

    항목 형식:
    | ID | Severity | 변환 타입 | 재현 절차 | 기대값 | 실제값 | 근본 원인 | 수정 요약 |

[F] Markdown. docs 폴더에 defect_list.md로 저장.
    README의 "RED 단계 To-Do 리스트 > 결함 목록 연결" 체크박스도 업데이트.

## User Prompt 3

보고서 작성 및 저장 Agent 실행해줘
