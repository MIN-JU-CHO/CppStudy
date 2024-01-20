#include <stdio.h>

// 비 멤버 함수이므로 const 반환 불가능
int GetStrLen(const char* str)				// C 문자열 길이 반환
{
	int len = -1;
	while (str[++len] != '\0') {}
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
	MyString(const char* origin);			// C 문자열로 문자열 생성
	MyString(const MyString& origin);		// 복사 생성
	~MyString();
	
	int GetLen() const;							// 문자열 길이 반환

	void Concat(const MyString& str);			// Concatenation
	void Concat(const char* str);

	int GetSubstr(int find_from, const MyString& substr) const;// 문자열 내 포함된 문자열 반환
	int GetSubstr(int find_from, const char* substr) const;
	int GetSubstr(const MyString& substr) const;
	int GetSubstr(const char* substr) const;

	bool IsEqual(const MyString& compare) const;// 문자열 같은지 비교
	bool IsEqual(const char* compare) const;

	int CmpSize(const MyString& compare) const;	// 문자열 크기 비교 (사전 순)
	int CmpSize(const char* compare) const;

	void PrintStr() const;					// print
	void PrintStr(int idx) const;			// print from idx
	char At(int idx) const;					// 범위 내의 문자 반환

	int GetCapacity() const;				// 할당된 메모리 크기
	void Reserve(int size);					// 메모리 크기 재할당
	
	MyString& Assign(const MyString& origin);		// 대입
	MyString& Assign(const char* origin);	// void로 구현해도 잘됨

	MyString& Insert(int loc, const MyString& str);	// 삽입
	MyString& Insert(int loc, const char* str);
	MyString& Insert(int loc, char c);
	MyString& Erase(int loc, int num);

	MyString operator+(const MyString& str);
	bool operator==(const MyString& str) const;
	char& operator[](const int idx) const;
	MyString& operator=(const MyString& str);
	MyString& operator=(const char c);
};

MyString::MyString() : len(0), data(nullptr), mem_capacity(0) {}

MyString::MyString(char c)						// 문자로 문자열 생성
{
	mem_capacity = len = 1;
	data = new char[1];
	data[0] = c;
}

MyString::MyString(const char* origin)			// C 문자열로 문자열 생성
{
	mem_capacity = len = GetStrLen(origin);
	data = new char[len];
	for (int i = 0;i < len; ++i)
	{
		data[i] = origin[i];
	}
}
MyString::MyString(const MyString& origin)		// 복사 생성
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

int MyString::GetLen() const					// 문자열 길이 반환
{
	return len;
}


void MyString::Concat(const MyString& str)			// Concatenation
{
	int addlen = str.GetLen();
	if (addlen == 0)
	{
		return;
	}
	mem_capacity = len + addlen;
	char* temp = data;
	data = new char[mem_capacity];
	for (int i = 0; i < len; ++i)
	{
		data[i] = temp[i];
	}
	for (int j = 0; j < addlen; ++j)
	{
		data[len + j] = str.data[j];
	}
	len += addlen;
	if (temp)
	{
		delete[] temp;
	}
}

void MyString::Concat(const char* str)
{
	MyString temp(str);
	Concat(temp);
}

int MyString::GetSubstr(int find_from, const MyString& substr) const// 문자열 내 포함된 문자열 반환
{
	int substrlen = substr.GetLen();
	if (substrlen == 0 || find_from < 0 || find_from >= len)
	{
		return -1;
	}
	int psubstr = -1;
	for (int i = find_from; i + substrlen - 1 < len; ++i)
	{
		if (data[i] != substr.data[0])
		{
			continue;
		}
		int j = 0;
		for (; j < substrlen; ++j)
		{
			if (data[i + j] != substr.data[j])
			{
				break;
			}
		}
		if (j == substrlen)
		{
			return i;
		}
	}
	return -1;
}

int MyString::GetSubstr(int find_from, const char* substr) const
{
	MyString temp(substr);
	return GetSubstr(find_from, temp);
}

