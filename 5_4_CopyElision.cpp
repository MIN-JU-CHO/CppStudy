#include <stdio.h>

class A {
    int x;

public:
    static int cnt_a;
    A(int c) : x(c)
    {
        ++cnt_a;
    }
    A(const A& a)
    {
        ++cnt_a;
        x = a.x;
        printf("a 복사 생성\n");
    }
};

class B {
    A a;

public:
    static int cnt_b;
    B(int c) : a(c)
    {
        ++cnt_b;
    }
    B(const B& b) : a(b.a)
    {
        ++cnt_b;
        printf("b 복사 생성\n");
    }
    A get_A() {
        A temp(a);      // a 복사 생성 1 (copy elision으로 생략)
        return temp;    // 임시 객체 복사 (복사 생성은 아니지만, copy elision으로 생략)
    }
};

// private, public 상관 없이 클래스 외부에서 초기화 가능
int A::cnt_a = 0;
int B::cnt_b = 0;
// 여러번 초기화 시 컴파일 오류 (VS error code: C2374)
//int A::cnt_a = 1;

int main(void)
{
    B b(10);
    // static 변수가 private이면 접근할 수 없음. -> static 함수로 get하는 것이 일반적
    //               public이면 접근 가능
    printf("A: %d\n", A::cnt_a);// 1
    printf("B: %d\n", B::cnt_b);// 1

    printf("---------\n");
    A a1 = b.get_A();           // a 복사 생성 2 (정상 출력)
    printf("A: %d\n", A::cnt_a);// 2
    printf("B: %d\n", B::cnt_b);// 1

    ++A::cnt_a;
    printf("static 변수가 public으로 선언되면 외부에서 수정될 가능성\n");
    printf("A: %d\n", A::cnt_a);// 3
    A::cnt_a = 4;
    printf("A: %d\n", A::cnt_a);// 4
}