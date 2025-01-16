#include <fstream>
#include <iostream>

#include "useful.hh"

ByteVector
readFile( std::string_view filename)
{
    std::ifstream file( std::string(filename), std::ios_base::binary);
    if ( !file.is_open())
    {
        std::cerr << "Could not open file " << filename << std::endl;
        exit( 1);
    }

    file.seekg( 0, std::ios_base::end);
    size_t length = file.tellg();
    file.seekg( 0, std::ios_base::beg);

    ByteVector buffer;
    buffer.reserve( length);
    std::copy( std::istreambuf_iterator<char>( file),
               std::istreambuf_iterator<char>(),
               std::back_inserter(buffer) );
    
    return buffer;
}