int MyString::GetSubstr(const MyString& substr) const
{
	return GetSubstr(0, substr);
}

int MyString::GetSubstr(const char* substr) const
{
	return GetSubstr(0, substr);
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
	MyString temp(compare);
	return IsEqual(temp);
}


int MyString::CmpSize(const MyString& compare) const// 문자열 크기 비교 (사전 순)
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
		if (data[i] > compare[i])				// include (len > cplen)
		{
			return 1;								// bc \0: always minimum
		}
	}
	int cplen = GetStrLen(compare);
	if (len == cplen)
	{
		return 0;
	}
	return -1;
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

char MyString::At(int idx) const					// 범위 내의 문자 반환
{
	if (idx < 0 || idx >= len)
	{
		return NULL;
	}
	return data[idx];
}

int MyString::GetCapacity() const				// 할당된 메모리 크기
{
	return mem_capacity;
}

void MyString::Reserve(int size)					// 메모리 크기 재할당
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

MyString& MyString::Assign(const MyString& origin)		// 대입
{
	len = origin.GetLen();
	if (mem_capacity < len)
	{
		mem_capacity = len;
		delete[] data;
		data = new char[mem_capacity];
	}
	for (int i = 0; i < len; ++i)
	{
		data[i] = origin.data[i];
	}
	return *this;
}

MyString& MyString::Assign(const char* origin)
{
	MyString temp(origin);
	return Assign(temp);
}



MyString& MyString::Insert(int loc, const MyString& str)
{
	if (loc < 0 || loc >= len)
	{
		return *this;
	}
	int strgetlen = str.GetLen();
	if (len + strgetlen > mem_capacity)
	{
		if (mem_capacity * 2 > len + strgetlen)
		{
			mem_capacity *= 2;
		}
		else
		{
			mem_capacity = len + strgetlen;
		}
		char* temp = data;
		data = new char[mem_capacity];
		int i = 0;
		for (; i < loc; ++i)
		{
			data[i] = temp[i];
		}
		for (int j = 0; j < strgetlen; ++j)
		{
			data[i + j] = str.data[j];
		}
		for (; i < len; ++i)
		{
			data[strgetlen + i] = temp[i];
		}
		delete[] temp;
		len += strgetlen;
		return *this;
	}
	// update 이전 값 소실 방지를 위해 뒤부터
	for (int i = len - 1; i >= loc; --i)
	{
		data[strgetlen + i] = data[i];
	}
	for (int i = 0; i < strgetlen; ++i)
	{
		data[loc + i] = str.data[i];
	}
	len += strgetlen;
	return *this;
}
MyString& MyString::Insert(int loc, const char* str)
{
	MyString temp(str);
	return Insert(loc, temp);
}

MyString& MyString::Insert(int loc, char c)
{
	MyString temp(c);
	return Insert(loc, temp);
}

MyString& MyString::Erase(int loc, int num)
{
	if (loc < 0 || loc >= len || num < 0 || loc + num - 1 >= len)
	{
		return *this;
	}
	for (int i = 0;loc + num + i < len; ++i)
	{
		data[loc + i] = data[loc + num + i];
	}
	len -= num;
	return *this;
}

MyString MyString::operator+(const MyString& str)
{
	Concat(str);
	return *this;
}
bool MyString::operator==(const MyString& str) const
{
	return IsEqual(str);
}
// 해당 위치의 문자 참조를 반환 -> 해당 문자 접근&수정 가능
char& MyString::operator[](const int idx) const
{
	if (idx < 0 || idx >= len)
	{
		static char empty = '\0';
		return empty;
	}
	return data[idx];
}

MyString& MyString::operator=(const MyString& str)
{
	Assign(str);
	return *this;
}

MyString& MyString::operator=(const char c)
{
	MyString temp(c);
	*this = temp;
	return *this;
}

