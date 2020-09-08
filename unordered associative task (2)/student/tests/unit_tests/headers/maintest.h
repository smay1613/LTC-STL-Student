#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "impl.h"
#include <experimental/filesystem>
#include <fstream>

namespace fs = std::experimental::filesystem;

template<int Files>
class NFiles : public ::testing::Test
{
protected:
    std::array<std::ofstream, Files> files;
    void SetUp() override
    {
        std::error_code success;
        fs::create_directory("sandbox", success);
        for (size_t i = 0; i < files.size(); i++)
        {
            files.at(i).open("sandbox/file" + std::to_string(i) + ".txt");
        }
    }

    void TearDown() override
    {
        std::error_code success;
        for (size_t i = 0; i < files.size(); i++)
        {
            fs::remove("sandbox/file" + std::to_string(i) + ".txt");
        }
        fs::remove("sandbox", success);
    }
};

class ThreeFiles : public NFiles<3>
{
};

class NineFiles : public NFiles<9>
{
};

class TwoFolders : public ::testing::Test
{
protected:
    std::array<std::ofstream, 4> files;
    void SetUp() override
    {
        std::error_code success;
        fs::create_directory("sandbox", success);
        fs::create_directory("sandbox/sandbox1", success);
        fs::create_directory("sandbox/sandbox2", success);
        for (size_t i = 0; i < files.size(); i++)
        {
            files.at(i).open("sandbox/sandbox" + std::to_string((i % 2) + 1) +"/file" + std::to_string(i) + ".txt");
        }
    }

    void TearDown() override
    {
        std::error_code success;
        for (size_t i = 0; i < files.size(); i++)
        {
            fs::remove("sandbox/sandbox" + std::to_string((i % 2) + 1) + "/file" + std::to_string(i) + ".txt");

        }
        fs::remove("sandbox/sandbox1", success);
        fs::remove("sandbox/sandbox2", success);
        fs::remove("sandbox", success);
    }
};

