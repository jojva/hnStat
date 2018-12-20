#ifndef ISUBCOMMAND_H
#define ISUBCOMMAND_H

class ISubcommand
{
public:
    virtual bool ParseCommandLine(int argc, char* argv[]) = 0;
    virtual void Run(void) = 0;
};

#endif
