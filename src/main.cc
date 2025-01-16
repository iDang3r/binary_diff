#include "diff.hh"
#include <iostream>
#include <string>

struct Args
{
    std::string orig_filename;
    std::string new_filename;
    bool help = false;
} args;

std::string getHelp()
{
    return "Usage: ar_diff <original> <new>";
}

void parseArgs( int argc, char* argv[])
{
    const std::vector<std::string_view> arguments = { argv + 1, argv + argc};
    for( const auto& argument : arguments)
    {
        if ( argument == "--help" || argument == "-h" )
        {
            args.help = true;
            return;
        }
    }
    if ( arguments.size() != 2 )
    {
        std::cerr << "Invalid arguments" << std::endl;
        args.help = true;
        return;
    }
    args.orig_filename = arguments[0];
    args.new_filename = arguments[1];
}

int main( int argc, char* argv[])
{
    std::cout << std::string( "Hello World ") << std::endl;
    parseArgs( argc, argv);

    if ( args.help )
    {
        std::cout << getHelp() << std::endl;
        return 0;
    }

    Diff diff( args.orig_filename, args.new_filename);

    std::cout << diff.dump() << std::endl;

    return 0;
}