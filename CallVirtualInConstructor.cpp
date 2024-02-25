#include <iostream>
using namespace std;
class A
{
	int level = 0;
public:
	A() { PrintLevel(); }
	A(int _level) : level(_level) { PrintLevel(); }
	virtual void PrintLevel()
	{
		cout << "A level: " << level << "\n";
	}
};

class B : public A
{
	int level = 1;
public:
	B() { PrintLevel(); }
	B(int _level) { PrintLevel(); level = _level; }
	void PrintLevel() override
	{
		cout << "B level: " << level << "\n";
	}
};


int main(void)
{
	B b(20);
	b.PrintLevel();
}