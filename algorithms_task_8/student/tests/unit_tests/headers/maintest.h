#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <vector>
#include "impl.h"

struct CvInfo
{
    std::string cv;
    skillMatrix expectedMatrix;
    CVGroup expectedCVType;
};

class SkillsMatrix : public ::testing::TestWithParam<CvInfo>
{
public:
    void SetUp() override
    {
    }
protected:
    keywords cppGroupKeywords {
        "GTest", "C++",
        "Qt", "STL", "CMake", "Boost", "C++11",
        "C++14", "C"
    };
    keywords javaKeyWords {
        "JSP", "Spring", "Java",
        "JVM", "Struts", "J2ME", "J2SE"
    };
    keywords generalDeveloperKeywords {
        "SQL", "Database", "Unit",
        "Review", "Development", "IPC",
        "Requirement", "Developer"
    };
    skillMatrix mainSkillMatrix {{CVGroup::CPP, cppGroupKeywords},
                                 {CVGroup::Java, javaKeyWords},
                                 {CVGroup::GeneralDev, generalDeveloperKeywords}};
};
