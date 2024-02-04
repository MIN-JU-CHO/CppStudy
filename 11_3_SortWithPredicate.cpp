#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template <typename Iter>
void print(Iter begin, Iter end)
{
	while (begin != end)
	{
		cout << *begin << " ";
		++begin;
	}
	cout << "\n";
}
// same as greater<T>() in header "functional"
template <typename T>
struct greater_cmp
{
	bool operator()(const T& a, const T& b) const
	{
		return a > b;
	}
};

int main(void)
{
	vector<int> arr = { 5, 3, 1, 6, 7, 4, 2 };
	print(arr.begin(), arr.end());
	sort(arr.begin(), arr.end(), greater_cmp<int>());
	print(arr.begin(), arr.end());
}