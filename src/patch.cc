#include <cassert>
#include <cstdio>
#include <iostream>
#include <sstream>

#include "patch.hh"
#include "useful.hh"

void
Patch::process()
{
    if ( !patch_.is_open() )
    {
        std::cerr << "WARNING: Patch has already been processed!\n";
        return;
    }
    patched_.reserve( orig_.size());

    std::string patch_line;
    size_t pos = 0u;
    while ( std::getline( patch_, patch_line) )
    {
        int skip = 0;
        if ( sscanf( patch_line.c_str(), "%d\n", &skip) )
        {
            while ( skip --> 0 )
            {
                patched_.push_back( orig_[pos++]);
            }
            continue;
        }

        char type = patch_line[0];
        Byte byte = (patch_line.size() == 3) ? patch_line[2] : '\n';

        if ( type == '<' )
        {
            if ( byte != orig_[pos] )
            {
                fprintf( stderr, "0x%02x != 0x%02x; on pos %d\n", byte, orig_[pos], (int)pos);
            }
            assert( byte == orig_[pos]);
            pos++;
        } else if ( type == '>' )
        {
            patched_.push_back( byte);
        } else
        {
            assert( !"Unreachable");
        }
    }
}
