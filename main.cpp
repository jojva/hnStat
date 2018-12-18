#include "App.h"

#include <iostream>

void usage(void)
{
    std::cout << "Usage:" << std::endl;
    std::cout << "\ttechtest distinct [--from <timestamp>] [--to <timestamp>] <input_file>" << std::endl;
    std::cout << "\ttechtest top <nb_top_queries> [--from <timestamp>] [--to <timestamp>] <input_file>" << std::endl;
}

int main(int argc, char* argv[])
{
    CApp App(argc, argv);
    bool bResult = App.IsParseOk();
    if (bResult)
    {
        bResult = App.Run();
    }
    else
    {
        usage();
    }

    return (bResult ? 0 : 1);
}
