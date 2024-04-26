#include "gtest/gtest.h"
#include "../PrintingSystem.h"
#include "../PrintingSystemImporter.h"
#include "../Utils.h"

using namespace std;
class AutomaticallyProcessTest: public ::testing::Test{
protected:
    void SetUp() override{
    }
    void TearDown() override {
    }
    PrintingSystem printsystem;
};

string happydayAPDir = "testXMLs/AutomaticallyProcessTests/HappyDayTest";

TEST_F(AutomaticallyProcessTest, HappyDayAP) {
    ASSERT_TRUE(DirectoryExists(happydayAPDir));
    int counter = 1;
    string filename = happydayAPDir + "/aptest" + ToString(counter) + ".xml";
    string outputFileName;
    while(FileExists(filename)){
        FileOutputStream errStream = FileOutputStream(happydayAPDir + "/outputXML.txt");
        PrintingSystemImporter::importPrintingSystem(filename.c_str(),&errStream,printsystem);

        FileOutputStream fileOutputStream = FileOutputStream(happydayAPDir + "/outputXML.txt");
        printsystem.processAllJobsAutomatically(&fileOutputStream);
        outputFileName = happydayAPDir + "/aptest" + ToString(counter) + ".txt";
        EXPECT_TRUE(FileCompare(happydayAPDir + "/outputXML.txt", outputFileName));
        counter +=1;
        filename = happydayAPDir + "/aptest" + ToString(counter) + ".xml";
        printsystem.clearSystemBecauseInvalid();
    }
    EXPECT_TRUE(counter == 4);
}

string invalidOutputAPDir = "testXMLs/AutomaticallyProcessTests/InvalidOutputTest";

TEST_F(AutomaticallyProcessTest, InvalidOutput) {
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
