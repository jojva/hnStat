#include "App.h"

#include <iostream>

CApp::CApp(int argc, char* argv[])
    : mbParseOk (true)
    , mSubcommand (SubcommandNone)
    , mInputFile ()
    , mNbTopQueries (-1)
    , mFrom (-1)
    , mTo (-1)
{
    if (argc < 2)
    {
        mbParseOk = false;
    }
    else
    {
        std::string Command = argv[1];
        if (Command == "distinct")
        {
            mSubcommand = SubcommandDistinct;
            mbParseOk = ParseSubcommandDistinct(argc, argv);
        }
        else if (Command == "top")
        {
            mSubcommand = SubcommandTop;
            mbParseOk = ParseSubcommandTop(argc, argv);
        }
        else
        {
            mbParseOk = false;
        }
    }
}

CApp::~CApp(void)
{
}

bool CApp::IsParseOk(void)
{
    return mbParseOk;
}

bool CApp::Run(void)
{
    // TODO
    std::cout << "Running with: " << std::endl;
    std::cout << "\tmbParseOk: " << mbParseOk << std::endl;
    std::cout << "\tmSubcommand: " << mSubcommand << std::endl;
    std::cout << "\tmInputFile: " << mInputFile << std::endl;
    std::cout << "\tmNbTopQueries: " << mNbTopQueries << std::endl;
    std::cout << "\tmFrom: " << mFrom << std::endl;
    std::cout << "\tmTo: " << mTo << std::endl;
    
    return true;
}

bool CApp::ParseSubcommandDistinct(int argc, char* argv[])
{
    // TODO: ParseSubcommandDistinct and ParseSubcommandTop are almost the same, refactor
    for (int Index = 2; Index < argc; Index++)
    {
        std::string Argument = argv[Index];
        if (Argument == "--from")
        {
            Index++;
            // TODO check that argc is big enough
            std::string Value = argv[Index];
            // TODO: try/catch
            mFrom = stoi(Value);
        }
        else if (Argument == "--to")
        {
            Index++;
            // TODO: check that argc is big enough
            std::string Value = argv[Index];
            // TODO: try/catch
            mTo = stoi(Value);
        }
        else
        {
            mInputFile = argv[Index];
        }
    }
    // TODO: return false if parsing goes wrong anywhere
    return true;
}

bool CApp::ParseSubcommandTop(int argc, char* argv[])
{
    // TODO: check that argc is big enough
    std::string NbTopQueries = argv[2];
    // TODO: try/catch
    mNbTopQueries = stoi(NbTopQueries);
    for (int Index = 3; Index < argc; Index++)
    {
        std::string Argument = argv[Index];
        if (Argument == "--from")
        {
            Index++;
            // TODO check that argc is big enough
            std::string Value = argv[Index];
            // TODO: try/catch
            mFrom = stoi(Value);
        }
        else if (Argument == "--to")
        {
            Index++;
            // TODO check that argc is big enough
            std::string Value = argv[Index];
            // TODO: try/catch
            mTo = stoi(Value);
        }
        else
        {
            mInputFile = argv[Index];
        }
    }
    // TODO: return false if parsing goes wrong anywhere
    return true;
}
