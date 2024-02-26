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

// Before C++17
template<typename T>
T sum_all()
{
	return 0;
}

template <typename T, typename... Ints>
T sum_all(T num, Ints... elems)
{
	return num + sum_all<T>(elems...);
}

template<typename T, typename... Ints>
double average(Ints... elems)
{
	return static_cast<double> (sum_all<T>(elems...)) / sizeof...(elems);
}

/*
// After C++ 17 -> FOLD
template<typename T, typename... Ints>
T sum_all(Ints... elems)
{
	return (... + elems);
}

template<typename T, typename... Ints>
double average(Ints... elems)
{
	return static_cast<double> (sum_all<T>(elems...)) / sizeof...(elems);
}

template<typename Int, typename... Ints>
Int diff_from(Int start, Ints... elems)
{
	return (start - ... - elems);
}

class A
{
public:
	void do_something(int x)
	{
		cout << "Do something with " << x << "\n";
	}
};

template <typename T, typename... Ints>
void do_many_things(const T& obj, Ints... nums)
{
	(obj.do_something(nums), ...);
}
*/

int main(void)
{
	string word = "this";
	cout << StrConcat(word, " ", "is", " ", "a", " ", "sentence", "\n");
	//cout << sum_all<int>(1, 4, 2, 3, 10) << "\n";
	//cout << average<int>(1, 4, 2, 3, 10) << "\n";
	//cout << diff_from(100, 1, 4, 2, 3, 10) << "\n";
	cout << average<int>(1, 4, 2, 3, 10) << "\n";

	/*A a;
	do_many_things(a, 1, 3, 2, 4);*/
}