
#include <sstream>
#include <vector>
#include <iostream>
#include "table.h"

tree_streambuf::tree_streambuf()
{
    setp(nullptr, nullptr);
}

void tree_streambuf::add_sink(std::streambuf *streambuf)
{
    this->streams.push_back(streambuf);
};

tree_streambuf::int_type tree_streambuf::overflow(tree_streambuf::int_type ch)
{
    for (auto stream:streams)
    {
        stream->sputc(ch);
    }
    return ch;
}
