#include <iostream>

namespace MyArray
{
	class Array;
	class Int;

	class Array
	{
		friend Int;
		
		const int dim;
		int* size;

		struct Address
		{
			int level;
			void* next;
		};
		Address* top;
	public:
		class Iterator
		{
			friend Int;

			int* location;
			Array* arr;
		public:
			Iterator(Array* _arr, int* loc = NULL) : arr(_arr)
			{
				location = new int[arr->dim];
				for (int i = 0; i < arr->dim; ++i)
				{
					location[i] = loc != NULL ? loc[i] : 0;
				}
			}
			Iterator(const Iterator& iter) : arr(iter.arr)
			{
				location = new int[arr->dim];
				for (int i = 0; i < arr->dim; ++i)
				{
					location[i] = iter.location[i];
				}
			}
			~Iterator()
			{
				delete[] location;
			}
			Iterator& operator++()
			{
				if (location[0] >= arr->size[0])
				{
					return (*this);
				}
				bool carry = false;
				int i = arr->dim - 1;
				do
				{
					++location[i];
					if (location[i] >= arr->size[i] && i >= 1)
					{
						carry = true;
						location[i] -= arr->size[i];
						--i;
					}
					else
					{
						carry = false;
					}
				} while (carry && i >= 0);
				return *this;
			}
			Iterator operator++(int)
			{
				Iterator temp(*this);
				this->operator++();
				return temp;
			}
			Iterator& operator=(const Iterator& iter)
			{
				arr = iter.arr;
				location = new int[arr->dim];
				for (int i = 0; i < arr->dim; ++i)
				{
					location[i] = iter.location[i];
				}
				return *this;
			}
			bool operator!=(const Iterator& iter)
			{
				if (arr->dim != iter.arr->dim)
				{
					return true;
				}
				for (int i = 0; i < arr->dim; ++i)
				{
					if (location[i] != iter.location[i])
					{
						return true;
					}
				}
				return false;
			}
			Int operator*();
		};
		friend Iterator;
		Array(int _dim, int* array_size) : dim(_dim)
		{
			size = new int[_dim];
			for (int i = 0; i < _dim; ++i)
			{
				size[i] = array_size[i];
			}
			top = new Address;
			top->level = 0;
			initialize_address(top);
		}
		Array(const Array& arr) : dim(arr.dim)
		{
			size = new int[dim];
			for (int i = 0; i < dim; ++i)
			{
				size[i] = arr.size[i];
			}
			top = new Address;
			top->level = 0;
			initialize_address(top);
		}
		void initialize_address(Address* cur)	// TopDown
		{
			if (!cur)
			{
				return;
			}
			if (cur->level == dim - 1)
			{
				cur->next = new int[size[cur->level]];
				return;
			}
			cur->next = new Address[size[cur->level]];
			for (int i = 0; i < size[cur->level]; ++i)
			{
				(static_cast<Address*>(cur->next) + i)->level = cur->level + 1;
				initialize_address(static_cast<Address*>(cur->next) + i);
			}
		}
		void delete_address(Address* cur)		// BottomUp
		{
			if (!cur)
			{
				return;
			}
			for (int i = 0; cur->level < dim-1 && i < size[cur->level]; ++i)
			{
				delete_address(static_cast<Address*>(cur->next) + i);
			}
			// delete real at Last Level
			if (cur->level == dim - 1)
			{
				delete[] static_cast<int*>(cur->next);
				return;
			}
			delete[] static_cast<Address*>(cur->next);
		}
		~Array()
		{
			delete_address(top);
			delete[] size;
		}
		Int operator[](const int idx);

		Iterator begin()
		{
			int* loc = new int[dim];
			for (int i = 0; i < dim; ++i)
			{
				loc[i] = 0;
			}
			Iterator temp(this, loc);
			delete[] loc;
			return temp;
		}
		Iterator end()
		{
			int* loc = new int[dim];
			loc[0] = size[0];
			for (int i = 1; i < dim; ++i)
			{
				loc[i] = 0;
			}
			Iterator temp(this, loc);
			delete[] loc;
			return temp;
		}
	};
	class Int
	{
		void* data;
		int levelp1;
		Array* array;
	public:
		Int(int idx, int _levelp1 = 0, void* _data = NULL, Array* _array = NULL) : levelp1(_levelp1), data(_data), array(_array)
		{
			if (levelp1 < 1 || idx >= array->size[levelp1 - 1])
			{
				return;
			}
			if (levelp1 == array->dim)
			{
				data = static_cast<void*>(static_cast<int*>(static_cast<Array::Address*>(data)->next) + idx);
			}
			else
			{
				data = static_cast<void*>(static_cast<Array::Address*>(static_cast<Array::Address*>(data)->next) + idx);
			}
		}
		Int(const Int& i) : data(i.data), levelp1(i.levelp1), array(i.array) {}
		Int& operator=(const int& a)						// 3
		{
			if (data)	// assign real int value
			{
				*static_cast<int*>(data) = a;
			}
			return *this;
		}
		Int operator[](const int idx)						// 2
		{
			if (!data)	// if prev idx out of range
			{
				return 0;
			}
			return Int(idx, levelp1 + 1, data, array);
		}
		operator int()										// 4
		{
			if (data)
			{
				return *static_cast<int*>(data);
			}
			return 0;
		}
	};
	Int Array::operator[](const int idx)					// 1
	{
		return Int(idx, 1, static_cast<void*>(top), this);
	}
	Int Array::Iterator::operator*()
	{
		Int start = arr->operator[](location[0]);
		for (int i = 1; i < arr->dim; ++i)
		{
			start = start.operator[](location[i]);
		}
		return start;
	}
}
int main(void)
{
	int size[] = { 2,3,4 };
	MyArray::Array arr(3, size);

	MyArray::Array::Iterator iter = arr.begin();
	for (int i = 0; iter != arr.end(); ++i, iter++)
	{
		(*iter) = i;
	}
	for (iter = arr.begin(); iter != arr.end(); ++iter)
	{
		std::cout << (*iter) << std::endl;
	}
	std::cout << std::endl;

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 4; ++k)
			{	// (((arr.operator[](i)).operator[](j)).operator[](k)).operator=((i+1)*(j+1)*(k+1))
				arr[i][j][k] = (i + 1) * (j + 1) * (k + 1) + arr[i][j][k];
			}	// 1 -> 2 -> 2 -> 3
		}
	}
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 4; ++k)
			{	// (((arr.operator[](i)).operator[](j)).operator[](k)).operator int()
				std::cout << "[" << i << "]" << "[" << j << "]" << "[" << k << "]: " << arr[i][j][k] << std::endl;
			}	// 1 -> 2 -> 2 -> 4
		}
	}
}