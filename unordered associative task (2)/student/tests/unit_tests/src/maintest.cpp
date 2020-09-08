#include "maintest.h"
#include <experimental/filesystem>

using namespace ::testing;
namespace fs = std::experimental::filesystem;

TEST_F(ThreeFiles, OneGroupThreeFiles)
{
    for (size_t i = 0; i < 3; i++)
    {
        files[i] << "11";
    }

    for (auto& file : files)
    {
        file.close();
    }

    std::vector<std::vector<std::string>> groups {findDuplicates("sandbox")};
    EXPECT_EQ(groups.size(), 1);
    EXPECT_EQ(groups.front().size(), 3);
}

TEST_F(ThreeFiles, ThreeGroupsOneFile)
{
    files[0] << "11";
    files[1] << "12";
    files[2] << "13";

    for (auto& file : files)
    {
        file.close();
    }

    std::vector<std::vector<std::string>> groups {findDuplicates("sandbox")};
    EXPECT_EQ(groups.size(), 0);
}

TEST_F(ThreeFiles, Reversed)
{
    files[0] << "12345";
    files[1] << "54321";
    files[2] << "12345";

    for (auto& file : files)
    {
        file.close();
    }

    std::vector<std::vector<std::string>> groups {findDuplicates("sandbox")};
    EXPECT_EQ(groups.size(), 1);
    EXPECT_EQ(groups.front().size(), 2);
}

TEST_F(TwoFolders, TwoGroups)
{
    files[0] << "111";
    files[1] << "111";
    files[2] << "121";
    files[3] << "121";

    for (auto& file : files)
    {
        file.close();
    }

    std::vector<std::vector<std::string>> groups {findDuplicates("sandbox")};
    EXPECT_EQ(groups.size(), 2);
    EXPECT_EQ(groups.front().size(), 2);
}

TEST_F(NineFiles, ThreeGroupsThreeFiles)
{
    for (size_t i = 0; i < 3; i++)
    {
        files[i] << "abcd";
    }

    for (size_t i = 3; i < 6; i++)
    {
        files[i] << "abcde";
    }

    for (size_t i = 6; i < 9; i++)
    {
        files[i] << "abcdg";
    }

    for (auto& file : files)
    {
        file.close();
    }

    std::vector<std::vector<std::string>> groups {findDuplicates("sandbox")};
    EXPECT_EQ(groups.size(), 3);
    EXPECT_TRUE(std::all_of(groups.begin(), groups.end(),
                          [](const std::vector<std::string>& subgroup) {return subgroup.size() == 3;}));
}
