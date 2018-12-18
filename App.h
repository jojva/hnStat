class CApp
{
public:
    bool ParseCommandLine(int argc, char* argv[]);
    bool Run(void);

private:
    bool ParseSubcommandDistinct(int argc, char* argv[]);
    bool ParseSubcommandTop(int argc, char* argv[]);
};
