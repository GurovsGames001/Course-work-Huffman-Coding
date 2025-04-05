#ifndef _STREAM_GUARD_H
#define _STREAM_GUARD_H
#include <iostream>

class StreamGuard
{
public:
    StreamGuard(std::basic_ios<char>& s) :
        s_(s),
        fill_(s.fill()),
        precision_(s.precision()),
        fmt_(s.flags())
    {}

    ~StreamGuard()
    {
        s_.fill(fill_);
        s_.precision(precision_);
        s_.flags(fmt_);
    }
private:
    std::basic_ios<char>& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags fmt_;
};

#endif