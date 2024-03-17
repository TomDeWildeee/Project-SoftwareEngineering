#include <fstream>
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
    ofstream myfile;
    int counter = 1;
    string filename = happydayAPDir + "/aptest" + ToString(counter) + ".xml";
    string outputFileName;
    while(FileExists(filename)){
        myfile.open(happydayAPDir + "/outputXML.txt");
        PrintingSystemImporter::importPrintingSystem(filename.c_str(),myfile,printsystem);
        printsystem.processAllJobsAutomatically(myfile);
        myfile.close();
        outputFileName = happydayAPDir + "/aptest" + ToString(counter) + ".txt";
        EXPECT_TRUE(FileCompare(happydayAPDir + "/outputXML.txt", outputFileName));
        counter +=1;
        filename = happydayAPDir + "/aptest" + ToString(counter) + ".xml";
        printsystem.clearSystemBecauseInvalid();
    }
    EXPECT_TRUE(counter == 4);
}

string invalidOutputDir = "testXMLs/AutomaticallyProcessTests/InvalidOutputTest";

TEST_F(AutomaticallyProcessTest, InvalidOutput) {
    ASSERT_TRUE(DirectoryExists(invalidOutputDir));
    ofstream myfile;
    int counter = 1;
    string filename = invalidOutputDir + "/invalidoutput" + ToString(counter) + ".xml";
    string outputFileName;
    while(FileExists(filename)){
        myfile.open(invalidOutputDir + "/outputXML.txt");
        PrintingSystemImporter::importPrintingSystem(filename.c_str(),myfile,printsystem);
        printsystem.processAllJobsAutomatically(myfile);
        myfile.close();
        outputFileName = invalidOutputDir + "/invalidoutput" + ToString(counter) + ".txt";
        EXPECT_FALSE(FileCompare(invalidOutputDir + "/outputXML.txt", outputFileName));
        counter +=1;
        filename = invalidOutputDir + "/invalidoutput" + ToString(counter) + ".xml";
        printsystem.clearSystemBecauseInvalid();
    }
    EXPECT_TRUE(counter == 2);
}