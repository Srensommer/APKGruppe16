#pragma once
namespace sharedPointerNamespace {
	template<typename T>
	struct Helper
	{
		virtual void operator()(T* t) = 0;
	};

	template<typename T, typename D>
	struct HelperImp : Helper<D>
	{
		HelperImp(D d) : _d{ d } {};
		virtual void operator()(T* t) { _d(t); }
		D _d;

	};

	template<typename T>
	class SharedPtr {
	private:
		T* ptr;
		size_t* count_ptr;
		Helper<T>* _h;

	public:
		template<typename D>
		explicit SharedPtr(T* t, D d)
		{
			_h = new HelperImp<T, D>(d);
			count_ptr = new size_t;
			*count_ptr = 1;
		}

		SharedPtr(T* t) : ptr(t)
		{
			count_ptr = new size_t;
			*count_ptr = 1;
		}

		SharedPtr(const SharedPtr& other)
		{
			ptr = other.ptr;
			count_ptr = other.count_ptr;
			(*count_ptr)++;
		}

		SharedPtr& operator=(const SharedPtr& other)
		{
			if (ptr == other.ptr) return ptr;
			(*count_ptr)--;
			if (*count_ptr == 0)
			{
				delete ptr;
				delete count_ptr;
			}
			ptr = other.ptr;
			count_ptr = other.count_ptr;
			(*count_ptr)++;
			return *this;
		}

		~SharedPtr()
		{
			--* count_ptr;
			if (*count_ptr == 0)
			{
				if (_h)
				{
					(*_h)(ptr);
				}
				else
				{
					delete ptr;
				}
				delete count_ptr;
			}
		}

		T& operator*() const
		{
			return *ptr;
		}

		T* operator->() const
		{
			return ptr;
		}

		bool operator==(const SharedPtr& other)
		{
			return ptr == other.ptr;
		}

		explicit operator bool() const
		{
			return *count_ptr > 0 ? true : false;
		}

		size_t count() const
		{
			return *count_ptr;
		}

	};
}