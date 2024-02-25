#include <iostream>
using namespace std;

class A {};

template <typename T>
void wrapper(T&& a)
{
	test(forward<T>(a));
}

void test(A& a) {
	cout << "Left Reference Call\n";
}
void test(const A& a) {
	cout << "Const Reference Call\n";
}
void test(A&& a) {
	cout << "Right Reference Call\n";
}

int main(void)
{
	A a;
	const A ca;
	cout << "=====ORIGINAL=====\n";
	test(a);
	test(ca);
	test(A());
	
	cout << "=====WRAPPER=====\n";
	wrapper(a);
	wrapper(ca);
	wrapper(A());
}