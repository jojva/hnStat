#include "Distinct.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

CDistinct::CDistinct(void)
{
}

CDistinct::~CDistinct(void)
{
}

bool CDistinct::ParseCommandLine(int argc, char* argv[])
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

void CDistinct::Run(void)
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
