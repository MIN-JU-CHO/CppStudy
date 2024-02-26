#include <string>
#include <iostream>
#include <stdlib.h>
using namespace std;

size_t GetLen(const string& str)
{
	return str.size();
}

size_t GetLen(const char* str)
{
	return strlen(str);
}

template<typename String, typename... Strings>
size_t GetLen(const String& str, Strings... strs)
{
	return GetLen(str) + GetLen(strs...);
}

void Append(string* str)
{
	return;
}

template<typename String, typename... Strings>
void Append(string* origin, const String& str, Strings... strs)
{
	origin->append(str);
	Append(origin, strs...);
}

template<typename String, typename... Strings>
string StrConcat(const String& str, Strings... strs)
{
	size_t length = GetLen(str, strs...);
	cout << "Length: " << length << "\n";
	string result;
	result.resize(length);
	result = str;
	Append(&result, strs...);
	return result;
}

int main(void)
{
	string word = "this";
	cout << StrConcat(word, " ", "is", " ", "a", " ", "sentence", "\n");
}