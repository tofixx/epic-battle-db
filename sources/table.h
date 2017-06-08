
#pragma once

#include <sstream>
#include <vector>
#include <string>
#include <iostream>

class tree_streambuf : public std::streambuf
{

private:

    // avoid reading from tree_buf
    using std::streambuf::sgetc;
    using std::streambuf::sgetn;
    using std::streambuf::in_avail;
    using std::streambuf::sbumpc;
    using std::streambuf::snextc;
    using std::streambuf::sputbackc;
    using std::streambuf::sungetc;

    std::vector<std::streambuf *> streams;


protected:
    using std::streambuf::overflow;
    virtual tree_streambuf::int_type overflow(tree_streambuf::int_type ch);

public:
    tree_streambuf();

    void add_sink(std::streambuf *streambuf);

};
