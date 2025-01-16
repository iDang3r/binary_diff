#include <string>

#include "diff.hh"

Diff::ByteVector
Diff::readFile( std::string_view filename)
{
    std::ifstream file( filename, std::ios_base::binary);

    file.seekg( 0, std::ios_base::end);
    size_t length = file.tellg();
    file.seekg( 0, std::ios_base::beg);

    std::vector<uint8_t> buffer;
    buffer.reserve( length);
    std::copy( std::istreambuf_iterator<char>( file),
                std::istreambuf_iterator<char>(),
                std::back_inserter(buffer) );
    return buffer;
}

std::string
Diff::dump() const
{
    return "orig: " + std::string( (char*)orig_.data(), orig_.size()) + "\n"
           "new: " + std::string( (char*)new_.data(), new_.size());
}
