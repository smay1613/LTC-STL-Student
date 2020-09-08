#include "maintest.h"

using namespace ::testing;


TEST_F(SkillsMatrix, Empty)
{
    skillMatrix matrix {buildSkillsMatrix({}, mainSkillMatrix)};
    EXPECT_FALSE(matrix.empty());
    EXPECT_TRUE(std::all_of(matrix.begin(), matrix.end(),
                            [](const std::pair<CVGroup, keywords>& row) {
                                return row.second.empty();
                            }
                            )
                );
    auto ratio = getGroupsRelation(mainSkillMatrix, matrix);
    auto topGroup = getPossibleCVGroups(ratio);
}

INSTANTIATE_TEST_SUITE_P(JavaTest,
                         SkillsMatrix,
                         testing::Values(CvInfo {
                                             std::string {"KEY SKILLS AND COMPETENCIES "
                                                          "Strong core Java development experience. "
                                                          "Extensive knowledge of JDBC/ ORM Tools and relational databases. "
                                                          "Database: Oracle (TOAD),SQL,MySQL "
                                                          "Software development: Java: J2SE(including Swing), J2ME; Prolog, C,C#. "
                                                          "Experience with application servers and containers as well as development and "
                                                          "integrating web services."},

                                              skillMatrix {{CVGroup::Java, {"J2ME", "Java", "J2SE"}},
                                                           {CVGroup::GeneralDev, {"Database", "development", "SQL"}},
                                                           {CVGroup::CPP, {"C"}}},

                                              CVGroup::Java
                                         }));
INSTANTIATE_TEST_SUITE_P(CppTest,
                         SkillsMatrix,
                         testing::Values(CvInfo {
                                             std::string {"Technical Skills"
                                                          "Languages	C, C++, Assembler, Java, C#, SQL, HTML, CSS, PHP, JavaScript "
                                                          "Libraries and Frameworks "
                                                          "WinAPI, STL, Boost, MFC, ATL, .NET, OLE/COM, Qt, DAO, ADO "
                                                          "Concepts	OOA/OOD (UML, Design Patterns, Refactoring), "
                                                          "Hardware	PCs, PDAs, Peripherals, Network accessories"
                                                          "Databases:SQL, DB2, MS Access Database"},
                                              skillMatrix {{CVGroup::Java, {"Java"}},
                                                           {CVGroup::GeneralDev, {"SQL", "Database"}},
                                                           {CVGroup::CPP, {"C", "C++", "Boost", "Qt", "STL"}}},
                                              CVGroup::CPP
                                         }));
TEST_P(SkillsMatrix, SkillsMatrixText)
{
    const std::string& cvText {GetParam().cv};
    const keywords& processedText {parseText(cvText)};

    const skillMatrix cvSkillMatrix {buildSkillsMatrix(processedText, mainSkillMatrix)};
    EXPECT_EQ(cvSkillMatrix.size(), 3);

    EXPECT_EQ(cvSkillMatrix, GetParam().expectedMatrix);
}

TEST_P(SkillsMatrix, MatrixTopGroups)
{
    const std::string& cvText {GetParam().cv};
    const keywords& processedText {parseText(cvText)};

    const skillMatrix cvSkillMatrix {buildSkillsMatrix(processedText, mainSkillMatrix)};

    const groupsRatio ratio {getGroupsRelation(mainSkillMatrix, cvSkillMatrix)};
    auto topGroups = getPossibleCVGroups(ratio);

    auto equalsExpected = [&](const CVGroup group) {
        return group == GetParam().expectedCVType;
    };

    EXPECT_TRUE(std::any_of(topGroups.begin(), topGroups.end(),
                            equalsExpected));
}
