#include <string>

enum ESubcommand
{
    SubcommandNone,
    SubcommandDistinct,
    SubcommandTop,
};

class CApp
{
public:
    CApp(int argc, char* argv[]);
    ~CApp();

    bool IsParseOk(void);
    bool Run(void);

private:
    void RunDistinct(void);
    void RunTop(void);

    bool ParseSubcommandDistinct(int argc, char* argv[]);
    bool ParseSubcommandTop(int argc, char* argv[]);

    bool mbParseOk;
    ESubcommand mSubcommand;
    std::string mInputFile;
    int mNbTopQueries;
    int mFrom;
    int mTo;
};
