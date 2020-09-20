#pragma once


template<typename T, size_t i>
class MyArray
{
public:
	MyArray() 
	{
		array = new T[i];
	}
	~MyArray()
	{
		delete [] array;
	}
	void fill(const T& value) 
	{
		for (T* i = begin(); i != end(); i++) 
		{
			*i = value;
		}
	}

	//Exercise 1.4
	//Copy constructor that allows implicit conversions.
	//Missing handling of different length arrays.
	template<typename U>
	MyArray(const MyArray<U, i>& original) 
	{
		array = new T[i];
		T* x = begin();
		U* y = original.begin();
		while (x != end()) {
			*x = *y;
			x++, y++;
		}
	}
	//Assignment operator that allows for arrays of one type, to be implicit converted to another type.
	template <typename U>
	MyArray<T, i>& operator=(const MyArray<U, i>& original) 
	{
		T* x = begin();
		U* y = original.begin();
		while (x != end()) {
			*x = *y;
			x++, y++;
		}
		return *this;
	}

	T* begin() const
	{
		return array;
	}
	T* end() const 
	{
		return array + _size;
	}
	T& operator[](int const i)
	{
		return *(array + i);
	}
	size_t size() const
	{
		return _size;
	}
private:
	size_t _size = i;
	T* array;
};

// Exercise 2.1 Partial specialization
template<typename T, size_t s>
class MyArray<T*, s>
{
public:
	MyArray()
	{
		array = new T*[s];
		for (T** i = begin(); i != end(); i++)
		{
			*i = nullptr;
		}
	}
	//Now uses delete to delete every element in the array. 
	~MyArray()
	{
		for(T** i = begin(); i != end(); i++)
		{
			delete (*i);
		}
		delete[] array;
	}
	//Figure out what to do with this. Initial guess is to delete it, or make it into fillnull with nullptr's.
	//void fill(const T& value)
	//{
	//	for (T* i = begin(); i != end(); i++)
	//	{
	//		*i = value;
	//	}
	//}

	//Missing handling of different length arrays.
	//Adding * to handle pointer elements used for initialization to be destroyed correctly
	template<typename U>
	MyArray(const MyArray<U, s>& original)
	{
		array = new T*[s];
		T** x = begin();
		U* y = original.begin();
		while (x != end()) {
			*x = *y;
			x++, y++;
		}
	}
	template <typename U>
	MyArray<T*, s>& operator=(const MyArray<U, s>& original)
	{
		T** x = begin();
		U* y = original.begin();
		while (x != end()) {
			*x = *y;
			x++, y++;
		}
		return *this;
	}

	T** begin() const
	{
		return array;
	}
	T** end() const
	{
		return array + _size;
	}
	T*& operator[](int i)
	{
		return *(array + i);
	}
	size_t size() const
	{
		return _size;
	}
private:
	size_t _size = s;
	T** array;
};