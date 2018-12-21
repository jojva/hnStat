#include "Distinct.h"

#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

CDistinct::CDistinct(void)
    : mInputFile()
    , mFrom(0)
    , mTo(std::numeric_limits<unsigned long>::max())
{
}

CDistinct::~CDistinct(void)
{
}

bool CDistinct::ParseCommandLine(int argc, char* argv[])
{
    try
    {
        for (int Index = 2; Index < argc; Index++)
        {
            std::string Argument = argv[Index];
            if (Argument == "--from")
            {
                Index++;
                std::string Value = argv[Index];
                mFrom = stoul(Value);
            }
            else if (Argument == "--to")
            {
                Index++;
                std::string Value = argv[Index];
                mTo = stoul(Value);
            }
            else
            {
                mInputFile = argv[Index];
            }
        }
    }
    catch (...)
    {
        return false;
    }
    return true;
}

void CDistinct::Run(void)
{
    std::ifstream File(mInputFile);

    if (File.is_open())
    {
        // Dumb vector-filling without eliminating duplicates (only for benchmark reference)
        // RunVectorDuplicates(File);

        // Fill a vector with everything, then sort, then eliminate duplicates
        // RunVectorUnique(File);

        // Use an std::set
        // RunSet(File);

        // Use an std::unordered_set (fastest)
        RunUnorderedSet(File);
    }
    else
    {
        std::cerr << "Could not open input file" << std::endl;
    }
}

void CDistinct::RunVectorDuplicates(std::ifstream& File)
{
    std::string Timestamp;
    std::string SearchString;

    std::vector<std::string> Queries;
    try
    {
        while (std::getline(File, Timestamp, '\t')
            && std::getline(File, SearchString, '\n'))
        {
            unsigned long ParsedTimestamp = stoul(Timestamp);
            if (ParsedTimestamp >= mFrom && ParsedTimestamp <= mTo)
            {
                Queries.push_back(SearchString);
            }
        }
    }
    catch (...)
    {
        std::cerr << "Error reading file" << std::endl;
        return;
    }

    std::cout << Queries.size() << std::endl;
}

void CDistinct::RunVectorUnique(std::ifstream& File)
{
    std::string Timestamp;
    std::string SearchString;

    std::vector<std::string> Queries;
    try
    {
        while (std::getline(File, Timestamp, '\t')
            && std::getline(File, SearchString, '\n'))
        {
            unsigned long ParsedTimestamp = stoul(Timestamp);
            if (ParsedTimestamp >= mFrom && ParsedTimestamp <= mTo)
            {
                Queries.push_back(SearchString);
            }
        }
    }
    catch (...)
    {
        std::cerr << "Error reading file" << std::endl;
        return;
    }
    std::sort(Queries.begin(), Queries.end());
    Queries.erase(std::unique(Queries.begin(), Queries.end() ), Queries.end());

    std::cout << Queries.size() << std::endl;
}

void CDistinct::RunSet(std::ifstream& File)
{
    std::string Timestamp;
    std::string SearchString;

    std::set<std::string> Queries;
    try
    {
        while (std::getline(File, Timestamp, '\t')
            && std::getline(File, SearchString, '\n'))
        {
            unsigned long ParsedTimestamp = stoul(Timestamp);
            if (ParsedTimestamp >= mFrom && ParsedTimestamp <= mTo)
            {
                Queries.insert(SearchString);
            }
        }
    }
    catch (...)
    {
        std::cerr << "Error reading file" << std::endl;
        return;
    }

    std::cout << Queries.size() << std::endl;
}

void CDistinct::RunUnorderedSet(std::ifstream& File)
{
    std::string Timestamp;
    std::string SearchString;

    std::unordered_set<std::string> Queries;
    try
    {
        while (std::getline(File, Timestamp, '\t')
            && std::getline(File, SearchString, '\n'))
        {
            unsigned long ParsedTimestamp = stoul(Timestamp);
            if (ParsedTimestamp >= mFrom && ParsedTimestamp <= mTo)
            {
                Queries.insert(SearchString);
            }
        }
    }
    catch (...)
    {
        std::cerr << "Error reading file" << std::endl;
        return;
    }

    std::cout << Queries.size() << std::endl;
}
