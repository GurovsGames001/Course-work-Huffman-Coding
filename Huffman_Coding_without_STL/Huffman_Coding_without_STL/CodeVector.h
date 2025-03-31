#ifndef _CODE_VECTOR_H
#define _CODE_VECTOR_H
#include "exceptions.h"

class CodeVector
{
public:
	CodeVector() : code_(0), pos_(0) {};
	CodeVector(const CodeVector& otherCodeVector) = default;
	CodeVector(CodeVector&& otherCodeVector) = default;
	~CodeVector() {};

	CodeVector& operator=(const CodeVector& otherCodeVector) = default;
	CodeVector& operator=(CodeVector&& otherCodeVector) = default;
	bool operator[](const unsigned int i) const { return code_ & 1 << i; };

	void push(const bool value);
	void pop();
	bool top() const;
	bool isEmpty() const { return pos_ == 0; };
	unsigned int size() const { return pos_; };

private:
	int code_;
	unsigned int pos_;
};

#endif