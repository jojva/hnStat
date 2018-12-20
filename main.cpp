#include "ISubcommand.h"
#include "Distinct.h"
#include "Top.h"

#include <iostream>

enum ESubcommandType
{
    SubcommandNone,
    SubcommandDistinct,
    SubcommandTop,
};

ESubcommandType ParseSubcommand(int argc, char* argv[])
{
    if (argc < 2)
    {
        return SubcommandNone;
    }
    else
    {
        std::string Command = argv[1];
        if (Command == "distinct")
        {
            return SubcommandDistinct;
        }
        else if (Command == "top")
        {
            return SubcommandTop;
        }
        else
        {
            return SubcommandNone;
        }
    }
}

void Usage(void)
{
    std::cout << "Usage:" << std::endl;
    std::cout << "\ttechtest distinct [--from <timestamp>] [--to <timestamp>] <input_file>" << std::endl;
    std::cout << "\ttechtest top <nb_top_queries> [--from <timestamp>] [--to <timestamp>] <input_file>" << std::endl;
}

void Execute(ISubcommand& subcommand, int argc, char* argv[])
{
    bool bParseOk = subcommand.ParseCommandLine(argc, argv);
    if (bParseOk)
    {
        subcommand.Run();
    }
    else
    {
        Usage();
    }
}

int main(int argc, char* argv[])
{
    switch (ParseSubcommand(argc, argv))
    {
        case SubcommandDistinct:
        {
            CDistinct Distinct;
            Execute(Distinct, argc, argv);
            break;
        }
        case SubcommandTop:
        {
            CTop Top;
            Execute(Top, argc, argv);
            break;
        }
        case SubcommandNone:
        default:
            Usage();
    }
    return 0;
}
