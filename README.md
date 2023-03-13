# B612 Algorithm Study
B612 1학기 알고리즘 스터디 레포입니다.

## repository structure
---
```
algorithmStudy
  | nx006
    | week1
      | (문제 번호) (문제 이름)
        | (정답코드).src
        | (풀이).md
      | 1000번 A+B
        | main.cpp
        | 1000.md
        
    | week2
      | 1003번 피보나치 함수
        | main.py
        | 1003.md
```
> 소스의 이름은 굳이 상관은 없지만, 나머지 폴더 구조, 이름 양식같은 것은 지켜주셔야 합니다.

## Rule
---
1. 리뷰 자료는 상세하게 쓰기
  - 모든 리뷰 자료(.md, 노션 페이지)는 글만 읽어도 이해할 수 있게끔 작성(간결하되 친절하게)
  - 기본적인 내용을 전부 다 적을 필요는 없음.
  - 그러나 리뷰 자료만 보고서도 이 문제를 어떻게 풀었는지 알 수 있게 적어야 함 (나에게 직접 설명한다는 느낌)
  - 노션 페이지와 레포지토리에 올라오는 내용을 일치시킬 것
2. 소스 코드 역시 알아보기 쉽게끔 작성
  - 변수명 등을 되도록 알아보기 쉽게끔 작성한다
  - 기본적인 클린 코드 규칙 적용
    - 수식이 길고 복잡하면 변수 단위로 나눈다
    - 필요할 경우 적절히 주석을 활용한다
    - `num`과 같은 추상적인 의미의 변수를 최대한 피한다.
    - 필요할 경우 주석 사용
  - 코딩 스타일은 본인의 방식을 따르나, 최대한 일관되게 적용
  - cpp의 경우 clang-format 사용 권장, 다른 언어 역시 그에 맞는 코드 포매터 적용
3. 매주 화요일 18:00 전까지 PR 완료해야 함
4. 커뮤니케이션
  - PR을 완료한 후 카톡으로 PR 완료했다고 말하기
5. 제출자료
  - 문제 번호와 이름으로 된 파일에, `소스 파일`, `.md`, `이미지 등 기타 자료들`만 제출
  - 나머지 구성 파일들(`.exe`, `sln`, `CMakeList`, `makefile` 등등은 제출 X)
6. 남의 코드 파일은 수정하지 않는다.

## Process
---
1. 해당 레포지토리를 fork 한 후에, 본인 id로 된 브랜치를 생성
2. 매주 한 문제 이상을 소스코드와 풀이와 함께 같은 폴더에 담아서 본인 fork해간 레포에 push한 후, 화요일 18:00 전까지 이 레포의 본인 id 브랜치에 Pull Request 생성
3. 카카오톡에 PR 날렸다고 말하기
4. 노션에도 동일하게 자료 생성

## PR 가이드
### PR 사용법
1. 이 레포를 본인 깃허브 계정으로 fork 한다.
2. fork 한 레포를 클론한다. `git clone [레포 클론 주소]` 사용
3. `git remote -v`를 통해 먼저 연결된 원격 저장소를 확인한다.
  - 보통 다음과 같이 되어 있을 것
  ```
  origin  https://github.com/nx006/algorithm-study.git (fetch)
  origin  https://github.com/nx006/algorithm-study.git (push)
  ```
  - `git remote add upstream https://github.com/HongikB612/algorithm-study.git`를 입력하여 원격 저장소에 원본 저장소를 추가한다
  - 참고로 origin과 upstream은 변수명임. 여기에 원격 레포지토리 주소를 변수로써 저장한다는 뜻임
4. 매번 새로 들어올 때마다, `git fetch upstream`을 통해 원본 저장소와 내 포크한 레포를 동기화시켜주는 것이 좋다.
  - `fetch`는 이후에 `merge` 과정을 거쳐야 하는데, fetch+merge를 합친 명령어로 `pull`이 있다.
  - `git pull upstream main`해서 원본 저장소의 main 레포지토리를 pull한다.
  - 참고로 이 pull 과정을 안 했을시 이후에 merge conflict 등 다양한 문제가 발생할 수 있어서, 꼭 pull을 해주는게 좋다
  - `git pull upstream submit`도 해서 submit도 동기화시켜주자.
  - 제가 최대한 main과 submit은 화요일/목요일마다 머지는 시켜놓을텐데, 가끔 까먹고 안 되어 있을 수 있거든요? 그래서 잘 확인해주시면 됩니다.
