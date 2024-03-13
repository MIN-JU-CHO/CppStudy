#include <iostream>

template<int N>
struct fibo
{
	static const int value = fibo<N - 1>::value + fibo<N - 2>::value;
};

template <>
struct fibo<2>
{
	static const int value = 1;
};

template <>
struct fibo<1>
{
	static const int value = 1;
};

int main(void)
{
	std::cout << fibo<7>::value << "\n";
}