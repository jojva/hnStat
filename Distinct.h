#ifndef DISTINCT_H
#define DISTINCT_H

#include "ISubcommand.h"

#include <fstream>
#include <string>

class CDistinct: public ISubcommand
{
public:
    CDistinct(void);
    virtual ~CDistinct(void);

    virtual bool ParseCommandLine(int argc, char* argv[]) override final;
    virtual void Run(void) override final;

private:
    void RunVectorDuplicates(std::ifstream& File);
    void RunVectorUnique(std::ifstream& File);
    void RunSet(std::ifstream& File);
    void RunUnorderedSet(std::ifstream& File);

private:
    std::string mInputFile;
    int mFrom;
    int mTo;
};

#endif
