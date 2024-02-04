#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
template <typename Iter>
void print(Iter begin, Iter end)
{
	while (begin != end)
	{
		cout << "[" << *begin << "] ";
		++begin;
	}
	cout << "\n----------------------\n";
}

class User
{
	int age;
	string name;
public:
	User(string _nm, int _age) : name(_nm), age(_age) {}
	bool operator< (const User& user) const
	{
		return age < user.age;
	}

	friend ostream& operator<< (ostream& o, const User& user);
};

ostream& operator<< (ostream& o, const User& user)
{
	return o << user.name << ", " << user.age;
}

int main(void)
{
	vector<User> vec;
	for (int i = 0; i < 100; ++i)
	{
		string name = "";
		name.push_back('a' + i / 26);
		name.push_back('a' + i % 26);
		vec.push_back(User(name, static_cast<int>(rand() % 10)));
	}
	vector<User> vec2;
	vec2 = vec;
	print(vec.begin(), vec.end());
	sort(vec.begin(), vec.end());
	print(vec.begin(), vec.end());
	stable_sort(vec2.begin(), vec2.end());
	print(vec2.begin(), vec2.end());
}