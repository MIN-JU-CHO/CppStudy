# CppStudy
 C++Study
## C++ 문법 개념 정리
[노션 링크](https://phrygian-kitten-eda.notion.site/C-CS-7ec928eb101844a399b81414ff94cc15?pvs=4)

[[복사 생성자 코드]](https://github.com/MIN-JU-CHO/CppStudy/blob/main/5_3_CopyConstructor.cpp)
[[copy elision 실험 코드]](https://github.com/MIN-JU-CHO/CppStudy/blob/main/5_4_CopyElision.cpp)
[[생성자 관련 개념 정리]](https://phrygian-kitten-eda.notion.site/C-CS-7ec928eb101844a399b81414ff94cc15?pvs=4)

[[static 변수 코드]](https://github.com/MIN-JU-CHO/CppStudy/blob/main/5_4_ClassStaticVar.cpp)
[[class 변수 관련 개념 정리]](https://phrygian-kitten-eda.notion.site/C-CS-7ec928eb101844a399b81414ff94cc15?pvs=4)

[[Custom String Class 코드]](https://github.com/MIN-JU-CHO/CppStudy/blob/main/5_5_StringClass.cpp)
[[Explicit, Mutable 실험 코드]](https://github.com/MIN-JU-CHO/CppStudy/blob/main/5_6_ExplicitMutable.cpp)

[[Custom String Class 연산자 오버로딩 및 함수 성능 비교 (chrono)]](https://github.com/MIN-JU-CHO/CppStudy/blob/main/6_1_Overloading.cpp)
[[복소수 Class 코드 - 연산자 오버로딩]](https://github.com/MIN-JU-CHO/CppStudy/blob/main/6_1_ComplexNumber.cpp)
[[연산자 오버로딩 관련 개념 정리]](https://phrygian-kitten-eda.notion.site/C-CS-7ec928eb101844a399b81414ff94cc15?pvs=4)

[[13-1 이동 생성자 원리 (noexcept)]](https://github.com/MIN-JU-CHO/CppStudy/blob/main/13_1_RValueReference.cpp)
<img src="https://github.com/MIN-JU-CHO/CppStudy/assets/60171052/e391a6d3-7c01-4de1-8a8f-0c82e17cfb4e.png" width="500" height="500"/>
> 1. 마지막에 추가되는 벡터의 원소를 먼저 복사 생성한다.
> 2. 새 벡터 공간에 기존 원소들을 이동 생성한다.

> 이동 생성 전, 후의 원소 주소값이 다르고, 새로 추가되는 원소의 주소값 부근에 이동됨에 유의하자.
