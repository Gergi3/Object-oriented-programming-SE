#pragma once
#include <utility>

struct Counter
{
	unsigned sharedCount = 0;
	unsigned weakCount = 0;

	void addSharedPtr()
	{
		sharedCount++;
		if (sharedCount == 1)
		{
			weakCount++;
		}
	}
	void removeSharedPtr()
	{
		sharedCount--;
		if (sharedCount == 0)
		{
			weakCount--;
		}
	}
	void addWeakPtr()
	{
		weakCount++;
	}
	void removeWeakPtr()
	{
		weakCount--;
	}

};

template<typename T> // forward declaration
class WeakPtr;

template<typename T>
class SharedPtr
{
	template<typename T>
	friend class WeakPtr;

	T* ptr = nullptr;
	Counter* counter = nullptr;
	
	void copyFrom(const SharedPtr<T>& other);
	void moveFrom(SharedPtr<T>&& other);
	void free();

	SharedPtr(WeakPtr<T>& ptr);

public:

	SharedPtr() = default;
	SharedPtr(T* ptr);
	SharedPtr(const SharedPtr<T>& other);
	SharedPtr<T>& operator=(const SharedPtr<T>& other);
	SharedPtr(SharedPtr<T>&& other) noexcept;
	SharedPtr<T>& operator=(SharedPtr<T>&& other) noexcept;
	~SharedPtr();

	T& operator*();
	const T& operator*() const;

	T* operator->();
	const T* operator->() const;

	bool isInitialized() const;
	operator bool() const;
};

template<typename T>
void SharedPtr<T>::copyFrom(const SharedPtr<T>& other)
{
	ptr = other.ptr;
	counter = other.counter;

	if (counter)
	{
		counter->addSharedPtr();
	}
}

template<typename T>
void SharedPtr<T>::moveFrom(SharedPtr<T>&& other)
{
	ptr = other.ptr;
	other.ptr = nullptr;
	counter = other.counter;
	other.counter = nullptr;
}

template<typename T>
void SharedPtr<T>::free()
{
	if (!counter && !ptr)
	{
		return;
	}

	counter->removeSharedPtr();

	if (counter->sharedCount == 0)
	{
		delete ptr;
	}

	if (counter->weakCount == 0)
	{
		delete counter;
	}
}

template<typename T>
SharedPtr<T>::SharedPtr(WeakPtr<T>& ptr)
{
	this->ptr = ptr.ptr;
	counter = ptr.counter;

	if (counter)
	{
		counter->addSharedPtr();
	}
}

template<typename T>
SharedPtr<T>::SharedPtr(T* ptr)
{
	if (ptr)
	{
		this->ptr = ptr;
		this->counter = new Counter();
		this->counter->addSharedPtr();
	}
}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other)
{
	copyFrom(other);
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<typename T>
SharedPtr<T>::~SharedPtr()
{
	free();
}

template<typename T>
T& SharedPtr<T>::operator*()
{
	if (this->ptr == nullptr)
	{
		throw std::runtime_error("nullptr!");
	}
	return *ptr;
}

template<typename T>
const T& SharedPtr<T>::operator*() const
{
	if (this->ptr == nullptr)
	{
		throw std::runtime_error("nullptr!");
	}
	return *ptr;
}

template<typename T>
T* SharedPtr<T>::operator->()
{
	return ptr;
}

template<typename T>
const T* SharedPtr<T>::operator->() const
{
	return ptr;
}

template<typename T>
bool SharedPtr<T>::isInitialized() const
{
	return ptr != nullptr;
}

template<typename T>
SharedPtr<T>::operator bool() const
{
	return isInitialized();
}
