#include <iostream>

#define UNUSED(expr) do { (void)(expr); } while (0)

bool parse_subcommand_distinct(int argc, char* argv[])
{
    // TODO
    UNUSED(argc);
    UNUSED(argv);
    std::cout << "distinct parser" << std::endl;
    return true;
}

bool parse_subcommand_top(int argc, char* argv[])
{
    // TODO
    UNUSED(argc);
    UNUSED(argv);
    std::cout << "top parser" << std::endl;
    return true;
}

bool parse_command_line(int argc, char* argv[])
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
            bParseOk = parse_subcommand_distinct(argc, argv);
        }
        else if (Command == "top")
        {
            bParseOk = parse_subcommand_top(argc, argv);
        }
        else
        {
            bParseOk = false;
        }
    }

    return bParseOk;
}

void usage(void)
{
    std::cout << "Usage:" << std::endl;
    std::cout << "\ttechtest distinct [--from <timestamp>] [--to <timestamp>] <input_file>" << std::endl;
    std::cout << "\ttechtest top <nb_top_queries> [--from <timestamp>] [--to <timestamp>] <input_file>" << std::endl;
}

int main(int argc, char* argv[])
{
    const bool bParseOk = parse_command_line(argc, argv);
    if (bParseOk)
    {

    }
    else
    {
        usage();
    }

    return 0;
}
