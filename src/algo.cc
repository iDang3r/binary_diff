#include <iostream>

#include "algo.hh"
#include "useful.hh"

void
LCS::process()
{
    for ( int i = 0; i < a_.size(); i++ )
    {
        lcs_[i][0] = 0;
    }
    for ( int j = 0; j < b_.size(); j++ )
    {
        lcs_[0][j] = 0;
    }

    for ( int i = 1; i <= a_.size(); i++ )
    {
        for ( int j = 1; j <= b_.size(); j++ )
        {
            if ( a_[i - 1] == b_[j - 1] )
            {
                lcs_[i][j] = lcs_[i - 1][j - 1] + 1;
            } else
            {
                lcs_[i][j] = std::max( lcs_[i - 1][j], lcs_[i][j - 1]);
            }
        }
    }
}

void
LCS::getAnswer( int i, int j, ByteVector &curr, std::vector<bool> &saved_a, std::vector<bool> &saved_b) const
{
    if ( i == 0 || j == 0 )
    {
        while ( i --> 0 )
        {
            saved_a.push_back( 0);
        }
        while ( j --> 0 )
        {
            saved_b.push_back( 0);
        }
        return;
    }
    if ( a_[i - 1] == b_[j - 1] )
    {
        saved_a.push_back( 1);
        saved_b.push_back( 1);
        i--; j--;
        curr.push_back( a_[i]);
    } else if ( lcs_[i - 1][j] == lcs_[i][j] )
    {
        saved_a.push_back( 0);
        i--;
    } else
    {
        saved_b.push_back( 0);
        j--;
    }
    getAnswer( i, j, curr, saved_a, saved_b);
}
