#include "Top.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

CTop::CTop(void)
    : mInputFile ()
    , mNbTopQueries (-1)
    , mFrom (-1)
    , mTo (-1)
{
}

CTop::~CTop(void)
{
}

bool CTop::ParseCommandLine(int argc, char* argv[])
{
    // TODO: check that argc is big enough
    std::string NbTopQueries = argv[2];
    // TODO: try/catch
    mNbTopQueries = stoi(NbTopQueries);
    for (int Index = 3; Index < argc; Index++)
    {
        std::string Argument = argv[Index];
        if (Argument == "--from")
        {
            Index++;
            // TODO check that argc is big enough
            std::string Value = argv[Index];
            // TODO: try/catch
            mFrom = stoi(Value);
        }
        else if (Argument == "--to")
        {
            Index++;
            // TODO check that argc is big enough
            std::string Value = argv[Index];
            // TODO: try/catch
            mTo = stoi(Value);
        }
        else
        {
            mInputFile = argv[Index];
        }
    }
    // TODO: return false if parsing goes wrong anywhere
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

    std::map<std::string, int> Queries;
    try
    {
        while (std::getline(File, Timestamp, '\t')
            && std::getline(File, SearchString, '\n'))
        {
            // This is safe as operator[] value-initializes the occurrence counter to 0 if it doesn't exist
            Queries[SearchString]++;
        }
    }
    catch (...)
    {
        std::cerr << "Error reading file" << std::endl;
        return;
    }

    // Copy the map into a vector for later sorting
    std::vector<std::pair<std::string, int>> Results;
    for (auto itQuery: Queries)
    {
        Results.push_back(itQuery);
    }

    // Describe the sorting compare function, then actually sort the queries
    auto QuerySorter = [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) -> bool
    {
       return a.second > b.second;
    };
    // TODO: Is "Results.begin() + mNbTopQueries" safe?
    std::partial_sort(Results.begin(), Results.begin() + mNbTopQueries, Results.end(), QuerySorter);

    int Count = 0;
    for (auto itResult: Results)
    {
        Count++;
        std::cout << itResult.second << " " << itResult.first << std::endl;
        if (Count == mNbTopQueries)
        {
            break;
        }
    }
}

void CTop::RunUnorderedMap(std::ifstream& File)
{
    std::string Timestamp;
    std::string SearchString;

    std::unordered_map<std::string, int> Queries;
    try
    {
        while (std::getline(File, Timestamp, '\t')
            && std::getline(File, SearchString, '\n'))
        {
            // This is safe as operator[] value-initializes the occurrence counter to 0 if it doesn't exist
            Queries[SearchString]++;
        }
    }
    catch (...)
    {
        std::cerr << "Error reading file" << std::endl;
        return;
    }

    // Copy the unordered_map into a vector for later sorting
    std::vector<std::pair<std::string, int>> Results;
    for (auto itQuery: Queries)
    {
        Results.push_back(itQuery);
    }

    // Describe the sorting compare function, then actually sort the queries
    auto QuerySorter = [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) -> bool
    {
       return a.second > b.second;
    };
    // TODO: Is "Results.begin() + mNbTopQueries" safe?
    std::partial_sort(Results.begin(), Results.begin() + mNbTopQueries, Results.end(), QuerySorter);

    int Count = 0;
    for (auto itResult: Results)
    {
        Count++;
        std::cout << itResult.second << " " << itResult.first << std::endl;
        if (Count == mNbTopQueries)
        {
            break;
        }
    }
}
