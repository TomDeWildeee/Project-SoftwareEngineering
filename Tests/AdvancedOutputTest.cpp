#include "gtest/gtest.h"
#include "../PrintingSystem.h"
#include "../PrintingSystemImporter.h"
#include "../Utils.h"

using namespace std;
class AdvancedOutputTest: public ::testing::Test{
protected:
    void SetUp() override{
    }
    void TearDown() override {
    }
    PrintingSystem printsystem;
};

string happydayAdvancedOutputDir = "testXMLs/AdvancedOutputTests/AdvancedOutputHappyDay";

TEST_F(AdvancedOutputTest, HappyDayAdvancedOutput) {
    ASSERT_TRUE(DirectoryExists(happydayAdvancedOutputDir));
    int counter = 1;
    string filename = happydayAdvancedOutputDir + "/advancedOutputTest" + ToString(counter) + ".xml";
    string outputFileName;
    while(FileExists(filename)){
        FileOutputStream errStream = FileOutputStream(happydayAdvancedOutputDir + "/outputXML.txt");
        PrintingSystemImporter::importPrintingSystem(filename.c_str(),&errStream,printsystem);
        NoOutputStream n;
        if (counter == 3) {
            printsystem.processJob(&n, printsystem.getJobs()[0]->getJobNR());
            printsystem.processJob(&n, printsystem.getJobs()[1]->getJobNR());
        } else {
            printsystem.processAllJobsAutomatically(&n);
        }

        printsystem.advancedOutput(&errStream);

        outputFileName = happydayAdvancedOutputDir + "/advancedOutputTest" + ToString(counter) + ".txt";
        EXPECT_TRUE(FileCompare(happydayAdvancedOutputDir + "/outputXML.txt", outputFileName));
        counter += 1;
        filename = happydayAdvancedOutputDir + "/advancedOutputTest" + ToString(counter) + ".xml";
        printsystem.clearSystemBecauseInvalid();
    }
    EXPECT_TRUE(counter == 4);
}

// string invalidOutputAPDir = "testXMLs/AutomaticallyProcessTests/InvalidOutputTest";

/*
TEST_F(A, InvalidOutput) {
    ASSERT_TRUE(DirectoryExists(invalidOutputAPDir));
    int counter = 1;
    string filename = invalidOutputAPDir + "/invalidoutput" + ToString(counter) + ".xml";
    string outputFileName;
    while(FileExists(filename)){
        FileOutputStream errStream = FileOutputStream(invalidOutputAPDir + "/outputXML.txt");
        PrintingSystemImporter::importPrintingSystem(filename.c_str(),&errStream,printsystem);

        FileOutputStream fileOutputStream = FileOutputStream(invalidOutputAPDir + "/outputXML.txt");
        printsystem.processAllJobsAutomatically(&fileOutputStream);
        outputFileName = invalidOutputAPDir + "/invalidoutput" + ToString(counter) + ".txt";
        EXPECT_FALSE(FileCompare(invalidOutputAPDir + "/outputXML.txt", outputFileName));
        counter +=1;
        filename = invalidOutputAPDir + "/invalidoutput" + ToString(counter) + ".xml";
        printsystem.clearSystemBecauseInvalid();
    }
    EXPECT_TRUE(counter == 2);
}
*/