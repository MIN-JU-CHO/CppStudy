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
			// can delete new int[], new Address[]
			delete[] cur->next;
		}
		~Array()
		{
			delete_address(top);
			delete[] size;
		}
		Int operator[](const int idx);
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
}
int main(void)
{
	int size[] = { 2,3,4 };
	MyArray::Array arr(3, size);

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 4; ++k)
			{	// (((arr.operator[](i)).operator[](j)).operator[](k)).operator=((i+1)*(j+1)*(k+1))
				arr[i][j][k] = (i + 1) * (j + 1) * (k + 1);
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