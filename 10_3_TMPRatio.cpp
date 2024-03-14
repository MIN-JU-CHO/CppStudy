#include <iostream>

template<int X, int Y>
struct GCD
{
	static const int value = GCD<Y, X% Y>::value;
};

template<int X>
struct GCD<X, 0>
{
	static const int value = X;
};

template<int N, int D = 1>
struct Ratio
{
private:
	const static int _gcd = GCD<N, D>::value;

public:
	//typedef Ratio<N / _gcd, D / _gcd> type;
	using type = Ratio<N / _gcd, D / _gcd>;
	static const int num = N / _gcd;
	static const int den = D / _gcd;
};

template<class R1, class R2>
struct _Ratio_add
{
	using type = Ratio<R1::num* R2::den + R2::num * R1::den, R1::den * R2::den>;
};

template<class R1, class R2>
struct Ratio_add : _Ratio_add<R1, R2>::type {};

template<class R1, class R2>
struct _Ratio_sub
{
	using type = Ratio<R1::num* R2::den - R2::num * R1::den, R1::den * R2::den>;
};

template<class R1, class R2>
struct Ratio_sub : _Ratio_sub<R1, R2>::type {};

template<class R1, class R2>
struct _Ratio_mul
{
	using type = Ratio<R1::num* R2::num, R1::den * R2::den>;
};

template<class R1, class R2>
struct Ratio_mul : _Ratio_mul<R1, R2>::type {};

template<class R1, class R2>
struct _Ratio_div
{
	using type = Ratio<R1::num* R2::den, R1::den * R2::num>;
};

template<class R1, class R2>
struct Ratio_div : _Ratio_div<R1, R2>::type {};


int main(void)
{
	/*typedef Ratio<2, 3> rat;
	typedef Ratio<3, 2> rat2;
	typedef Ratio_add<rat, rat2> rat3;*/
	using rat = Ratio<2, 3>;
	using rat2 = Ratio<3, 2>;
	using rat3 = Ratio_add<rat, rat2>;

	std::cout << "2/3 + 3/2 = " << rat3::num << "/" << rat3::den << "\n";

	using rat4 = Ratio_mul<rat3, rat>;
	std::cout << "13/6 * 2/3 = " << rat4::num << "/" << rat4::den << "\n";
}