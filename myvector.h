#ifndef VECTOR_H_
#define VECTOR_H_
#include <iostream>
using namespace std;

template <typename T>
class MyVector
{
private:
	T* data;//ָ��������
	int _size;//vectorԪ������
	int _capacity;//vector����
	
	//����vector����
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
	// ���캯��
	MyVector(int newsize = 0, int newcapacity = 10)
	{
		_size = newsize;
		_capacity = newcapacity;
		data = new T[_capacity];
	};

	// ��������
	~MyVector()
	{
		delete[] data;
	};

	// ����Ԫ�ص�����
	size_t Size() const
	{
		return _size;
	}

	// �������������*-+
	size_t Capacity() const
	{
		return _capacity;
	}

	// ��ĩβ���Ԫ��
	void pushback(const T& value)
	{
		if (_size == _capacity)
		{
			// ���������������չ����
			Resize(_capacity * 2);
		}
		data[_size++] = value;
	}

	void pop_back()
	{
		// int temp = data[_size];
		_size--;
		// ��� �����ж���ģ��ͷŵ�
		if (_size == _capacity / 4)
		{
			Resize(_capacity / 2);
		}
	}

	// ����Ԫ��
	T& operator[](size_t index)
	{
		if (index >= _size)
		{
			// ����Խ�����
			throw std::out_of_range("Index out of range");
		}
		return data[index];
	}

	// �޸�Ԫ��
	void modify(size_t index, const T& value)
	{
		if (index >= _size)
		{
			// ����Խ�����
			throw std::out_of_range("Index out of range");
		}
		data[index] = value;
	}
	//���vector
	void clear()
	{
		_size = 0;
		delete[] data;
	}
   
	void resize(int newsize, T s = 0)
	{
		if (newsize <= _size)
			_size = newsize; // ����´�СС�ڵ��ڵ�ǰ��С��ֱ�Ӹ��µ�ǰ��С
		else
		{
			if (newsize >= _capacity)
			{
				Resize(_capacity * 2); // ����´�С���ڵ������������� Resize ������������
			}
			for (int i = _size; i <= newsize; i++)
			{
				data[i] = s; // ��ʼ��������Ԫ�أ��ӵ�ǰ��С���´�С
			}
			_size = newsize;
		}
	}
	//���ص�һ��Ԫ��
	T front()
	{
		return data[0];
	}
	//�������һ��Ԫ��
	T back()
	{
		return data[_size - 1];
	}
	//����=��ʹvector֮�����ֱ�Ӹ�ֵ
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
//�ж�vcetor�Ƿ�Ϊ��
	bool empty()
	{
		if (_size == 0)
			return 1;
		else
			return 0;
	}
	//������
	class Iterator
	{
	public:
		typedef T* iterator;
		typedef T* const_iterator;

		T* ptr;
		Iterator(T* p) : ptr(p) {}

		// ���������*���Ա����ͨ������������Ԫ��
		T& operator*() const
		{
			return *ptr;
		}
		// ����ǰ׺���������
		Iterator& operator++()
		{
			++ptr;
			return *this;
		}
		// ���غ�׺���������
		Iterator operator++(int)
		{
			Iterator temp = *this;
			++ptr;
			return temp;
		}
		// ����ǰ׺�ݼ������
		Iterator& operator--()
		{
			--ptr;
			return *this;
		}
		// ���غ�׺�ݼ������
		Iterator operator--(int)
		{
			Iterator temp = *this;
			--ptr;
			return temp;
		}
		// ���ؼӷ������
		Iterator operator+(int n) const
		{
			return Iterator(ptr + n);
		}
		// ���ؼ��������
		Iterator operator-(int n) const
		{
			return Iterator(ptr - n);
		}
		// ���ظ��ϼӷ������
		Iterator& operator+=(int n)
		{
			ptr += n;
			return *this;
		}
		// ���ظ��ϼ��������
		Iterator& operator-=(int n)
		{
			ptr -= n;
			return *this;
		}
		// ������������
		bool operator==(const Iterator& other) const
		{
			return ptr == other.ptr;
		}
		// ���ز��������
		bool operator!=(const Iterator& other) const
		{
			return ptr != other.ptr;
		}
		// ���ش��������
		bool operator>(const Iterator& other) const
		{
			return ptr > other.ptr;
		}
		// ����С�������
		bool operator<(const Iterator& other) const
		{
			return ptr < other.ptr;
		}
		// ���ش��ڵ��������
		bool operator>=(const Iterator& other) const
		{
			return ptr >= other.ptr;
		}
		// ����С�ڵ��������
		bool operator<=(const Iterator& other) const
		{
			return ptr <= other.ptr;
		}
		// �����±������
		T& operator[](int index) const
		{
			return *(ptr + index);
		}
	};
	Iterator begin() const
	{
		return Iterator(data);
	}

	// ���ؽ���������
	Iterator end() const
	{
		return Iterator(data + _size);
	}
};

// template <typename T>

#endif