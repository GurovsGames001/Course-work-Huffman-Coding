#ifndef __STACK
#define __STACK
#include <memory>
#include "exceptions.h"

template <class T>
class Stack
{
public:
	virtual ~Stack() {}
	virtual void push(const T& e) = 0; // ���������� �������� � ����
	virtual const T& pop() = 0; // �������� � ����������� �������� ��������
	virtual bool isEmpty() = 0; // �������� ����� �� ������� 
};

template <class T>
class StackArray : public Stack<T>
{
public:
	StackArray(size_t size = 100); // size ������ ������ ����� "�� ���������"
	StackArray(const StackArray<T>& src); // = delete;
	StackArray(StackArray<T>&& src);
	StackArray<T>& operator=(const StackArray<T>& src); // = delete;
	StackArray<T>& operator=(StackArray<T>&& src);
	~StackArray() {};
	void push(const T& e);
	const T& pop();
	const T top();
	bool isEmpty() { return top_ == 0; };

private:
	std::unique_ptr<T[]> array_; // ������ ��������� �����: !!! array_[0] � �� ������������, top_ �� 1 �� size_
	size_t top_; // ������� �����, ������� ���������� � ���� ���������
	size_t size_; // ������ �����
	void swap(StackArray<T>& src);
};

// ����������� ����������� � �������� ����� ���������� ������, ���� �� ������� delete
template <class T>
StackArray<T>::StackArray(const StackArray<T>& src) :
	size_(src.size_),
	top_(src.top_)
{
	try // !!! array_[0] � �� ������������, top_ �� 1 �� size_
	{
		array_ = std::make_unique<T[]>(src.size_ + 1);
	}
	catch (...) 
	{
		throw WrongStackSize();
	}
	// ����������� �������
	for (size_t i = 1; i < src.top_; i++) 
	{
		array_[i] = src.array_[i];
	}
}

// ����������� �����������
template <class T>
StackArray<T>::StackArray(StackArray<T>&& src) : size_(src.size_), top_(src.top_)
{
	array_ = std::move(src.array_);
	src.size_ = 0;
	src.top_ = 0;
}

template <class T>
StackArray<T>& StackArray<T>::operator=(const StackArray<T>& src)
{
	size_ = src.size_;
	top_ = src.top_;
	std::unique_ptr<T[]> temp = std::make_unique<T[]>(size_ + 1);
	// ����������� �������
	for (size_t i = 1; i < top_; i++)
	{
		temp[i] = src.array_[i];
	}
	array_.reset();
	array_ = std::move(temp);

	return *this;
}

template <class T>
StackArray<T>& StackArray<T>::operator=(StackArray<T>&& src)
{
	size_ = src.size_;
	top_ = src.top_;
	array_.reset();
	array_ = std::move(src.array_);
	src.size_ = 0;
	src.top_ = 0;

	return *this;
}

template <class T>
void StackArray<T> ::swap(StackArray<T>& src)
{
	std::swap(array_, src.array_); // (this->array_, src.array_)
	std::swap(top_, src.top_);
	std::swap(size_, src.size_);
}

template <class T>
StackArray<T>::StackArray(size_t size) :
	size_(size),
	top_(0)
{ // !!! array_[0] � �� ������������, top_ �� 1 �� size_
	try 
	{
		array_ = std::make_unique<T[]>(size_ + 1); // �������� �������� ������ ��� �������� �����...
	}
	catch (...) // ���� ���-�� ��������� (��������, ������ ������� �������
	{							// ��� �������������) - ��������� �������������� ��������
		throw WrongStackSize();
	}
}

template <class T>
void StackArray<T>::push(const T& e)
{
	if (top_ == size_) 
	{
		std::unique_ptr<T[]> temp = std::make_unique<T[]>(size_ * 2 + 1);
		// ����������� �������
		for (size_t i = 1; i < top_; i++)
		{
			temp[i] = array_[i];
		}
		array_.reset();
		array_ = std::move(temp);
		size_ *= 2;

		//throw StackOverflow(); // ��� ����� ��� ������ ��������
	}
	array_[++top_] = e; // ��������� �������� � ����
}

template <class T>
const T& StackArray<T>::pop()
{
	if (isEmpty()) // (top_ == 0)
	{
		throw StackUnderflow(); // ���� ����
	}
	return array_[top_--]; // ������� ��������� �������� � �����, �� ������ "�� ��������"
}

template <class T>
const T StackArray<T>::top()
{
	return array_[top_];
}

#endif