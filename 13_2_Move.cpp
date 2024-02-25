#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

class MyString
{
	int id;
	int size;
	int length;
	char* data;
public:
	static int cnt;
	MyString() : size(0), length(0), data(nullptr), id(++cnt) { cout << "빈 문자열 생성\n"; }
	MyString(const char* str)
	{
		id = ++cnt;
		cout << id << " 문자열 생성\n";
		size = length = strlen(str);
		data = new char[length];
		for (int i = 0; i < length; ++i)
		{
			data[i] = str[i];
		}
	}
	MyString(const MyString& str)
	{
		id = ++cnt;
		cout << id << " 복사 생성\n";
		size = str.size;
		length = str.length;
		if (size < length)
		{
			size = length;
		}
		data = new char[size];
		for (int i = 0; i < length; ++i)
		{
			data[i] = str.data[i];
		}
		id = ++cnt;
	}
	MyString(MyString&& ref) noexcept
	{
		id = ++cnt;
		cout << id << " 이동 생성\n";
		size = ref.size;
		length = ref.length;
		if (size < length)
		{
			size = length;
		}
		data = ref.data;
		ref.length = 0;
		ref.size = 0;
		ref.data = nullptr;
	}
	~MyString()
	{
		cout << id << "해제\n";
		--cnt;
		if (data)
		{
			delete[] data;
		}
	}
	MyString& operator=(const MyString& str)
	{
		cout << "복사\n";
		if (size < str.length)
		{
			delete[] data;
			size = str.length;
			data = new char[size];
		}
		length = str.length;
		for (int i = 0; i < length; ++i)
		{
			data[i] = str.data[i];
		}
		return (*this);
	}
	MyString& operator=(MyString&& str) noexcept
	{
		cout << "이동\n";
		delete[] data;
		size = str.size;
		length = str.length;
		if (size < length)
		{
			size = length;
		}
		data = str.data;
		str.data = nullptr;
		return (*this);
	}
	int Length() const
	{
		return length;
	}
	void Print() const
	{
		cout << "id: " << id << '\t';
		for (int i = 0; i < length; ++i)
		{
			cout << data[i];
		}
		cout << "\n";
	}
};
int MyString::cnt = 0;

template <typename T>
void MySwap(T& a, T& b)
{
	T tmp(move(a));
	a = move(b);
	b = move(tmp);
}

int main(void)
{
	MyString str1("abc");
	MyString str2("def");
	cout << "str1: ";
	str1.Print();
	cout << "str2: ";
	str2.Print();
	cout << "===SWAP===\n";
	MySwap(str1, str2);
	cout << "str1: ";
	str1.Print();
	cout << "str2: ";
	str2.Print();
}