5. 작업을 열심히 마무리하고선, `git add [파일명]`을 통해 변경사항이 들어있는 파일을 스테이징 아리아로 옮긴다.
  - `git add .`를 하면 모든 변경된 파일이 스테이징 아리아에 올라간다.
  - 대신 이때는 수동으로 필요없는 파일들은 지운다.
  - `git add 1003.md`를 하면 1003.md 파일만 스테이징 아리아에 올라간다.
6. `git commit -m [커밋메시지]`로 스테이징된 파일들을 로컬 레포지토리로 옮긴다
  - 커밋 메시지 컨벤션은 후술할 내용 참조
7. `git push origin`으로 원격 레포지토리에 푸시한다.
  - 참고로 이때 origin 뒤에 브랜치 이름을 붙인다면 해당 브랜치로 푸시된다
  - 예를 들어 `git push origin nx006`라 하면 nx006라는 브랜치로 푸시됨
  - **upstream**으로 푸시하지 않는다.
8. 이후에 github.com으로 가서, 변경사항을 확인한 후 `Create Pull Request`를 눌러 `pull request`를 생성해준다
9. merge conflict가 나는지 확인한 후에, submit 브랜치에 PR을 생성한다
10. 카카오톡/디스코드에 PR 올렸다고 말한다.

### PR 이후
매주 화요일마다 제(nx006)가 PR을 모두 체크한 뒤에, main으로 머지할 것입니다. 만약 수정사항이 있으면 PR을 거절하고, 다시 PR을 보내달라고 요청할 것입니다. 이때 목요일까지 다시 수정해서 올려주시면 됩니다.

## 커밋 규칙
커밋 메시지는 일관되게 작성해주세요. 여기서는 딱히 커밋 규칙에 대한 강제사항을 두지는 않겠으나, 다음 규칙을 적용하면 보기 편합니다.

1. 단위 기능 별로 커밋한다.
  - 너무 많은 커밋을 남기는 것은 좋지 않으나, 적당히 기능/수정 사항 별로 쪼개서 커밋을 남기는 게 좋다.
2. 커밋 메시지는 일관되게 영어로 작성한다.
  - 커밋 메시지 규칙은 하단을 참고해주세요.
3. 제목과 본문을 빈 행으로 구분한다
4. 제목을 50글자 내로 제한
5. 제목 첫 글자는 대문자로 작성
6. 제목 끝에 마침표 넣지 않기
7. 제목은 명령문으로 사용하며 과거형을 사용하지 않는다
8. 본문의 각 행은 72글자 내로 제한
9. 어떻게 보다는 무엇과 왜를 설명한다

근데 3번부터는 사실 저도 안 지켜서, 너무 빡빡하게는 안 지켜도 됨. 오히려 너무 엄격한 커밋 양식은 그 효율성을 떨어뜨린다고 생각해서, 개인적으로는 커밋 규칙을 엄격하게 강요하는 걸 별로 안 좋아하긴 합니다. 그냥 본인이 생갔했을 때 일관되게 하시면 됩니다.

### 커밋 유형 양식
- Feat : 새로운 기능의 추가
- Fix: 버그 수정
- Docs: 문서 수정
- Style: 스타일 관련 기능(코드 포맷팅, 세미콜론 누락, 코드 자체의 변경이 없는 경우)
- Refactor: 코드 리펙토링
- Test: 테스트 코트, 리펙토링 테스트 코드 추가
- Chore: 빌드 업무 수정, 패키지 매니저 수정(ex .gitignore 수정 같은 경우)

예시
```
Docs: Update Readme
```
```
Feat: Add Fibonacci function
```
```text
Fix: Fibonacci function to working with long long type

Now fibonacci function uses long long type, and if overflows happens function throws error
```
```
Fix: Anagram_hash function returns invalid hash error

Now anagram_hash function returns valid hash, which is ordered by lexicographical order
```
```
Style: Apply clang-format to main.cpp, use llvm format
```
```
Refactor: Rename the cnt variable to testCount

Rename the variable with more descriptive name
```
```
Refactor: remove unused import
```

참고로 커밋 메시지 규칙같은 건 팀마다 다릅니다. 어디서는 `DOCS Update readme` 이런 식으로 쓰기도 하고, `:` 이거를 붙이기도 하고, 안 붙이기도 합니다.
알골 스터디에서는 거기까지 제한을 두지 않되, 본인에게 맞추어서 일관되게 작성해주시면 됩니다.