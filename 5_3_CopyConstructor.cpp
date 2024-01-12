#include <stdio.h>
#include <string.h>
class string
{
public:
	char* str;
	int len;

public:
	string(char c, int n);				// 문자 c가 n개 있는 문자열로 정의
	string(const char* s);
	string(const string& s);
	~string();

	void add_string(const string& s);	// str 뒤에 s 를 붙인다.
	void copy_string(const string& s);	// str 에 s 를 복사한다.
	int str_len();						// 문자열 길이 리턴
};

string::string(char c, int n)			// 문자 c가 n개 있는 문자열로 정의
{
	len = n;
	str = new char[len + 1];			// 끝 '\0' 문자 고려
	for (int i = 0; i < n; ++i)
	{
		str[i] = c;
	}
	str[n] = '\0';
}

string::string(const char* s)
{
	len = strlen(s);
	str = new char[len + 1];
	strcpy(str, s);
}

string::string(const string& s)			// 복사 생성자
{
	len = s.len;
	str = new char[len + 1];
	strcpy(str, s.str);
}

string::~string()
{
	if (str)
	{
		delete[] str;
	}
}

void string::add_string(const string& s)	// str 뒤에 s 를 붙인다.
{
	char* temp = str;
	str = new char[len + s.len + 1];
	strcpy(str, temp);
	strcpy(str + len, s.str);
	len = len + s.len;
	if (temp)
	{
		delete[] temp;
	}
}

void string::copy_string(const string& s)	// str 에 s 를 복사한다.
{
	if (str)
	{
		delete[] str;
	}
	len = s.len;
	str = new char[len + 1];
	strcpy(str, s.str);
}

int string::str_len()						// 문자열 길이 리턴
{
	return len;
}

int main() {
	// aaaaa
	string s1('a', 5);
	printf("s1: %s\n", s1.str);

	// Hello
	string s2("Hello");
	printf("s2: %s\n", s2.str);

	// aaaaaHello
	s1.add_string(s2);
	printf("s1 after add_string: %s\n", s1.str);

	// aaaaaHello
	string s3 = s1;
	printf("s3 (copied from s1): %s\n", s3.str);

	// Hello
	s3.copy_string(s2);
	printf("s3 after copy_string: %s\n", s3.str);

	// 5
	printf("Length of s3: %d\n", s3.str_len());

	return 0;
}