#ifndef __EXCEPTION
#define __EXCEPTION
#include <exception>

///////////////////////////////////////////////
// Исключения для CodeVector
class CodeVectorOverflow : public std::exception
{
public:
	CodeVectorOverflow() : reason_("ERROR: CodeVector Overflow") {}
	const char* what() const { return reason_; }
private:
	const char* reason_; // ! const
};

class CodeVectorUnderflow : public std::exception
{
public:
	CodeVectorUnderflow() : reason_("ERROR: CodeVector Underflow") {}
	const char* what() const { return reason_; }
private:
	const char* reason_; // ! const
};

#endif