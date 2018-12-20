#ifndef TOP_H
#define TOP_H

#include "ISubcommand.h"

#include <string>

class CTop: public ISubcommand
{
public:
    CTop(void);
    virtual ~CTop(void);

    virtual bool ParseCommandLine(int argc, char* argv[]) override final;
    virtual void Run(void) override final;

private:
    std::string mInputFile;
    int mNbTopQueries;
    int mFrom;
    int mTo;
};

#endif
