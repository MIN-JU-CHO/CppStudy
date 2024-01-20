#include <stdio.h>
#include <ctype.h>
int GetLen(const char* str)
{
	int i = -1;
	while (str[++i] != '\0') {};
	return i;
}

class Complex
{
	double real = 0;
	double img = 0;

	double GetReal(const char* str, int begin, int end) const;
public:
	Complex(double real, double img) : real(real), img(img) {};
	Complex(const Complex& cp) : real(cp.real), img(cp.img) {};

	Complex Plus(const Complex& p) const;
	Complex Plus(double preal, double pimg) const;
	Complex operator+(const Complex& p);
	Complex operator-(const Complex& p);
	Complex operator*(const Complex& p);
	Complex operator/(const Complex& p);
	Complex& operator=(const Complex& c);
	Complex& operator+=(const Complex& c);	// operator+ 사용
	Complex& operator-=(const Complex& c);	// operator- 사용
	Complex& operator*=(const Complex& c);	// operator* 사용
	Complex& operator/=(const Complex& c);	// operator/ 사용
	//Complex operator+(const char* str);	// 문자열 -> 복소수 생성자, operator+ 사용
	//Complex operator-(const char* str);	// 문자열 -> 복소수 생성자, operator- 사용
	//Complex operator*(const char* str);	// 문자열 -> 복소수 생성자, operator* 사용
	//Complex operator/(const char* str);	// 문자열 -> 복소수 생성자, operator/ 사용
	Complex(const char* str);	// 문자열 -> 복소수 생성자
	

	void Print() const;
};

Complex Complex::Plus(double preal, double pimg) const
{
	Complex temp(*this);
	temp.real += preal;
	temp.img += pimg;
	return temp;
}

Complex Complex::Plus(const Complex& p) const
{
	Complex temp(*this);
	temp.real += p.real;
	temp.img += p.img;
	return temp;
}
// const (Rvalue) 로 반환하면 타입 불일치로 연속 연산 불가능
// 매개변수로 받을 때 타입: const Complex& => 참조할 수 있는 non-const Lvalue여야 함
Complex Complex::operator+(const Complex& p)
{
	Complex temp(real + p.real, img + p.img);
	return temp;
}

Complex Complex::operator-(const Complex& p)
{
	Complex temp(real - p.real, img - p.img);
	return temp;
}

Complex Complex::operator*(const Complex& p)
{
	Complex temp(real * p.real - img * p.img, real * p.img + img * p.real);
	return temp;
}

Complex Complex::operator/(const Complex& p)
{
	Complex temp((real * p.real + img * p.img) / (p.real * p.real + p.img * p.img), 
		(p.real * img - real * p.img) / (p.real * p.real + p.img * p.img));
	return temp;
}
// 마찬가지로, non-const Lvalue여야 확장 참조 연산(ex 비교연산)도 가능하다.
// 깊은 복사가 필요한 멤버 변수가 없으므로, 선언이나 정의 없이 default 사용 가능
Complex& Complex::operator=(const Complex& c)
{
	real = c.real;
	img = c.img;
	return *this;
}

Complex& Complex::operator+=(const Complex& c)
{
	*this = *this + c;
	return *this;
}
Complex& Complex::operator-=(const Complex& c)
{
	*this = *this - c;
	return *this;
}
Complex& Complex::operator*=(const Complex& c)
{
	*this = *this * c;
	return *this;
}
Complex& Complex::operator/=(const Complex& c)
{
	*this = *this / c;
	return *this;
}

//Complex Complex::operator+(const char* str)
//{
//	Complex temp(str);
//	return *this + temp;
//}
//Complex Complex::operator-(const char* str)
//{
//	Complex temp(str);
//	return *this - temp;
//}
//Complex Complex::operator*(const char* str)
//{
//	Complex temp(str);
//	return *this * temp;
//}
//Complex Complex::operator/(const char* str)
//{
//	Complex temp(str);
//	return *this / temp;
//}

// 문자열 -> 복소수 생성자
Complex::Complex(const char* str)
{
	int begin = 0, len = GetLen(str);
	real = 0, img = 0;
	if (len == 0)
	{
		return;
	}
	int pos_i = -1;
	for (int i = 0; i < len; ++i)
	{
		if (str[i] == 'i')
		{
			pos_i = i;
			break;
		}
	}
	// i가 없을 때는 실수부만 처리
	if (pos_i == -1)
	{
		real = GetReal(str, begin, len - 1);
	}
	// i 전은 실수부, 후는 허수부로 처리, i 직전 부호값 처리
	else
	{
		real = GetReal(str, begin, pos_i - 1);
		img = GetReal(str, pos_i + 1, len - 1);
		if (pos_i >= 1 && str[pos_i - 1] == '-')
		{
			img *= -1;
		}
	}
}
// 문자열 -> 실수 읽기
double Complex::GetReal(const char* str, int begin, int end) const
{
	if (begin > end)
	{
		return 0;
	}
	bool minus = false;
	if (str[begin] == '-')
	{
		minus = true;
	}
	if (str[begin] == '-' || str[begin] == '+')
	{
		++begin;
	}
	bool is_int = true;
	double num = 0, decimal = 1;
	for (int i = begin; i <= end; ++i)
	{
		if (isdigit(str[i]) && is_int)
		{
			num *= 10;
			num += str[i] - '0';
		}
		// 첫 . 만 가능
		else if (str[i] == '.' && is_int)
		{
			is_int = false;
		}
		else if (isdigit(str[i]) && !is_int)
		{
			decimal /= 10;
			num += decimal * (str[i] - '0');
		}
		else
		{
			break;
		}
	}
	// 음수는 마지막에 처리해줘야 수 읽기의 덧셈 연산이 정상적으로 수행됨
	if (minus)
	{
		num *= -1;
	}
	return num;
}

void Complex::Print() const
{
	printf("(%f, %f)\n", real, img);
}

int main(void)
{
	Complex a(1, 2);
	Complex b(3, -2);
	Complex c(0, 0);
	c = a * b + a / b + a + b;
	c.Print();
	printf("\n");

	Complex a1 = b;	// Copy Constructor
	Complex a2(0, 0);
	a2 = b;	// Assignment Operator

	a += b;
	a.Print();
	b.Print();
	printf("\n");

	a = Complex(0, 0);
	a.Print();
	// "-1.1 + i3.9.23" 일 경우 img => 3.9
	a = a + "-1.1 + i3.923";
	a.Print();
	a = a - "1.2 -i1.823";
	a.Print();
	a = a * "2.3+i22";
	a.Print();
	a = a / "-12+i55";
	a.Print();
}