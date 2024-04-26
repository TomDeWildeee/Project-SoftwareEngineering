#include "../PrintingSystem.h"
#include "../PrintingSystemImporter.h"
#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include "../Utils.h"

using namespace std;
class OutputTest: public ::testing::Test{
protected:
    friend class PrintingSystem;
    void SetUp() override{
    }
    void TearDown() override {
    }
    PrintingSystem printsystem;
};

string outputHappyDayDirectory = "testXMLs/OutputTests/OutputHappyDay";

TEST_F(OutputTest, SimpleOutputHappyDay) {
    ASSERT_TRUE(DirectoryExists(outputHappyDayDirectory));
    int counter = 1;
    string filename = outputHappyDayDirectory + "/outputhappyday" + ToString(counter) + ".xml";
    string outputfilename;
    while(FileExists(filename)){
        FileOutputStream errStream = FileOutputStream(outputHappyDayDirectory + "/outputhappyday.txt");
        PrintingSystemImporter::importPrintingSystem(filename.c_str(),&errStream,printsystem);

        FileOutputStream fileOutputStream = FileOutputStream(outputHappyDayDirectory + "/outputhappyday.txt");
        printsystem.saveOutput(&fileOutputStream);
        outputfilename = outputHappyDayDirectory + "/outputhappyday" + ToString(counter) + ".txt";
        EXPECT_TRUE(FileCompare(outputHappyDayDirectory + "/outputhappyday.txt", outputfilename));
        counter += 1;
        filename = outputHappyDayDirectory + "/outputhappyday" + ToString(counter) + ".xml";
        printsystem.clearSystemBecauseInvalid();
    }
    EXPECT_TRUE(counter == 5);
}

string outputInvalidDirectory = "testXMLs/OutputTests/OutputInvalid";

TEST_F(OutputTest, SimpleOutputInvalid) {
    ASSERT_TRUE(DirectoryExists(outputInvalidDirectory));
    int counter = 1;
    string filename = outputInvalidDirectory + "/outputinvalid" + ToString(counter) + ".xml";
    string outputfilename;
    while(FileExists(filename)){
        FileOutputStream errStream = FileOutputStream(outputInvalidDirectory + "/outputinvalid.txt");
        PrintingSystemImporter::importPrintingSystem(filename.c_str(),&errStream,printsystem);

        FileOutputStream fileOutputStream = FileOutputStream(outputInvalidDirectory + "/outputinvalid.txt");
        printsystem.saveOutput(&fileOutputStream);
        outputfilename = outputInvalidDirectory + "/outputinvalid" + ToString(counter) + ".txt";
        EXPECT_FALSE(FileCompare(outputInvalidDirectory + "/outputinvalid.txt", outputfilename));
        counter += 1;
        filename = outputInvalidDirectory + "/outputinvalid" + ToString(counter) + ".xml";
        printsystem.clearSystemBecauseInvalid();
    }
    EXPECT_TRUE(counter == 5);
}

