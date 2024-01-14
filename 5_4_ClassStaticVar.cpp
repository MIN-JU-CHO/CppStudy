#include <stdio.h>

class Monster
{
    // 멤버 변수 여기서 초기화 가능 (C++ 11 이후, 상수형 non-static 변수 동일)
    const int damage = 5;
    // static 변수는 클래스 내부에서 초기화 불가능
    static int cnt_monster;

public:
    // 상수형 변수는 반드시 생성자에서 initialize 필요
    // 따라서 default 생성자 불가능
    Monster() {++cnt_monster;};       //<- 선언 시 문법 에러 (const int damage; 선언만 했을 때)
    //Monster() = default;            //<- 이용 시 문법 에러 (const int damage; 선언만 했을 때)
    Monster(int d) : damage(d)
    {
        ++cnt_monster;
    }

    int GetDamage()
    {
        printf("Damage: %d\n", damage);
        return damage;
    }

    static int GetMonsterNum()
    {
        printf("Current Monsters: %d\n", cnt_monster);
        return cnt_monster;
    }
};
int Monster::cnt_monster = 0;

int main(void)
{
    printf("*********************\n");
    Monster m1 = Monster(10);
    Monster::GetMonsterNum();   // 1
    m1.GetDamage();             // 10 생성자 initializer에서 덮어씌워짐.
    Monster m2 = Monster();
    Monster::GetMonsterNum();   // 2 만약 Monster() = default; 라면 1
    m2.GetDamage();             // 5
    printf("*********************\n");
}

