#include<map>
#include<string>
#include<iostream>
#include<Windows.h>
using namespace std;
template<typename K, typename V>
void print(const map<K, V>& m1)
{
	for (typename map<K, V>::const_iterator iter = m1.cbegin(); iter != m1.cend(); ++iter)
	{
		//cout << iter->first << "\t" << iter->second << endl;
	}
	for (const pair<K, V>& kv : m1)
	{
		cout << kv.first << "\t" << kv.second << endl;
	}
}
template<typename K, typename V>
void search_print(const map<K, V>& m1, const K& key)
{
	auto iter = m1.find(key);
	if (iter != m1.end())
	{
		cout << key << "--> " << iter->second << "\n";
	}
	else
	{
		cout << key << "은(는) 목록에 없습니다.\n";
	}
}

void test_map()
{
	map<string, double> pitcher_list;
	pitcher_list.insert(pair<string, double>("박세웅", 2.23));
	pitcher_list.insert(pair<string, double>("해커", 2.93));
	pitcher_list.insert(pair<string, double>("피어밴드", 2.95));

	pitcher_list.insert(make_pair("차우찬", 3.04));
	pitcher_list.insert(make_pair("장원준", 3.05));
	pitcher_list.insert(make_pair("헥터", 3.09));

	pitcher_list["니퍼트"] = 3.56;
	pitcher_list["박종훈"] = 3.76;
	pitcher_list["켈리"] = 3.90;
	pitcher_list["오승환"] = 3.58;
	print(pitcher_list);
	search_print(pitcher_list, string("오승환"));
	search_print(pitcher_list, string("류현진"));
}

template <typename K, typename V>
void print(const multimap<K, V>& mm)
{
	for (const pair<K, V> p : mm)
	{
		cout << p.first << " " << p.second << endl;
	}
}

void test_multimap()
{
	multimap<int, string> mm;
	mm.insert(make_pair(1, "hello"));
	mm.insert(make_pair(1, "hi"));
	mm.insert(make_pair(1, "ahihi"));
	mm.insert(make_pair(2, "bye"));
	//mm.insert(make_pair(2, "baba"));
	print(mm);
	pair<multimap<int, string>::iterator, multimap<int, string>::iterator> range = mm.equal_range(1);
	for (auto equal_iter = range.first; equal_iter != range.second; ++equal_iter)
	{
		cout << equal_iter->first << " : " << equal_iter->second << endl;
	}
	auto range2 = mm.equal_range(3);
	for (auto equal_iter = range2.first; ; ++equal_iter)
	{
		// 무효한 반복자이므로 역참조 불가능
		//cout << equal_iter->first << " : " << equal_iter->second << endl;
		if (equal_iter == range2.second)
		{
			cout << "empty\n";
			break;
		}
	}
	auto range3 = mm.equal_range(2);
	for (auto equal_iter = range3.first; equal_iter != range3.second; ++equal_iter)
	{
		cout << equal_iter->first << " : " << equal_iter->second << endl;
	}
}

int main(void)
{
	SetConsoleOutputCP(CP_UTF8);
	//test_map();
	test_multimap();
}