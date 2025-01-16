#ifndef DIFF_HH
#define DIFF_HH

#include <cstdint>
#include <fstream>
#include <string_view>
#include <vector>

class Diff
{
private:
    using ByteVector = std::vector<uint8_t>;

    ByteVector orig_;
    ByteVector new_;
public:
    Diff( std::string_view orig_filename, std::string_view new_filename)
    :
        orig_( readFile( orig_filename)),
        new_( readFile( new_filename))
    {}

    std::string dump() const;

private:
    ByteVector readFile( std::string_view filename);
};

#endif // DIFF_HH