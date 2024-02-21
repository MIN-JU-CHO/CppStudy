#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

class MyString
{
	int size;
	int length;
	char* data;
public:
	MyString() : size(0), length(0), data(nullptr) { cout << "빈 문자열 생성\n"; }
	MyString(const char* str)
	{
		cout << "문자열 생성\n";
		size = length = strlen(str);
		data = new char[length];
		for (int i = 0; i < length; ++i)
		{
			data[i] = str[i];
		}
	}
	MyString(const MyString& str)
	{
		cout << "복사 생성 ";
		size = str.size;
		length = str.length;
		if (size < length)
		{
			size = length;
		}
		data = new char[size];
		cout << &data << ": ";
		for (int i = 0; i < length; ++i)
		{
			data[i] = str.data[i];
			cout << data[i];
		}
		cout << "\n";
	}
	MyString(MyString&& ref) noexcept
	{
		cout << "이동 생성 ";
		size = ref.size;
		length = ref.length;
		if (size < length)
		{
			size = length;
		}
		data = ref.data;
		cout << &ref.data << ": ";
		for (int i = 0; i < length; ++i)
		{
			cout << data[i];
		}
		cout << "\n";
		ref.data = nullptr;
	}
	~MyString()
	{
		if (data)
		{
			delete[] data;
		}
	}
	void PrintAddress()
	{
		cout << &data << ": ";
		for (int i = 0; i < length; ++i)
		{
			cout << data[i];
		}
		cout << "\n";
	}
};

int main(void)
{
	MyString s1("a"), s2("b"), s3("c");
	vector<MyString> vs;
	vs.resize(0);
	cout << "===첫번째 원소 추가===\n";
	vs.push_back(s1);
	cout << "--모든 원소 주소 출력--\n";
	for (int i = 0; i < vs.size(); ++i)
	{
		vs[i].PrintAddress();
	}
	cout << "===두번째 원소 추가===\n";
	vs.push_back(s2);
	cout << "--모든 원소 주소 출력--\n";
	for (int i = 0; i < vs.size(); ++i)
	{
		vs[i].PrintAddress();
	}
	cout << "===세번째 원소 추가===\n";
	vs.push_back(s3);
	cout << "--모든 원소 주소 출력--\n";
	for (int i = 0; i < vs.size(); ++i)
	{
		vs[i].PrintAddress();
	}
}