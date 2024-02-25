#include <iostream>
using namespace std;

class A
{
public:
	A()
	{
		cout << "construct\n";
	}
	A(const A& a)
	{
		cout << "copy construct\n";
	}
	A(A&& a)
	{
		cout << "move construct\n";
	}
};

class B
{
	A a;
public:
	B() : a() {}
	B(A&& _a) : a(move(_a)) {}
};

int main(void)
{
	A a;
	B(move(a));
}