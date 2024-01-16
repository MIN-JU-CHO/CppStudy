#include <stdio.h>

// 비 멤버 함수이므로 const 반환 불가능
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

public:
	MyString();
	MyString(char c);						// 문자로 문자열 생성
	MyString(const char* origin);			// C 문자열로 문자열 생성
	MyString(const MyString& origin);		// 복사 생성
	~MyString();
	
	int GetLen() const;						// 문자열 길이 반환
	void Concat(const char* str);			// Concatenation
	int GetSubstr(const char* substr) const;// 문자열 내 포함된 문자열 반환
	bool IsEqual(const char* compare) const;// 문자열 같은지 비교
	int CmpSize(const char* compare) const;	// 문자열 크기 비교 (사전 순)

	void Concat(const MyString& str);			// Concatenation
	int GetSubstr(const MyString& substr) const;// 문자열 내 포함된 문자열 반환
	bool IsEqual(const MyString& compare) const;// 문자열 같은지 비교
	int CmpSize(const MyString& compare) const;	// 문자열 크기 비교 (사전 순)

	void PrintStr() const;					// print
	void PrintStr(int idx) const;			// print from idx
};

MyString::MyString() : len(0), data(nullptr) {}

MyString::MyString(char c)						// 문자로 문자열 생성
{
	len = 1;
	data = new char[len];	
	data[0] = c;
}

MyString::MyString(const char* origin)			// C 문자열로 문자열 생성
{
	len = GetStrLen(origin);
	data = new char[len];
	for (int i = 0;i < len; ++i)
	{
		data[i] = origin[i];
	}
}
MyString::MyString(const MyString& origin)		// 복사 생성
{
	len = origin.GetLen();
	data = new char[len];
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

void MyString::Concat(const char* str)			// Concatenation
{
	if (str == nullptr)
	{
		printf("Concat 비정상: nullptr\n");
		return;
	}
	if (str[0] == '\0')
	{
		printf("Concat 비정상: 붙일 문자열 존재 X\n");
		return;
	}
	int addlen = GetStrLen(str);
	char* temp = data;
	data = new char[len + addlen];
	for (int i = 0; i < len; ++i)
	{
		data[i] = temp[i];
	}
	for (int j = 0; j < addlen; ++j)
	{
		data[len + j] = str[j];
	}
	len += addlen;
	if (temp)
	{
		delete[] temp;
	}
}

int MyString::GetSubstr(const char* substr) const// 문자열 내 포함된 문자열 반환
{
	/*if (substr == nullptr)
	{
		printf("GetSubstr 비정상\n");
		return -1;
	}*/
	if (substr[0] == '\0')
	{
		printf("GetSubstr 비정상: 검색 문자열 존재 X\n");
		return -1;
	}
	int substrlen = GetStrLen(substr);
	int psubstr = -1;
	for (int i = 0; i < len; ++i)
	{
		if (data[i] != substr[0])
		{
			continue;
		}
		psubstr = i;
		for (int j = 0; j < substrlen; ++j)
		{
			if (i + j >= len)
			{
				return -1;
			}

			if (data[i + j] != substr[j])
			{
				psubstr = -1;
				break;
			}
		}
		if (psubstr != -1)
		{
			return psubstr;
		}
	}
	return -1;
}

bool MyString::IsEqual(const char* compare) const// 문자열 같은지 비교
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

int MyString::CmpSize(const char* compare) const// 문자열 크기 비교 (사전 순)
{
	for (int i = 0; i < len; ++i)
	{
		if (data[i] < compare[i])
		{
			return -1;
		}
		if (data[i] > compare[i])				// include (len > cplen)
		{
			return 1;							// bc \0: always minimum
		}
	}
	int cplen = GetStrLen(compare);
	if (len == cplen)
	{
		return 0;
	}
	return -1;
}

void MyString::Concat(const MyString& str)			// Concatenation
{
	int addlen = str.GetLen();
	if (addlen == 0)
	{
		return;
	}
	char* temp = data;
	data = new char[len + addlen];
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

int MyString::GetSubstr(const MyString& substr) const// 문자열 내 포함된 문자열 반환
{
	int substrlen = substr.GetLen();
	if (substrlen == 0)
	{
		return -1;
	}
	int psubstr = -1;
	for (int i = 0; i < len; ++i)
	{
		if (data[i] != substr.data[0])
		{
			continue;
		}
		psubstr = i;
		for (int j = 0; j < substrlen; ++j)
		{
			if (i + j >= len)
			{
				return -1;
			}

			if (data[i + j] != substr.data[j])
			{
				psubstr = -1;
				break;
			}
		}
		if (psubstr != -1)
		{
			return psubstr;
		}
	}
	return -1;
}
// MyString은 null문자가 없으므로 로직이 다름
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

int MyString::CmpSize(const MyString& compare) const// 문자열 크기 비교 (사전 순)
{
	for (int i = 0; i < len; ++i)
	{
		if (data[i] < compare.data[i])
		{
			return -1;
		}
		if (data[i] > compare.data[i])				// include (len > cplen)
		{
			return 1;								// bc \0: always minimum
		}
	}
	int cplen = compare.GetLen();
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
	s2.Concat(nullptr);
	s2.PrintStr();
	printf("GetLength: %d \n", s2.GetLen());
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
}