int main(void)
{
	// 빈 문자열 생성 // \n // 0
	MyString nullstr = MyString();
	nullstr.PrintStr();
	printf("GetLength: %d \n", nullstr.GetLen());
	printf("*********************************\n");

	// 문자로 문자열 생성 // a // 1
	MyString s0 = MyString('a');
	s0.PrintStr();
	printf("GetLength: %d \n", s0.GetLen());
	printf("*********************************\n");

	// C 문자열로 문자열 생성 // abcde // 5
	MyString s1 = MyString("abcde");
	s1.PrintStr();
	printf("GetLength: %d \n", s1.GetLen());
	printf("*********************************\n");

	// 복사 생성 // abcde // 5
	MyString s2 = MyString(s1);
	s2.PrintStr();
	printf("GetLength: %d \n", s2.GetLen());
	printf("*********************************\n");

	// Concatenation // abcdef // 6
	s2.Concat("f");
	s2.PrintStr();
	printf("GetLength: %d \n", s2.GetLen());
	// 비정상: 붙일 문자열 존재 X // abcdef // 6
	s2.Concat("");
	s2.PrintStr();
	printf("GetLength: %d \n", s2.GetLen());
	// 비정상: nullptr // abcdef // 6
	//s2.Concat(nullptr);
	//s2.PrintStr();
	//printf("GetLength: %d \n", s2.GetLen());
	// aabcdef // 7
	s0.Concat(s2);
	s0.PrintStr();
	printf("GetLength: %d \n", s0.GetLen());
	// aabcdef // 7
	s0.Concat(nullstr);
	s0.PrintStr();
	printf("GetLength: %d \n", s0.GetLen());
	printf("*********************************\n");

	// 문자열 내 포함된 문자열 반환 // cde // 2
	int idxSubstr = s1.GetSubstr("cd");
	s1.PrintStr(idxSubstr);
	printf("substridx: %d\n", idxSubstr);
	// -1
	idxSubstr = s1.GetSubstr("dc");
	s1.PrintStr(idxSubstr);
	printf("substridx: %d\n", idxSubstr);
	// 비정상: 검색 문자열 존재 X // -1
	idxSubstr = s1.GetSubstr("");
	s1.PrintStr(idxSubstr);
	printf("substridx: %d\n", idxSubstr);
	// s1 ⊂ s2 // abcdef // 0
	idxSubstr = s2.GetSubstr(s1);
	s2.PrintStr(idxSubstr);
	printf("substridx: %d\n", idxSubstr);
	// s1 ⊂ s0 // abcdef // 1
	idxSubstr = s0.GetSubstr(s1);
	s0.PrintStr(idxSubstr);
	printf("substridx: %d\n", idxSubstr);
	// NULL ⊂ s0 // -1
	// 이슈: len을 반환하게 하면 공집합도 집합의 부분집합임을 표현할 수 있는가?
	idxSubstr = s0.GetSubstr(nullstr);
	s0.PrintStr(idxSubstr);
	printf("substridx: %d\n", idxSubstr);
	printf("*********************************\n");

	// 문자열 같은지 비교 // 0 // 0 // 1 // 0 // 1 // 0
	printf("%d ", s1.IsEqual("abcdef"));
	printf("%d ", s2.IsEqual("abcde"));
	printf("%d ", s1.IsEqual("abcde"));
	printf("%d ", s1.IsEqual(""));
	printf("%d ", nullstr.IsEqual(""));
	printf("%d ", nullstr.IsEqual("abcde"));
	printf("\n-----\n");
	// 0 // 0 // 1 // 0 // 1 // 0
	printf("%d ", s1.IsEqual(s2));
	printf("%d ", s2.IsEqual(s1));
	printf("%d ", s1.IsEqual(s1));
	printf("%d ", s1.IsEqual(nullstr));
	printf("%d ", nullstr.IsEqual(nullstr));
	printf("%d ", nullstr.IsEqual(s1));
	printf("\n*********************************\n");
	
	// 문자열 크기 비교 (사전 순)
	// -1 // 1 // -1 // 1 // -1 // 1 // 0 // 1 // -1 // 0
	MyString s3 = MyString("bbcde");
	printf("%d\n", s1.CmpSize("abcdef"));
	printf("%d\n", s2.CmpSize("abcde"));
	printf("%d\n", s1.CmpSize("bbcde"));
	printf("%d\n", s3.CmpSize("abcde"));
	printf("%d\n", s2.CmpSize("bbcde"));
	printf("%d\n", s3.CmpSize("abcdef"));
	printf("%d\n", s1.CmpSize("abcde"));
	printf("%d\n", s1.CmpSize(""));
	printf("%d\n", nullstr.CmpSize("abcde"));
	printf("%d\n", nullstr.CmpSize(""));
	printf("-----\n");
	// -1 // 1 // -1 // 1 // -1 // 1 // 0 // 1 // -1 // 0
	printf("%d\n", s1.CmpSize(s2));
	printf("%d\n", s2.CmpSize(s1));
	printf("%d\n", s1.CmpSize(s3));
	printf("%d\n", s3.CmpSize(s1));
	printf("%d\n", s2.CmpSize(s3));
	printf("%d\n", s3.CmpSize(s2));
	printf("%d\n", s1.CmpSize(s1));
	printf("%d\n", s1.CmpSize(""));
	printf("%d\n", nullstr.CmpSize(s1));
	printf("%d\n", nullstr.CmpSize(nullstr));
	printf("*********************************\n");

	MyString str1("very very very long string");
	str1.Reserve(30);
	printf("Capacity: %d\tLength: %d\n", str1.GetCapacity(), str1.GetLen());
	str1.PrintStr();
	MyString str2 = MyString();
	printf("Capacity: %d\tLength: %d\n", str2.GetCapacity(), str2.GetLen());
	str2.PrintStr();
	str2.Assign(str1);
	printf("Capacity: %d\tLength: %d\n", str2.GetCapacity(), str2.GetLen());
	str2.PrintStr();
	str1.Assign("");
	printf("Capacity: %d\tLength: %d\n", str1.GetCapacity(), str1.GetLen());
	str1.PrintStr();
	str1.Assign(str2);
	printf("Capacity: %d\tLength: %d\n", str1.GetCapacity(), str1.GetLen());
	str1.PrintStr();
	printf("*********************************\n");

	s1.PrintStr();
	printf("Capacity: %d\tLength: %d\n", s1.GetCapacity(), s1.GetLen());
	s2.PrintStr();
	printf("Capacity: %d\tLength: %d\n", s2.GetCapacity(), s2.GetLen());
	printf("%c\n",s1.At(2));
	s1.Insert(2, s2).PrintStr();
	printf("Capacity: %d\tLength: %d\n", s1.GetCapacity(), s1.GetLen());
	printf("%c\n", s2.At(2));
	s2.Insert(2, "a");
	s2.PrintStr();
	printf("Capacity: %d\tLength: %d\n", s2.GetCapacity(), s2.GetLen());
	s2.Insert(2, 'A');
	s2.PrintStr();
	printf("Capacity: %d\tLength: %d\n", s2.GetCapacity(), s2.GetLen());
	printf("*********************************\n");

	s1.PrintStr();
	s1.Erase(2, 6).PrintStr();
	printf("Capacity: %d\tLength: %d\n", s1.GetCapacity(), s1.GetLen());

	MyString te("abcabcd");
	MyString tee("bcd");
	printf("%d\n", te.GetSubstr(0, tee));
	printf("*********************************\n");

	MyString test1("xxxxxxx"), test2("Taeyeon"), test3("xxxxxxx");
	printf("%d\n", test1 == test2);
	printf("%d\n", test1 == test3);
	test3 = test3 + test1;
	test3.PrintStr();
	test1[1] = 'T';
	test1.PrintStr();
}