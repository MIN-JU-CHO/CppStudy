#include <stdio.h>
#include <string.h>
class MyString
{
	int len = 0;
	int mem_capacity = 0;
	char* data;
	mutable int log = 0;

public:
	MyString();
	explicit MyString(int size);
	MyString(const char* origin);
	MyString(const MyString& origin);

	~MyString();

	int GetLen() const;
	int GetCapacity() const;
	int GetLog() const;
	void Print() const;
};

MyString::MyString(int size) : len(0), mem_capacity(size), data(nullptr), log(0) {}
MyString::MyString(const char* origin) : log(0)
{
	mem_capacity = len = strlen(origin);
	data = new char[mem_capacity];
	for (int i = 0; i < len; ++i)
	{
		data[i] = origin[i];
	}
}
MyString::~MyString()
{
	if (data)
	{
		delete[] data;
	}
}

int MyString::GetLen() const
{
	++log;
	return len;
}

int MyString::GetCapacity() const
{
	++log;
	return mem_capacity;
}

int MyString::GetLog() const
{
	return ++log;
}

void MyString::Print() const
{
	++log;
	for (int i = 0; i < len; ++i)
	{
		printf("%c", data[i]);
	}
	printf("\n");
}

void PrintLen(MyString s)
{
	s.Print();
	printf("PrintLen: %d\n", s.GetLen());
	printf("PrintCapacity: %d\n", s.GetCapacity());
	printf("PrintLog: %d\n", s.GetLog());
}

int main(void)
{
	PrintLen("aa");

	// Error because of Explicit Constructor
	// PrintLen(5);
}