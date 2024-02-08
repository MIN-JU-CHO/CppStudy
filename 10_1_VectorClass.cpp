#include <iostream>
#include <string>
// variable length and sequece array (without RandomAccessIterator version)
template<typename T>
class Vector
{
	T* data;
	int capacity;
	int length;
public:
	// constructor, deconstructor
	Vector(int _cap = 1) : capacity(_cap), length(0), data(new T[_cap]) {}
	Vector(int _cap, T _val) : capacity(_cap), length(_cap), data(new T[_cap])
	{
		for (int i = 0; i < length; ++i)
		{
			data[i] = _val;
		}
	}
	~Vector()
	{
		if (data)
		{
			delete[] data;
		}
	}
	// push_back, pop_back
	void push_back(T elem)
	{
		if (capacity <= length)
		{
			resize(capacity * 2);
		}
		data[length] = elem;
		++length;
	}
	T pop_back()
	{
		--length;
		return data[length];
	}
	// resize
	void resize(int new_size)
	{
		if (new_size < length)
		{
			return;
		}
		T* temp = data;
		capacity = new_size;
		data = new T[capacity];
		for (int i = 0; i < length; ++i)
		{
			data[i] = temp[i];
		}
		delete[] temp;
	}
	// []
	T operator[] (int idx)
	{
		return data[idx];
	}
	// at
	void* at(int idx)
	{
		if (idx < 0 || idx >= length)
		{
			return nullptr;
		}
		return &data[idx];
	}
	// insert
	void insert(int idx, T val)
	{
		if (capacity <= length)
		{
			resize(capacity * 2);
		}
		for (int i = length - 1; i >= idx; --i)
		{
			data[i + 1] = data[i];
		}
		data[idx] = val;
		++length;
	}
	// remove
	void remove(int idx)
	{
		for (int i = idx + 1; i < length; ++i)
		{
			data[i - 1] = data[i];
		}
		--length;
	}
	// size
	int size()
	{
		return length;
	}
	int alloc_size()
	{
		return capacity;
	}
};

template<>
class Vector<bool>
{
	unsigned int* data;
	int capacity;
	int length;
public:
	typedef bool value_type;
	// constructor, deconstructor
	Vector(int n = 1) : capacity(n / 32 + 1), length(0), data(new unsigned int[n / 32 + 1])
	{
		for (int i = 0; i < capacity; ++i)
		{
			data[i] = 0;
		}
	}
	Vector(int n, bool _val) : capacity(n / 32 + 1), length(n), data(new unsigned int[n / 32 + 1])
	{
		unsigned int val = _val == true ? 0xFFFFFFFF : 0;
		for (int i = 0; i < capacity; ++i)
		{
			data[i] = val;
		}
	}
	~Vector()
	{
		if (data)
		{
			delete[] data;
		}
	}
	// push_back, pop_back
	void push_back(bool elem)
	{
		if (capacity * 32 <= length)
		{
			resize(capacity * 2);
		}
		if (elem)
		{
			data[length / 32] |= (1 << (length % 32));
		}
		++length;
	}
	bool pop_back()
	{
		--length;
		return (data[length / 32] & (1 << (length % 32))) != 0;
	}
	// resize
	void resize(int new_size)
	{
		if (new_size < length)
		{
			return;
		}
		unsigned int* temp = data;
		data = new unsigned int[new_size];
		for (int i = 0; i < capacity; ++i)
		{
			data[i] = temp[i];
		}
		for (int i = capacity; i < new_size; ++i)
		{
			data[i] = 0;
		}
		capacity = new_size;
		delete[] temp;
	}
	// []
	bool operator[] (int idx)
	{
		return (data[idx / 32] & (1 << (idx % 32))) != 0;
	}
	// at
	void* at(int idx)
	{
		if (idx < 0 || idx >= length)
		{
			return nullptr;
		}
		bool temp;
		temp = (data[idx / 32] & (1 << (idx % 32))) != 0;
		return &temp;
	}
	// insert
	void insert(int idx, bool val)
	{
		if (capacity <= length)
		{
			resize(capacity * 2);
		}
		for (int i = length - 1; i >= idx; --i)
		{
			int nxt = i + 1, cur = i;
			if (data[cur / 32] & (1 << (cur % 32)))
			{
				data[nxt / 32] |= (1 << (nxt % 32));
			}
			else
			{
				unsigned int all_one_except_nxt = 0xFFFFFFFF;
				all_one_except_nxt ^= (1 << (nxt % 32));
				data[nxt / 32] &= all_one_except_nxt;
			}
		}
		if (val)
		{
			data[idx / 32] |= (1 << (idx % 32));
		}
		else
		{
			unsigned int all_one_except_idx = 0xFFFFFFFF;
			all_one_except_idx ^= (1 << (idx % 32));
			data[idx / 32] &= all_one_except_idx;
		}
		++length;
	}
	// remove
	void remove(int idx)
	{
		for (int i = idx + 1; i < length; ++i)
		{
			int prev = i - 1, cur = i;
			if (data[cur / 32] & (1 << (cur % 32)))
			{
				data[prev / 32] |= (1 << (prev % 32));
			}
			else
			{
				unsigned int all_one_except_prev = 0xFFFFFFFF;
				all_one_except_prev ^= (1 << (prev % 32));
				data[prev / 32] &= all_one_except_prev;
			}
		}
		--length;
	}
	// size
	int size()
	{
		return length;
	}
	int alloc_size()
	{
		return capacity;
	}
};

