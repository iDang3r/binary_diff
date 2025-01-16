#ifndef ALGO_HH
#define ALGO_HH

#include <stdio.h>
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdio>
#include <vector>

#include "useful.hh"

class LCS
{
private:
    ByteVector a_, b_;
    std::vector<std::vector<Byte>> lcs_;
public:
    LCS( const ByteVector &a, const ByteVector &b)
    :
        a_( a), b_( b)
    {
        lcs_.resize( a.size() + 1);
        for ( size_t i = 0; i < lcs_.size(); i++ )
        {
            lcs_[i].resize( b.size() + 1, Byte( 0));
        }
    }

    void process();

    std::tuple<ByteVector, std::vector<bool>, std::vector<bool>>
    getAnswer() const
    {
        ByteVector ans;
        std::vector<bool> saved_a, saved_b;
        ans.reserve( std::min( a_.size(), b_.size()));
        getAnswer( a_.size(), b_.size(), ans, saved_a, saved_b);
        std::reverse( ans.begin(), ans.end());
        std::reverse( saved_a.begin(), saved_a.end());
        std::reverse( saved_b.begin(), saved_b.end());
        assert( a_.size() == saved_a.size());
        assert( b_.size() == saved_b.size());
        return {ans, saved_a, saved_b};
    }

private:
    void getAnswer( int i, int j, ByteVector &curr, std::vector<bool> &saved_a, std::vector<bool> &saved_b) const;
};

#endif // ALGO_HH
