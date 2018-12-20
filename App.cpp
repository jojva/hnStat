#include "App.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

CApp::CApp(int argc, char* argv[])
    : mbParseOk (true)
    , mSubcommand (SubcommandNone)
    , mInputFile ()
    , mNbTopQueries (-1)
    , mFrom (-1)
    , mTo (-1)
{
    if (argc < 2)
    {
        mbParseOk = false;
    }
    else
    {
        std::string Command = argv[1];
        if (Command == "distinct")
        {
            mSubcommand = SubcommandDistinct;
            mbParseOk = ParseSubcommandDistinct(argc, argv);
        }
        else if (Command == "top")
        {
            mSubcommand = SubcommandTop;
            mbParseOk = ParseSubcommandTop(argc, argv);
        }
        else
        {
            mbParseOk = false;
        }
    }
}

CApp::~CApp(void)
{
}

bool CApp::IsParseOk(void)
{
    return mbParseOk;
}

bool CApp::Run(void)
{
    // TODO
    std::cout << "Running with: " << std::endl;
    std::cout << "\tmbParseOk: " << mbParseOk << std::endl;
    std::cout << "\tmSubcommand: " << mSubcommand << std::endl;
    std::cout << "\tmInputFile: " << mInputFile << std::endl;
    std::cout << "\tmNbTopQueries: " << mNbTopQueries << std::endl;
    std::cout << "\tmFrom: " << mFrom << std::endl;
    std::cout << "\tmTo: " << mTo << std::endl;

    switch (mSubcommand)
    {
        case SubcommandDistinct:
            RunDistinct();
            break;
        case SubcommandTop:
            RunTop();
            break;
        case SubcommandNone:
        default:
            break;
    }

    return true;
}

void CApp::RunDistinct(void)
{
    std::ifstream File(mInputFile);
    int Timestamp;
    std::string SearchString;

    // 0° Dumb vector-filling (only for benchmark reference)
    // std::vector<std::string> Queries;
    // while (File >> Timestamp >> SearchString)
    // {
    //     Queries.push_back(SearchString);
    // }

    // 1° Fill a vector with everything, then sort, then eliminate duplicates
    // std::vector<std::string> Queries;
    // while (File >> Timestamp >> SearchString)
    // {
    //     Queries.push_back(SearchString);
    // }
    // std::sort(Queries.begin(), Queries.end());
    // Queries.erase(std::unique(Queries.begin(), Queries.end() ), Queries.end());

    // 2° Use an std::set
    // std::set<std::string> Queries;
    // while (File >> Timestamp >> SearchString)
    // {
    //     Queries.insert(SearchString);
    // }

    // 3° Use an std::unordered_set (fastest)
    std::unordered_set<std::string> Queries;
    while (File >> Timestamp >> SearchString)
    {
        Queries.insert(SearchString);
    }

    std::cout << Queries.size() << std::endl;
}

void CApp::RunTop(void)
{
    std::ifstream File(mInputFile);
    int Timestamp;
    std::string SearchString;

    // 1° Use an std::map
    // std::map<std::string, int> Queries;
    // while (File >> Timestamp >> SearchString)
    // {
    //     // This is safe as operator[] value-initializes the occurrence counter to 0 if it doesn't exist
    //     Queries[SearchString]++;
    // }

    // 2° Use an std::unordered_map (fastest)
    std::unordered_map<std::string, int> Queries;
    while (File >> Timestamp >> SearchString)
    {
        // This is safe as operator[] value-initializes the occurrence counter to 0 if it doesn't exist
        Queries[SearchString]++;
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

bool CApp::ParseSubcommandDistinct(int argc, char* argv[])
{
    // TODO: ParseSubcommandDistinct and ParseSubcommandTop are almost the same, refactor
    for (int Index = 2; Index < argc; Index++)
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
            // TODO: check that argc is big enough
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

bool CApp::ParseSubcommandTop(int argc, char* argv[])
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
