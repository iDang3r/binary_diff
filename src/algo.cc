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

void
Myers::myers_diff()
{
    std::unordered_map<int, History> history;
    history[1] = {0};

    int a_max = a_.size();
    int b_max = b_.size();

    for ( int d = 0; d <= a_max + b_max; ++d )
    {
        for ( int k = -d; k <= d; k += 2 )
        {
            bool go_down = (k == -d || (k != d && history[k - 1].x < history[k + 1].x));

            History next;
            if ( go_down )
            {
                next = history[k + 1];
            } else
            {
                next = history[k - 1];
                next.x++;
            }

            int y = next.x - k;
            if ( 1 <= y && y <= b_max && go_down )
            {
                next.saved_b.push_back( 0);
            } else if ( 1 <= next.x && next.x <= a_max )
            {
                next.saved_a.push_back( 0);
            }

            while ( next.x < a_max && y < b_max && a_[next.x] == b_[y] )
            {
                next.saved_a.push_back( 1);
                next.saved_b.push_back( 1);
                next.x++; y++;
            }

            if ( next.x >= a_max && y >= b_max )
            {
                saved_a_ = next.saved_a;
                saved_b_ = next.saved_b;
                return;
            }
            
            history[k] = next;
        }
    }
    assert( !"Unreachable");
}
