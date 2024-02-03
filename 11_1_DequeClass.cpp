#include <iostream>
template <typename T>
class Deque
{
	const int size_per_block = 5;
	int start_idx = 2, end_idx = 2;
	T** blocks = nullptr;
	int first_block, last_block;
	int cnt_block = 0, cnt_data = 0;
	int alloc_size = 20;
public:
	Deque() { first_block = last_block = 5; }
	Deque(int _size_of_block, int _alloc_size, int _cnt_data) : size_per_block(_size_of_block), cnt_data(_cnt_data)
	{
		start_idx = end_idx = size_per_block / 2;
		cnt_block = cnt_data / size_per_block + 1;
		if (_alloc_size < cnt_block)
		{
			alloc_size = cnt_block + 1;
		}
		first_block = (alloc_size - cnt_block) / 2;
		blocks = new T * [alloc_size];
		for (int i = first_block; i < first_block + cnt_block; ++i)
		{
			T* temp = new T[size_per_block];
			blocks[i] = temp;
		}
		last_block = first_block + cnt_block;
	}
	Deque(int _size_of_block, int _alloc_size, int _cnt_data, T _val) : size_per_block(_size_of_block), cnt_data(_cnt_data)
	{
		start_idx = end_idx = size_per_block / 2;
		cnt_block = cnt_data / size_per_block + 1;
		if (_alloc_size < cnt_block)
		{
			alloc_size = cnt_block + 1;
		}
		first_block = (alloc_size - cnt_block) / 2;
		blocks = new T * [alloc_size];

		int first_offset = 0;
		T* temp_first = new T[size_per_block];
		for (int j = start_idx; j < size_per_block; ++j)
		{
			temp_first[j] = _val;
			++first_offset;
		}
		blocks[first_block] = temp_first;
		int j = 0;
		for (int i = first_block + 1; i < first_block + cnt_block; ++i)
		{
			T *temp = new T[size_per_block];
			int real_size_per_block = size_per_block;
			if (i == first_block + cnt_block - 1)
			{
				real_size_per_block -= first_offset;
			}
			for (j = 0; j < real_size_per_block; ++j)
			{
				temp[j] = _val;
			}
			blocks[i] = temp;
		}
		last_block = first_block + cnt_block;
		end_idx = j == size_per_block ? 0 : j;
	}
	// Todo: copy constructure
	Deque(const Deque& deq) : size_per_block(deq.size_of_block), start_idx(deq.start_idx), end_idx(deq.end_idx),
		first_block(deq.first_block), last_block(deq.last_block), cnt_block(deq.cnt_block), cnt_data(deq.cnt_data), alloc_size(deq.alloc_size)
	{
		blocks = new T * [alloc_size];

		int first_offset = 0;
		T* temp_first = new T[size_per_block];
		for (int j = start_idx; j < size_per_block; ++j)
		{
			temp_first[j] = deq.blocks[first_block][j];
			++first_offset;
		}
		blocks[first_block] = temp_first;
		int j = 0;
		for (int i = first_block + 1; i < first_block + cnt_block; ++i)
		{
			T* temp = new T[size_per_block];
			int real_size_per_block = size_per_block;
			if (i == first_block + cnt_block - 1)
			{
				real_size_per_block -= first_offset;
			}
			for (j = 0; j < real_size_per_block; ++j)
			{
				temp[j] = deq.blocks[i][j];
			}
			blocks[i] = temp;
		}
	}
	void print_all()
	{
		std::cout << first_block << "] ";
		for (int j = start_idx; j < size_per_block; ++j)
		{
			std::cout << blocks[first_block][j] << " ";
		}
		std::cout << std::endl;
		for (int i = first_block + 1; i < last_block; ++i)
		{
			std::cout << i <<"] ";
			for (int j = 0; j < size_per_block; ++j)
			{
				if (i == last_block - 1 && j >= end_idx)
				{
					break;
				}
				std::cout << blocks[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
	void print_all(int all)
	{
		for (int i = first_block; i < last_block; ++i)
		{
			std::cout << i << "] ";
			for (int j = 0; j < size_per_block; ++j)
			{
				std::cout << blocks[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
	class Iterator
	{
		T* location;
		int block_idx, cur_idx;
		Deque* deq;
		friend Deque;
	public:
		Iterator(T* _loc, int _blk, int _cur, Deque* _deq) : location(_loc), block_idx(_blk), cur_idx(_cur), deq(_deq) {}
		Iterator(const Iterator& iter) : location(iter.location), block_idx(iter.block_idx), cur_idx(iter.cur_idx), deq(iter.deq) {}
		// Todo : =, !=, ++iter, iter++, --iter, iter--, +, -, *
		Iterator& operator=(const Iterator& iter)
		{
			block_idx = iter.block_idx;
			cur_idx = iter.cur_idx;
			location = iter.location;
			deq = iter.deq;
			return (*this);
		}
		bool operator!=(const Iterator& iter) const
		{
			if (location == iter.location && deq == iter.deq)
			{
				return false;
			}
			return true;
		}
		Iterator& operator++()
		{
			++cur_idx;
			if (cur_idx >= deq->size_per_block)
			{
				++block_idx;
				cur_idx = 0;
			}
			if (block_idx == deq->last_block || (block_idx == deq->last_block - 1 && cur_idx == deq->end_idx))
			{
				cur_idx = deq->end_idx;
			}
			location = &deq->blocks[block_idx][cur_idx];
			//std::cout << "\n[" << block_idx << "][" << cur_idx << "]\n";
			return (*this);
		}
		Iterator operator++(int)
		{
			Iterator temp(*this);
			this->operator++();
			return temp;
		}
		Iterator& operator--()
		{
			if (block_idx == deq->first_block && cur_idx == deq->start_idx)
			{
				return (*this);
			}
			--cur_idx;
			if (cur_idx < 0)
			{
				--block_idx;
				cur_idx = deq->size_per_block - 1;
			}
			location = &deq->blocks[block_idx][cur_idx];
			//std::cout << "\n[" << block_idx << "][" << cur_idx << "]\n";
			return (*this);
		}
		Iterator operator--(int)
		{
			Iterator temp(*this);
			this->operator--();
			return temp;
		}
		Iterator operator-(int num)
		{
			Iterator temp(*this);
			for (int i = 0; i < num; ++i)
			{
				temp.operator--();
			}
			return temp;
		}
		Iterator operator+(int num)
		{
			Iterator temp(*this);
			for (int i = 0; i < num; ++i)
			{
				temp.operator++();
			}
			return temp;
		}
		T operator*()
		{
			return *location;
		};
	};
	friend Iterator;
	Iterator begin()
	{
		return Iterator(&blocks[first_block][start_idx], first_block, start_idx, this);
	}
	Iterator end()
	{
		if (end_idx != 0)
		{
			return Iterator(&blocks[last_block - 1][end_idx], last_block - 1, end_idx, this);
		}
		return Iterator(&blocks[last_block][end_idx], last_block, end_idx, this);
	}
	void print(Iterator iter)
	{
		std::cout << *iter.location << std::endl;
	}
};

int main(void)
{
	Deque<int> deq(5, 20, 10, -1);
	deq.print_all();
	std::cout << "----\n";
	deq.print(deq.begin() + 1);
	std::cout << "----\n";
	for (auto iter = deq.begin(); iter != deq.end();)
	{
		std::cout << *iter << " ";
		iter++;
	}
}