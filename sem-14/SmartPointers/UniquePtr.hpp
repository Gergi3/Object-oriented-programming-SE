#pragma once
#include <utility>

template<typename T>
class UniquePtr
{
	T* ptr = nullptr;

	void moveFrom(UniquePtr<T>&& other);
	void free();

public:
	UniquePtr() = default;
	UniquePtr(T* ptr);
	UniquePtr(const UniquePtr<T>& other) = delete;
	UniquePtr<T>& operator=(const UniquePtr<T>& other) = delete;
	UniquePtr(UniquePtr<T>&& other) noexcept;
	UniquePtr<T>& operator=(UniquePtr<T>&& other) noexcept;
	~UniquePtr();

	T& operator*();
	const T& operator*() const;

	T* operator->();
	const T* operator->() const;

	T* get();
	const T* get() const;

	bool isInitialized() const;
	operator bool() const;

	T* release();
	void reset();
};

template<typename T>
void UniquePtr<T>::moveFrom(UniquePtr<T>&& other)
{
	ptr = other.ptr;
	other.ptr = nullptr;
}

template<typename T>
void UniquePtr<T>::free()
{
	delete ptr;
	ptr = nullptr;
}

template<typename T>
UniquePtr<T>::UniquePtr(T* ptr)
{
	this->ptr = ptr;
}

template<typename T>
UniquePtr<T>::UniquePtr(UniquePtr<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template<typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<typename T>
UniquePtr<T>::~UniquePtr()
{
	free();
}

template<typename T>
T& UniquePtr<T>::operator*()
{
	if (this->ptr == nullptr)
	{
		throw std::runtime_error("nullptr!");
	}
	return *ptr;
}

template<typename T>
const T& UniquePtr<T>::operator*() const
{
	if (this->ptr == nullptr)
	{
		throw std::runtime_error("nullptr!");
	}
	return *ptr;
}

template<typename T>
T* UniquePtr<T>::operator->()
{
	return ptr;
}

template<typename T>
const T* UniquePtr<T>::operator->() const
{
	return ptr;
}

template<typename T>
T* UniquePtr<T>::get()
{
	return ptr;
}

template<typename T>
const T* UniquePtr<T>::get() const
{
	return ptr;
}

template<typename T>
bool UniquePtr<T>::isInitialized() const
{
	return ptr != nullptr;
}

template<typename T>
UniquePtr<T>::operator bool() const
{
	return isInitialized();
}

template<typename T>
inline T* UniquePtr<T>::release()
{
	T* toRelease = ptr;
	ptr = nullptr;
	return toRelease;
}

template<typename T>
void UniquePtr<T>::reset()
{
	free();
}
