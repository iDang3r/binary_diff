#include <cstdio>
#include <iostream>
#include <ostream>
#include <string>

#include "diff.hh"
#include "patch.hh"
#include "useful.hh"

struct Args
{
    std::string orig_filename;
    std::string other_filename;
    std::string output;
    bool help = false;
    bool patch = false;
} args;

std::string getHelp()
{
    return "Usage: ar_diff <original> <new>\n"
           "       ar_diff <original> <patch> -p";
}

void parseArgs( int argc, char* argv[])
{
    std::vector<std::string_view> arguments = { argv + 1, argv + argc};
    std::vector<std::string> files;
    for ( int i = 0; i < arguments.size(); ++i )
    {
        if ( arguments[i] == "--help" || arguments[i] == "-h" )
        {
            args.help = true;
            return;
        }
        if ( arguments[i] == "--patch" || arguments[i] == "-p" )
        {
            args.patch = true;
            continue;
        }
        if ( arguments[i] == "--output" || arguments[i] == "-o" )
        {
            args.output = arguments[++i];
            continue;
        }
        if ( arguments[i].front() == '-' )
        {
            std::cerr << "Unknown option\n";
            exit(1);
        }
        files.push_back( std::string( arguments[i]));
    }
    if ( files.size() != 2 )
    {
        std::cerr << "Invalid arguments" << std::endl;
        args.help = true;
        return;
    }
    args.orig_filename = files[0];
    args.other_filename = files[1];
}

int main( int argc, char* argv[])
{
    parseArgs( argc, argv);

    if ( args.help )
    {
        std::cout << getHelp() << std::endl;
        return 17;
    }

    if ( !args.output.empty() )
    {
        freopen( args.output.c_str(), "w", stdout);
    }
    
    if ( !args.patch )
    {
        Diff diff( args.orig_filename, args.other_filename);
        diff.process();

        std::cout << diff.getDiff();
    } else
    {
        Patch patch( args.orig_filename, args.other_filename);
        patch.process();

        ByteVector res = patch.getPatched();

        for ( auto& c : res )
        {
            std::cout << c;
        }
    }
    return 0;
}