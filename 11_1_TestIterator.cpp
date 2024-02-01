#include<vector>
#include<list>
#include<deque>
#include<iostream>

using namespace std;
int main(void)
{
	vector<int> v(5, 0);
	v[0] = 1;
	v[1] = 2;
	v[2] = 3;
	// 1 2
	for (vector<int>::iterator iter = v.begin(); iter != v.end(); ++iter)
	{
		cout << *iter << endl;
		if (*iter == 2)
		{
			v.insert(iter, 3);
			break;
		}
	}
	cout << endl;
	// 1 3
	for (vector<int>::iterator iter = v.begin(); iter != v.end(); ++iter)
	{
		cout << *iter << endl;
		if (*iter == 3)
		{
			v.erase(iter);
			break;
		}
	}
	cout << endl;
	// vector<t>::size_type은 부호 없는 정수 이므로 -1이 아닌 max값으로 돌아간다.
	/*for (vector<int>::size_type i = v.size() - 1; i >= 0; --i)
	{
		cout << v[i] << endl;
	}*/
	// 0 0 3 2 1
	for (vector<int>::reverse_iterator iter = v.rbegin(); iter != v.rend(); ++iter)
	{
		cout << *iter << endl;
	}
	cout << endl;

	list <int> lst;
	lst.push_back(10);
	lst.push_back(20);
	lst.push_back(30);
	lst.push_back(40);
	// 10 20 30 40
	for (list<int>::iterator iter = lst.begin(); iter != lst.end(); ++iter)
	{
		if (*iter == 20)
		{
			lst.insert(iter, 50);
		}
		cout << *iter << endl;
	}
	cout << endl;
	// 10 50 20
	for (list<int>::iterator iter = lst.begin(); iter != lst.end(); ++iter)
	{
		if (*iter == 30)
		{
			lst.erase(iter);
			break;
		}
		cout << *iter << endl;
	}
	cout << endl;
	
	deque <int> deq;
	deq.push_back(100);
	deq.push_back(200);
	deq.push_back(300);
	deq.push_back(400);
	// 100 200
	for (deque<int>::iterator iter = deq.begin(); iter != deq.end(); ++iter)
	{
		cout << *iter << endl;
		if (*iter == 200)
		{
			deq.insert(iter, 500);
			break;
		}
	}
	cout << endl;
	// 100 500 200
	for (deque<int>::iterator iter = deq.begin(); iter != deq.end(); ++iter)
	{
		if (*iter == 300)
		{
			deq.erase(iter);
			break;
		}
		cout << *iter << endl;
	}
}