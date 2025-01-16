#ifndef DIFF_HH
#define DIFF_HH

#include <string_view>

#include "useful.hh"

class Diff
{
private:
    ByteVector orig_;
    ByteVector new_;

    std::vector<bool> saved_orig_{};
    std::vector<bool> saved_new_{};
public:
    Diff( std::string_view orig_filename, std::string_view new_filename)
    :
        orig_( readFile( orig_filename)),
        new_( readFile( new_filename))
    {}

    void process();
    std::string getDiff() const;
    std::string dump() const;
};

#endif // DIFF_HH