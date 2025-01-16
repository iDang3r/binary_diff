#ifndef PATCH_HH
#define PATCH_HH

#include "useful.hh"
#include <fstream>
#include <iostream>

class Patch
{
private:
    ByteVector orig_;
    std::ifstream patch_;

    ByteVector patched_;
public:
    Patch( std::string_view orig_filename, std::string_view patch_filename)
    :
        orig_( readFile( orig_filename)),
        patch_( std::string(patch_filename))
    {
        if ( !patch_.is_open() )
        {
            std::cerr << "Could not open patch file " << patch_filename << std::endl;
            exit( 1);
        }
    }

    ByteVector getPatched() const
    {
        return patched_;
    }

    void process();
};

#endif // PATCH_HH
