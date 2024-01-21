#include <stdio.h>
#include <iostream>

class Int
{
	int data;
public:
	Int() : data(0) {};
	Int(int data) : data(data) {};
	Int(const Int& c) : data(c.data) {};
	
	operator int() const;
	Int& operator++();
	Int operator++(int);
	int get_data() const { return data; };
};

Int::operator int() const
{
	return data;
}

Int& Int::operator++()
{
	printf("전위 증감 연산자\n");
	++data;
	return *this;
}

Int Int::operator++(int)
{
	printf("후위 증감 연산자\n");
	Int temp(data);
	++data;
	std::cout << "temp: " << temp.get_data() << " origin: " << data << std::endl;
	return temp;
}

void Print(const Int& a)	// Int 와 Int& 모두 받을 수 있음
{
	printf("Int: %d\n", a.get_data());
}

int main(void)
{
	Int x(3);
	// x => [x.operator int()] => (int) 3
	int a = x + 4;
	printf("%d\n", a);

	x = a * 2 + x + 4;				// x.operator int()와 default operator=
	printf("%d\n", x);				// 여기서는 x.operator int() 작동 X
	std::cout << x << std::endl;	// 여기서는 x.operator int() 작동 O
	printf("\n");
	
	Int t(3);
	//Print(++t);
	std::cout << ++t << std::endl;
	//Print(t++);
	std::cout << t++ << std::endl;
	std::cout << t << std::endl;
}