using namespace std;
int main(void)
{
	Vector<int> int_vec(2, 0);
	cout << "alloc_size: " << int_vec.alloc_size() << "\n";
	int_vec.push_back(3);
	cout << "alloc_size: " << int_vec.alloc_size() << "\n";
	int_vec.push_back(2);
	cout << "alloc_size: " << int_vec.alloc_size() << "\n";

	for (int i = 0; i < int_vec.size(); ++i)
	{
		cout << i << ": " << int_vec[i] << "\n";
	}

	Vector<string> str_vec(1, "o");
	cout << "alloc_size: " << str_vec.alloc_size() << "\n";
	str_vec.push_back("Hello");
	cout << "alloc_size: " << str_vec.alloc_size() << "\n";
	str_vec.push_back("World");
	cout << "alloc_size: " << str_vec.alloc_size() << "\n";

	for (int i = 0; i < str_vec.size(); ++i)
	{
		cout << i << ": " << str_vec[i] << "\n";
	}
	cout << "\n";

	Vector<bool> bool_vec;
	bool_vec.push_back(true);
	bool_vec.push_back(true);
	bool_vec.push_back(false);
	bool_vec.push_back(false);
	bool_vec.push_back(false);
	bool_vec.push_back(true);
	bool_vec.push_back(false);
	bool_vec.push_back(true);
	bool_vec.push_back(false);
	bool_vec.push_back(true);
	bool_vec.push_back(false);
	bool_vec.push_back(true);
	bool_vec.push_back(false);
	bool_vec.push_back(true);
	bool_vec.push_back(false);
	bool_vec.push_back(true);
	bool_vec.push_back(false);
	// 11000101010101010
	for (int i = 0; i < bool_vec.size(); ++i)
	{
		cout << bool_vec[i];
	}
	cout << "\n";
	// 000111101010101010
	bool_vec.remove(0);
	bool_vec.remove(0);
	bool_vec.insert(3, true);
	bool_vec.insert(3, true);
	bool_vec.insert(3, true);
	for (int i = 0; i < bool_vec.size(); ++i)
	{
		cout << bool_vec[i];
	}
	cout << "\n";
	// always 1 until size is smaller than 32
	cout << "alloc_size: " << bool_vec.alloc_size() << "\n";
	cout << "size: " << bool_vec.size() << "\n";
	// 111101010101010
	bool_vec.remove(0);
	bool_vec.remove(0);
	bool_vec.remove(0);
	for (int i = 0; i < bool_vec.size(); ++i)
	{
		cout << bool_vec[i];
	}
	// 0
	cout << "\n" << bool_vec.pop_back() << '\n';
	// 11110101010101
	for (int i = 0; i < bool_vec.size(); ++i)
	{
		cout << bool_vec[i];
	}
}