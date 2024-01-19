#include <stdio.h>
#include <chrono>

int GetStrLen(const char* str)				// C 문자열 길이 반환
{
	int len = 0;
	while (str[len] != '\0')
	{
		++len;
	}
	return len;
}

class MyString
{
	int len = 0;
	char* data = nullptr;
	int mem_capacity = 0;

public:
	MyString();
	MyString(char c);						// 문자로 문자열 생성
	MyString(const char* origin);			// C 문자열로 생성
	MyString(const MyString& origin);		// copy constructor
	~MyString();

	int GetLen() const;							// return len
	int GetCapacity() const;					// return capacity
	void Reserve(int size);						// reallocation

	void PrintStr() const;					// print
	void PrintStr(int idx) const;			// print from idx
	char At(int idx) const;					// 범위 내 문자 반환

	bool IsEqual(const MyString& compare) const;// 문자열 같은지 비교
	bool IsEqual(const char* compare) const;
	int CmpSize(const MyString& compare) const;	// 문자열 사전 순 비교
	int CmpSize(const char* compare) const;
	bool operator==(MyString& compare) const;
};

MyString::MyString() : len(0), data(nullptr), mem_capacity(0) {}

MyString::MyString(char c)
{
	mem_capacity = len = 1;
	data = new char[1];
	data[0] = c;
}
MyString::MyString(const char* origin)
{
	mem_capacity = len = GetStrLen(origin);
	data = new char[len];
	for (int i = 0;i < len; ++i)
	{
		data[i] = origin[i];
	}
}
MyString::MyString(const MyString& origin)
{
	len = origin.GetLen();
	mem_capacity = origin.GetCapacity();
	if (mem_capacity < len)
	{
		mem_capacity = len;
	}
	data = new char[mem_capacity];
	for (int i = 0; i < len; ++i)
	{
		data[i] = origin.data[i];
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
	return len;
}

int MyString::GetCapacity() const
{
	return mem_capacity;
}

void MyString::Reserve(int size)
{
	if (size <= mem_capacity)
	{
		return;
	}
	mem_capacity = size;
	char* temp = data;
	data = new char[mem_capacity];
	for (int i = 0; i < len; ++i)
	{
		data[i] = temp[i];
	}
	if (temp)
	{
		delete[] temp;
	}
}

void MyString::PrintStr() const
{
	for (int i = 0; i < len; ++i)
	{
		printf("%c", data[i]);
	}
	printf("\n");
}
void MyString::PrintStr(int idx) const
{
	if (idx < 0 || idx >= len)
	{
		return;
	}
	for (int i = idx; i < len; ++i)
	{
		printf("%c", data[i]);
	}
	printf("\n");
}

char MyString::At(int idx) const
{
	if (idx < 0 || idx >= len)
	{
		return NULL;
	}
	return data[idx];
}

bool MyString::IsEqual(const MyString& compare) const// 문자열 같은지 비교
{
	if (compare.GetLen() != len)
	{
		return false;
	}
	for (int i = 0; i < len; ++i)
	{
		if (data[i] != compare.data[i])
		{
			return false;
		}
	}
	return true;
}
bool MyString::IsEqual(const char* compare) const
{
	for (int i = 0; i < len; ++i)
	{
		if ((compare[i] == '\0' && len != 0) || data[i] != compare[i])
		{
			return false;
		}
	}
	if (compare[len] != '\0')
	{
		return false;
	}
	return true;
}

int MyString::CmpSize(const MyString& compare) const// 문자열 사전순 비교
{
	int cplen = compare.GetLen();
	int minlen;
	if (cplen < len)
	{
		minlen = cplen;
	}
	else
	{
		minlen = len;
	}
	for (int i = 0; i < minlen; ++i)
	{
		if (data[i] < compare.data[i])
		{
			return -1;
		}
		if (data[i] > compare.data[i])
		{
			return 1;
		}
	}
	if (len == cplen)
	{
		return 0;
	}
	else if (len < cplen)
	{
		return -1;
	}
	return 1;
}
int MyString::CmpSize(const char* compare) const
{
	for (int i = 0; i < len; ++i)
	{
		if (data[i] < compare[i])
		{
			return -1;
		}
		if (data[i] > compare[i])
		{
			return 1;
		}
	}
	int cplen = GetStrLen(compare);
	if (len == cplen)
	{
		return 0;
	}
	return -1;
}

bool MyString::operator==(MyString& compare) const
{	// little performance difference
	return IsEqual(compare);	// or return !CmpSize(compare);
}

int main(void)
{
	MyString s1("a word");
	MyString s2("sentence");
	MyString s3("sentence");

	if (s1 == s2)
	{
		printf("s1 == s2\n");
	}
	else
	{
		printf("s1 != s2\n");
	}

	if (s2 == s3)
	{
		printf("s2 == s3\n");
	}
	else
	{
		printf("s2 != s3\n");
	}

	// Performance: IsEqual vs CmpSize 
	MyString str1("Hello, world!");
	MyString str2("Hello, world!");

	// IsEqual()
	auto start = std::chrono::high_resolution_clock::now();
	bool result = str1 == str2;
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed_time = end - start;
	printf("IsEqual() elapsed time: %f seconds\n", elapsed_time.count());

	// CmpSize()
	start = std::chrono::high_resolution_clock::now();
	result = str1.CmpSize(str2) == 0;
	end = std::chrono::high_resolution_clock::now();
	elapsed_time = end - start;
	printf("CmpSize() elapsed time: %f seconds\n", elapsed_time.count());
}