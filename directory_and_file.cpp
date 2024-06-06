#include "directory_and_file.h"
int main()
{
    auto dirRoot = Directory("Dir:/");
    auto dirA = dirRoot.AddData(std::make_unique<Directory>("Dir:/A/"));
    auto dirAA = dirA->AddData(std::make_unique<Directory>("Dir:/A/A/"));
    auto dirAB = dirAA->AddData(std::make_unique<Directory>("Dir:/A/B/"));
    auto dirB = dirRoot.AddData(std::make_unique<Directory>("Dir:/B/"));
    auto dirC = dirRoot.AddData(std::make_unique<Directory>("Dir:/C/"));

    auto file1 = dirRoot.AddData(std::make_unique<File>("File:/1", 1));
    auto fileA1 = dirA->AddData(std::make_unique<File>("File:/A/1", 10));
    auto fileA2 = dirA->AddData(std::make_unique<File>("File:/A/2", 100));
    auto fileAB1 = dirAB->AddData(std::make_unique<File>("File:/A/B/1", 1000));
    auto fileC1 = dirC->AddData(std::make_unique<File>("File:/C/1", 10000));
    auto fileC2 = dirC->AddData(std::make_unique<File>("File:/C/2", 100000));
    auto fileC3 = dirC->AddData(std::make_unique<File>("File:/C/3", 1000000));

    PrintSize(dirRoot);
    std::cout << "------------------" << std::endl;
    PrintSize(*dirA);
    PrintSize(*fileA2);
    RemoveData(*dirA, fileA2);
    PrintSize(*dirA);
    std::cout << "------------------" << std::endl;
    RemoveData(dirRoot, dirA);
    PrintSize(dirRoot);
    std::cout << "------------------" << std::endl;
    PrintSize(*dirB);
    PrintSize(*dirC);
    RemoveData(*dirC, fileC3);
    PrintSize(*dirC);
    std::cout << "------------------" << std::endl;
    RemoveData(dirRoot, fileC1);
    RemoveData(dirRoot, dirC);
    PrintSize(dirRoot);
}
