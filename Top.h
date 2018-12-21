#ifndef TOP_H
#define TOP_H

#include "ISubcommand.h"

#include <fstream>
#include <string>

class CTop: public ISubcommand
{
public:
    CTop(void);
    virtual ~CTop(void);

    virtual bool ParseCommandLine(int argc, char* argv[]) override final;
    virtual void Run(void) override final;

private:
    void RunMap(std::ifstream& File);
    void RunUnorderedMap(std::ifstream& File);

private:
    std::string mInputFile;
    unsigned int mNbTopQueries;
    unsigned int mFrom;
    unsigned int mTo;
};

#endif
