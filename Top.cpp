#include "Top.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

CTop::CTop(void)
    : mInputFile ()
    , mNbTopQueries (0)
    , mFrom (0)
    , mTo (std::numeric_limits<unsigned long>::max())
{
}

CTop::~CTop(void)
{
}

bool CTop::ParseCommandLine(int argc, char* argv[])
{
    std::string NbTopQueries = argv[2];
    try
    {
        mNbTopQueries = stoi(NbTopQueries);
        for (int Index = 3; Index < argc; Index++)
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

void CTop::Run(void)
{
    std::ifstream File(mInputFile);
    std::string Timestamp;
    std::string SearchString;

    if (File.is_open())
    {
        // Use an std::map
        // RunMap(File);

        // Use an std::unordered_map
        RunUnorderedMap(File);
    }
    else
    {
        std::cerr << "Could not open input file" << std::endl;
    }
}

void CTop::RunMap(std::ifstream& File)
{
    std::string Timestamp;
    std::string SearchString;

    std::map<std::string, unsigned int> Queries;
    try
    {
        while (std::getline(File, Timestamp, '\t')
            && std::getline(File, SearchString, '\n'))
        {
            unsigned long ParsedTimestamp = stoul(Timestamp);
            if (ParsedTimestamp >= mFrom && ParsedTimestamp <= mTo)
            {
                // This is safe as operator[] value-initializes the occurrence counter to 0 if it doesn't exist
                Queries[SearchString]++;
            }
        }
    }
    catch (...)
    {
        std::cerr << "Error reading file" << std::endl;
        return;
    }

    // Copy the map into a vector for sorting
    std::vector<std::pair<std::string, unsigned int>> Results;
    unsigned int MinOccurrence = 0;
    for (auto itQuery: Queries)
    {
        if (itQuery.second > MinOccurrence)
        {
            Results.emplace_back(itQuery);
            std::sort(Results.begin(), Results.end(), [](auto Left, auto Right){return Left.second > Right.second;});
            if (Results.size() > mNbTopQueries)
            {
                Results.pop_back();
                MinOccurrence = Results.back().second;
            }
        }
    }
    for (auto itResult: Results)
    {
        std::cout << itResult.second << " " << itResult.first << std::endl;
    }
}

void CTop::RunUnorderedMap(std::ifstream& File)
{
    std::string Timestamp;
    std::string SearchString;

    std::unordered_map<std::string, unsigned int> Queries;
    try
    {
        while (std::getline(File, Timestamp, '\t')
            && std::getline(File, SearchString, '\n'))
        {
            unsigned long ParsedTimestamp = stoul(Timestamp);
            if (ParsedTimestamp >= mFrom && ParsedTimestamp <= mTo)
            {
                // This is safe as operator[] value-initializes the occurrence counter to 0 if it doesn't exist
                Queries[SearchString]++;
            }
        }
    }
    catch (...)
    {
        std::cerr << "Error reading file" << std::endl;
        return;
    }

    // Copy the unordered_map into a vector for sorting
    std::vector<std::pair<std::string, unsigned int>> Results;
    unsigned int MinOccurrence = 0;
    for (auto itQuery: Queries)
    {
        if (itQuery.second > MinOccurrence)
        {
            Results.emplace_back(itQuery);
            std::sort(Results.begin(), Results.end(), [](auto Left, auto Right){return Left.second > Right.second;});
            if (Results.size() > mNbTopQueries)
            {
                Results.pop_back();
                MinOccurrence = Results.back().second;
            }
        }
    }
    for (auto itResult: Results)
    {
        std::cout << itResult.second << " " << itResult.first << std::endl;
    }
}
