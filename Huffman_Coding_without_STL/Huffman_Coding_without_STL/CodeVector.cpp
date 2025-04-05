#include "CodeVector.h"

void CodeVector::push(const bool value)
{
	if (pos_ <= 32)
	{
		code_ = code_ | value << pos_;
		pos_++;
	}
	else
	{
		throw CodeVectorOverflow();
	}
}

void CodeVector::pop()
{
	if (pos_ > 0)
	{
		code_ = code_ & ~(1 << (pos_ - 1));
		pos_--;
	}
	else
	{
		throw CodeVectorUnderflow();
	}
}

bool CodeVector::top() const
{
	return (pos_ != 0) ? code_ & 1 << (pos_ - 1) : 0;
}