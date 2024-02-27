#include <iostream>
#include <typeinfo>
using namespace std;

template <typename T, unsigned int N>
class Array
{
	T data[N];
public:
	Array(T(&arr)[N])
	{
		for (int i = 0; i < N; ++i)
		{
			data[i] = arr[i];
		}
	}

	T* getArray()
	{
		return data;
	}
	unsigned int size()
	{
		return N;
	}
	void print_all()
	{
		for (int i = 0; i < N; ++i)
		{
			cout << data[i] << ", ";
		}
		cout << "\n";
	}
};

template<int N>
struct Int
{
	static const int num = N;
};

template<typename T, typename U>
struct add
{
	typedef Int<T::num + U::num> result;
};

template<int N>
struct factorial
{
	static const int result = N * factorial<N - 1>::result;
};
template<>
struct factorial<1>
{
	static const int result = 1;
};

int main(void)
{
	// Basic concept
	int arr[3] = { 1, 2, 3 };
	Array<int, 3> arr_w(arr);
	arr_w.print_all();
	cout << (typeid(Array<int, 3>) != typeid(Array<int, 5>)) << "\n";

	cout << "===Template Meta Programming===\n";
	typedef Int<1> one;
	typedef Int<2> two;
	typedef add<one, two>::result three;
	cout << three::num << '\n';

	cout << "===Factorial(TMP)===\n";
	cout << "6! = " << factorial<6>::result << '\n';
}