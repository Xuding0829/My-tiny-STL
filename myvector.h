#ifndef VECTOR_H_
#define VECTOR_H_
#include <iostream>
using namespace std;

template <typename T>
class MyVector
{
private:
	T* data;//指针存放数据
	int _size;//vector元素数量
	int _capacity;//vector容量
	
	//分配vector容量
	void Resize(size_t newCapacity)
	{
		T* newData = new T[newCapacity];
		for (size_t i = 0; i < _size; ++i)
		{
			newData[i] = data[i];
		}
		delete[] data;
		data = newData;
		_capacity = newCapacity;
	}

public:
	// 构造函数
	MyVector(int newsize = 0, int newcapacity = 10)
	{
		_size = newsize;
		_capacity = newcapacity;
		data = new T[_capacity];
	};

	// 析构函数
	~MyVector()
	{
		delete[] data;
	};

	// 返回元素的数量
	size_t Size() const
	{
		return _size;
	}

	// 返回数组的容量*-+
	size_t Capacity() const
	{
		return _capacity;
	}

	// 在末尾添加元素
	void pushback(const T& value)
	{
		if (_size == _capacity)
		{
			// 如果数组已满，扩展容量
			Resize(_capacity * 2);
		}
		data[_size++] = value;
	}

	void pop_back()
	{
		// int temp = data[_size];
		_size--;
		// 如果 容量有多余的，释放掉
		if (_size == _capacity / 4)
		{
			Resize(_capacity / 2);
		}
	}

	// 访问元素
	T& operator[](size_t index)
	{
		if (index >= _size)
		{
			// 处理越界访问
			throw std::out_of_range("Index out of range");
		}
		return data[index];
	}

	// 修改元素
	void modify(size_t index, const T& value)
	{
		if (index >= _size)
		{
			// 处理越界访问
			throw std::out_of_range("Index out of range");
		}
		data[index] = value;
	}
	//清空vector
	void clear()
	{
		_size = 0;
		delete[] data;
	}
   
	void resize(int newsize, T s = 0)
	{
		if (newsize <= _size)
			_size = newsize; // 如果新大小小于等于当前大小，直接更新当前大小
		else
		{
			if (newsize >= _capacity)
			{
				Resize(_capacity * 2); // 如果新大小大于等于容量，调用 Resize 函数进行扩容
			}
			for (int i = _size; i <= newsize; i++)
			{
				data[i] = s; // 初始化新增的元素，从当前大小到新大小
			}
			_size = newsize;
		}
	}
	//返回第一个元素
	T front()
	{
		return data[0];
	}
	//返回最后一个元素
	T back()
	{
		return data[_size - 1];
	}
	//重载=，使vector之间可以直接赋值
	MyVector operator=(MyVector c)
	{
		data = new T[c._capacity];
		_size = c._size;
		_capacity = c._capacity;
		for (int i = 0; i < _size; i++)
		{
			data[i] = c.data[i];
		}
		return *this;
	}
//判断vcetor是否为空
	bool empty()
	{
		if (_size == 0)
			return 1;
		else
			return 0;
	}
	//迭代器
	class Iterator
	{
	public:
		typedef T* iterator;
		typedef T* const_iterator;

		T* ptr;
		Iterator(T* p) : ptr(p) {}

		// 重载运算符*，以便可以通过迭代器访问元素
		T& operator*() const
		{
			return *ptr;
		}
		// 重载前缀递增运算符
		Iterator& operator++()
		{
			++ptr;
			return *this;
		}
		// 重载后缀递增运算符
		Iterator operator++(int)
		{
			Iterator temp = *this;
			++ptr;
			return temp;
		}
		// 重载前缀递减运算符
		Iterator& operator--()
		{
			--ptr;
			return *this;
		}
		// 重载后缀递减运算符
		Iterator operator--(int)
		{
			Iterator temp = *this;
			--ptr;
			return temp;
		}
		// 重载加法运算符
		Iterator operator+(int n) const
		{
			return Iterator(ptr + n);
		}
		// 重载减法运算符
		Iterator operator-(int n) const
		{
			return Iterator(ptr - n);
		}
		// 重载复合加法运算符
		Iterator& operator+=(int n)
		{
			ptr += n;
			return *this;
		}
		// 重载复合减法运算符
		Iterator& operator-=(int n)
		{
			ptr -= n;
			return *this;
		}
		// 重载相等运算符
		bool operator==(const Iterator& other) const
		{
			return ptr == other.ptr;
		}
		// 重载不等运算符
		bool operator!=(const Iterator& other) const
		{
			return ptr != other.ptr;
		}
		// 重载大于运算符
		bool operator>(const Iterator& other) const
		{
			return ptr > other.ptr;
		}
		// 重载小于运算符
		bool operator<(const Iterator& other) const
		{
			return ptr < other.ptr;
		}
		// 重载大于等于运算符
		bool operator>=(const Iterator& other) const
		{
			return ptr >= other.ptr;
		}
		// 重载小于等于运算符
		bool operator<=(const Iterator& other) const
		{
			return ptr <= other.ptr;
		}
		// 重载下标运算符
		T& operator[](int index) const
		{
			return *(ptr + index);
		}
	};
	Iterator begin() const
	{
		return Iterator(data);
	}

	// 返回结束迭代器
	Iterator end() const
	{
		return Iterator(data + _size);
	}
};

// template <typename T>

#endif