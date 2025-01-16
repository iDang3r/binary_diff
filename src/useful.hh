#ifndef USEFUL_HH
#define USEFUL_HH

#include <cstdint>
#include <vector>

using Byte = uint8_t;
using ByteVector = std::vector<Byte>;

inline std::string dump( const ByteVector& bvec)
{
    return std::string( (char*)bvec.data(), bvec.size());
}

ByteVector readFile( std::string_view filename);

#endif // USEFUL_HH
