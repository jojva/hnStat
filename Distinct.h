#ifndef DISTINCT_H
#define DISTINCT_H

#include "ISubcommand.h"

#include <string>

class CDistinct: public ISubcommand
{
public:
    CDistinct(void);
    virtual ~CDistinct(void);

    virtual bool ParseCommandLine(int argc, char* argv[]) override final;
    virtual void Run(void) override final;

private:
    std::string mInputFile;
    int mFrom;
    int mTo;
};

#endif
