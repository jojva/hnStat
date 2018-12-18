#include "App.h"

#include <iostream>

#define UNUSED(expr) do { (void)(expr); } while (0)

bool CApp::ParseCommandLine(int argc, char* argv[])
{
    bool bParseOk = true;

    if (argc < 2)
    {
        bParseOk = false;
    }
    else
    {
        std::string Command = argv[1];
        if (Command == "distinct")
        {
            bParseOk = ParseSubcommandDistinct(argc, argv);
        }
        else if (Command == "top")
        {
            bParseOk = ParseSubcommandTop(argc, argv);
        }
        else
        {
            bParseOk = false;
        }
    }

    return bParseOk;
}

bool CApp::Run(void)
{
    // TODO
    return true;
}

bool CApp::ParseSubcommandDistinct(int argc, char* argv[])
{
    // TODO
    UNUSED(argc);
    UNUSED(argv);
    std::cout << "distinct parser" << std::endl;
    return true;
}

bool CApp::ParseSubcommandTop(int argc, char* argv[])
{
    // TODO
    UNUSED(argc);
    UNUSED(argv);
    std::cout << "top parser" << std::endl;
    return true;
}

