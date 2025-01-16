#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <fcntl.h>
#include <unistd.h>
#include <algorithm>

constexpr int size_orig = 10'000;
constexpr int size_new = 18'000;
constexpr int patch_size = 5'000;

#define NAME_ORIG    "test1"
#define NAME_NEW     "test2"
#define NAME_PATCH   "test_patch"
#define NAME_PATCHED "test3"

void dump_array( const char* filename, void* array, int size)
{
    FILE* file = fopen( filename, "wb");
    if ( !file )
    {
        exit(1);
    }
    fwrite( array, 1, size, file);
    fclose( file);
}

void read_array( const char* filename, void* array, int size)
{
    FILE* file = fopen( filename, "rb");
    if ( !file )
    {
        exit(1);
    }
    fread( array, 1, size, file);
    fclose( file);
}

void call_ar_diff( const char* const args[])
{
    pid_t parent = getpid();
    pid_t pid = fork();

    if ( pid == -1 )
    {
        exit( 4);
    } 
    else if ( pid > 0 )
    {
        int status;
        waitpid( pid, &status, 0);
    }
    else
    {
        execv( "./ar_diff", (char* const*)args);
        perror( "ERROR");
        exit( 1);
    }
}

int main()
{
    srand(time(0));
    uint8_t array_orig[size_orig];
    uint8_t array_new[size_new];

    for ( int i = 0; i < size_orig; ++i )
    {
        array_orig[i] = rand() & UINT8_MAX;
    }
    dump_array( NAME_ORIG, array_orig, size_orig);

    int from = std::max( 0, size_orig / 2 - size_new / 2);
    int to = std::min( size_new, size_orig);
    for ( int i = 0; i < size_new; ++i )
    {
        if ( from <= i && i <= to )
        {
            array_new[i] = array_orig[i];
        } else
        {
            array_new[i] = rand() & UINT8_MAX;
        }
    }
    for ( int i = 0; i < patch_size; ++i)
    {
        array_new[rand() % size_new] = rand() & UINT8_MAX;
    }
    dump_array( NAME_NEW, array_new, size_new);

    const char* const args1[] = {"ar_diff", NAME_ORIG, NAME_NEW, "-o", NAME_PATCH, NULL};
    call_ar_diff( args1);
    
    const char* const args2[] = {"ar_diff", NAME_ORIG, "-p", NAME_PATCH, "-o", NAME_PATCHED, NULL};
    call_ar_diff( args2);

    uint8_t array_really_new[size_new];
    read_array( NAME_NEW, array_really_new, size_new);
    
    uint8_t array_patched[size_new];
    read_array( NAME_PATCHED, array_patched, size_new);

    for ( int i = 0; i < size_new; ++i )
    {
        if ( array_really_new[i] != array_patched[i] )
        {
            printf( "Test failed\n");
            return 1;
        }
    }
    
    printf( "Test passed\n");
    return 0;
}
