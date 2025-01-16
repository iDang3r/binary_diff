#include <cstdio>
#include <iostream>
#include <string>

#include "diff.hh"
#include "algo.hh"

void
Diff::process()
{
    LCS lcs( orig_, new_);
    lcs.process();

    auto [saved_orig, saved_new] = lcs.getAnswer();
    saved_orig_ = saved_orig;
    saved_new_ = saved_new;
}

std::string
Diff::getDiff() const
{
    std::string diff;
    int i = 0, j = 0;
    int skip = 0;

    while ( i < orig_.size() && j < orig_.size() )
    {
        if ( saved_orig_[i] && saved_new_[j] )
        {
            i++; j++; skip++;
            continue;
        }
        if ( !saved_orig_[i] )
        {
            if ( skip )
            {
                diff += std::to_string( skip) + "\n";
                skip = 0;
            }
            diff += std::string("< ") + (char)orig_[i] + "\n";
            i++;
            continue;
        }
        if ( !saved_new_[j] )
        {
            if ( skip )
            {
                diff += std::to_string( skip) + "\n";
                skip = 0;
            }
            diff += std::string("> ") + (char)new_[j] + "\n";
            j++;
            continue;
        }
        assert( !"Unreachable");
    }
    
    if ( skip )
    {
        diff += std::to_string( skip) + "\n";
        skip = 0;
    }
    while ( i < orig_.size() )
    {
        diff += std::string("< ") + (char)orig_[i] + "\n";
        i++;
    }
    while ( j < new_.size() )
    {
        diff += std::string("> ") + (char)new_[j] + "\n";
        j++;
    }

    return diff;
}

std::string
Diff::dump() const
{
    for ( int i = 0; i < saved_orig_.size(); ++i )
    {
        std::cout << saved_orig_[i];
    }
    std::cout << std::endl;

    for ( int i = 0; i < saved_new_.size(); ++i )
    {
        std::cout << saved_new_[i];
    }
    std::cout << std::endl;

    return "orig: " + ::dump( orig_) + "\n"
           "new:  " + ::dump( new_);
}
