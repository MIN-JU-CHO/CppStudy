#include <iostream>
using namespace std;

class Parent : exception
{
public:
	virtual const char* what() const noexcept override
	{
		return "Parent!\n";
	}
};

class Child : Parent
{
public:
	const char* what() const noexcept override
	{
		return "Child!\n";
	}
};

void gogo(int a)
{
	if (a == 1)
	{
		throw Parent();
	}
	if (a == 2)
	{
		throw Child();
	}
}

int main(void)
{
	int a;
	cin >> a;
	try
	{
		gogo(a);
	}
	catch (Child & c)
	{
		cout << "Catch Child!\n";
		cout << c.what();
	}
	catch (Parent& p)
	{
		cout << "Catch Parent!\n";
		cout << p.what();
	}
}