#include<iostream>
using namespace std;
class A
{
	int a;
	
public:
	A(){}
	A(int _a) : a(_a) {  }
	virtual void show() = 0;
};

class B : public A
{
	int b;
	void show() //override
	{
		cout << "B: " << b << endl;
	}
public:
	B(int _b) : b(_b) {}
};

int main(void)
{
	A* pb = new B(10);
	pb->show();
}