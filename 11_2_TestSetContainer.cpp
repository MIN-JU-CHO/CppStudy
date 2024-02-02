#include<set>
#include <string>
#include<iostream>
#include <Windows.h>

template <typename T, typename C>
void print(const std::set<T, C> &s)
{
	std::cout << "[ ";
	for (typename std::set<T>::const_iterator iter = s.cbegin(); iter != s.cend(); ++iter)
	{
		std::cout << (*iter) << " ";
	}
	std::cout << "]\n";
}
template <typename T>
void answer_is_elem(const std::set<T>& s, T val)
{
	if (s.find(val) != s.end())
	{
		std::cout << "Yes\n";
	}
	else
	{
		std::cout << "No\n";
	}
}

class Todo
{
	int priority;
	std::string desc;
public:
	Todo(int _priority, std::string _desc):priority(_priority), desc(_desc){}
	//bool operator<(const Todo& td) const
	//{
	//	if (priority == td.priority)
	//	{
	//		return desc < td.desc;
	//	}
	//	// 숫자가 낮은 것이 중요도가 더 높기 때문
	//	return priority > td.priority;
	//}
	friend struct TodoCmp;
	friend std::ostream& operator<< (std::ostream& o, const Todo& td);
};
struct TodoCmp
{// 왜 ()연산자 일까?
	bool operator()(const Todo& a, const Todo& b) const
	{
		if (a.priority == b.priority)
		{
			return a.desc < b.desc;
		}
		return a.priority > b.priority;
	}
};
std::ostream& operator<< (std::ostream& o, const Todo& td)
{
	o << "[중요도: " << td.priority << "] " << td.desc << std::endl;
	return o;
}

void test_set()
{
	set<int> s;
	for (int i = 5; i >= 1; --i)
	{
		s.insert(i * 10);
	}
	print(s);
	cout << "Is 20 element of s?: ";
	answer_is_elem(s, 20);
	cout << "Is 25 element of s?: ";
	answer_is_elem(s, 25);

	set<Todo, TodoCmp>todos;
	todos.insert(Todo(1, "play basketball"));
	todos.insert(Todo(2, "do math assignment"));
	todos.insert(Todo(1, "programming project"));
	todos.insert(Todo(3, "meet friends"));
	todos.insert(Todo(2, "watch a movie"));
	print(todos);
	todos.erase(todos.find(Todo(2, "do math assignment")));
	print(todos);
}
using namespace std;

int main(void)
{
	SetConsoleOutputCP(CP_UTF8);
	test_set();
}