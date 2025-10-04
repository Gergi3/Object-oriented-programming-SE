#include "shared_ptr.hpp"

template<typename T>
class WeakPtr
{
	template<class D> friend class SharedPtr;

	T* ptr;
	Counter* counter;

	void copyFrom(const WeakPtr<T>& other);
	void moveFrom(WeakPtr<T>&& other);
	void free();

public:

	WeakPtr() = default;
	WeakPtr(SharedPtr<T>& ptr);
	WeakPtr(const WeakPtr<T>& other);
	WeakPtr<T>& operator=(const WeakPtr<T>& other);
	WeakPtr(WeakPtr<T>&& other) noexcept;
	WeakPtr<T>& operator=(WeakPtr<T>&& other) noexcept;
	~WeakPtr();

	SharedPtr<T> lock() const;
	bool expired() const;
};

template<typename T>
void WeakPtr<T>::copyFrom(const WeakPtr<T>& other)
{
	ptr = other.ptr;
	counter = other.counter;

	if (counter)
	{
		counter->addWeakPtr();
	}
}

template<typename T>
void WeakPtr<T>::moveFrom(WeakPtr<T>&& other)
{
	ptr = other.ptr;
	other.ptr = nullptr;
	counter = other.counter;
	other.counter = nullptr;
}

template<typename T>
void WeakPtr<T>::free()
{
	if (!counter && !ptr)
	{
		return;
	}

	counter->removeWeakPtr();

	if (counter->weakCount == 0)
	{
		delete counter;
	}
}

template<typename T>
WeakPtr<T>::WeakPtr(SharedPtr<T>& ptr)
{
	this->ptr = ptr.ptr;
	counter = ptr.counter;

	if (counter)
	{
		counter->addWeakPtr();
	}
}

template<typename T>
WeakPtr<T>::WeakPtr(const WeakPtr<T>& other)
{
	copyFrom(other);
}

template<typename T>
WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
WeakPtr<T>::WeakPtr(WeakPtr<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template<typename T>
WeakPtr<T>& WeakPtr<T>::operator=(WeakPtr<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<typename T>
WeakPtr<T>::~WeakPtr()
{
	free();
}

template<typename T>
SharedPtr<T> WeakPtr<T>::lock() const
{
	if (expired())
	{
		return SharedPtr<T>();
	}
	return SharedPtr<T>(*this);
}

template<typename T>
bool WeakPtr<T>::expired() const
{
	return counter && counter->sharedCount == 0;
}
