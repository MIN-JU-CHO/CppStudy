#include <functional>
#include<unordered_set>
#include<string>
#include<iostream>
using namespace std;
template<typename T>
void print(const unordered_set<T>& us)
{
	cout << "-----------" << "\n";
	for (const T& elem : us)
	{
		cout << elem << "\n";
	}
	cout << "-----------" << "\n";
}
template<typename T>
void has_element(const unordered_set<T>& us, const T val)
{
	if (us.find(val) != us.end())
	{
		cout << val << " 가 존재\n";
		return;
	}
	cout << val << " 가 없다\n";
}
void test_default_uset()
{
	unordered_set<string> s;
	s.insert("hi");
	s.insert("my");
	s.insert("name");
	s.insert("is");
	s.insert("cmj");
	s.insert("welcome");
	s.insert("to");
	s.insert("c++");
	print(s);
	has_element(s, string("c++"));
	has_element(s, string("c"));
	string hi = "hi";
	cout << "'" << hi << "' 를 삭제\n";
	s.erase(s.find(hi));
	has_element(s, hi);
	hi = "ho";
	has_element(s, hi);
	// 무효화 된 iterator라서 erase 시 오류 발생
	//s.erase(s.find(hi));
}
class Todo
{
	int priority;
	string desc;
public:
	Todo(int _p, string _str) : priority(_p), desc(_str) {}
	bool operator==(const Todo& cmp) const
	{
		if (cmp.desc == desc && cmp.priority == priority)
		{
			return true;
		}
		return false;
	}
	friend ostream& operator<< (ostream& o, const Todo& td);
	friend struct hash<Todo>;
};
namespace std
{
	template <>
	struct hash<Todo>
	{
		size_t operator()(const Todo& t) const
		{
			hash<string> hash_func;
			return t.priority ^ (hash_func(t.desc));
		}
	};

}
ostream& operator<< (ostream& o, const Todo& td)
{
	return o << "[중요도 : " << td.priority << "] " << td.desc;
}

void test_class_uset()
{
	unordered_set<Todo> todos;
	todos.insert(Todo(1, "농구 하기"));
	todos.insert(Todo(2, "수학 숙제 하기"));
	todos.insert(Todo(1, "프로그래밍 프로젝트"));
	todos.insert(Todo(3, "친구 만나기"));
	todos.insert(Todo(1, "영화 보기"));
	print(todos);
	has_element(todos, Todo(1, "영화 보기"));
	has_element(todos, Todo(2, "영화 보기"));
}

int main(void)
{
	// test_default_uset();
	test_class_uset();
}