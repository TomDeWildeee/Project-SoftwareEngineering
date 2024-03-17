#include <fstream>
#include "gtest/gtest.h"
#include "../PrintingSystem.h"
#include "../PrintingSystemImporter.h"
#include "../Utils.h"
using namespace std;
class ManualllyProcessTest: public ::testing::Test{
protected:
    friend class PrintingSystem;
    friend class job;
    void SetUp() override{
    }
    void TearDown() override{
    };
    PrintingSystem printsystem;
};
string HappyDayMPDir = "testXMLs/ManuallyProcessTests/HappyDayTest";

TEST_F(ManualllyProcessTest, HappyDayMP){
    ASSERT_TRUE(DirectoryExists(HappyDayMPDir));
    ofstream myfile;
    int counter = 1;
    string filename = HappyDayMPDir + "/mptest" + ToString(counter) + ".xml";
    string outputFileName;
    while(FileExists(filename)){
        myfile.open(HappyDayMPDir + "/outputXML.txt");
        PrintingSystemImporter::importPrintingSystem(filename.c_str(),myfile,printsystem);
        vector<Job*> jobs = printsystem.getJobs();
        printsystem.processJob(jobs[2]->getJobNR(), myfile);
        printsystem.processJob(jobs[4]->getJobNR(),myfile);
        myfile.close();
        outputFileName = HappyDayMPDir + "/mptest" + ToString(counter) + ".txt";
        EXPECT_TRUE(FileCompare(HappyDayMPDir + "/outputXML.txt", outputFileName));
        counter += 1;
        filename = HappyDayMPDir + "/mptest" + ToString(counter) + ".xml";
        printsystem.clearSystemBecauseInvalid();
    }
    EXPECT_TRUE(counter == 4);
}

string invalidOutputMPDir = "testXMLs/ManuallyProcessTests/InvalidOutputTest";

TEST_F(ManualllyProcessTest, InvalidOutPut){
    ASSERT_TRUE(DirectoryExists(HappyDayMPDir));
    ofstream myfile;
    int counter = 1;
    string filename = invalidOutputMPDir + "/mptest" + ToString(counter) + ".xml";
    string outputFileName;
    while(FileExists(filename)){
        myfile.open(invalidOutputMPDir + "/outputXML.txt");
        PrintingSystemImporter::importPrintingSystem(filename.c_str(),myfile,printsystem);
        vector<Job*> jobs = printsystem.getJobs();
        printsystem.processJob(jobs[2]->getJobNR(), myfile);
        printsystem.processJob(jobs[4]->getJobNR(),myfile);
        myfile.close();
        outputFileName = invalidOutputMPDir + "/mptest" + ToString(counter) + ".txt";
        EXPECT_FALSE(FileCompare(invalidOutputMPDir + "/outputXML.txt", outputFileName));
        counter += 1;
        filename = invalidOutputMPDir + "/mptest" + ToString(counter) + ".xml";
        printsystem.clearSystemBecauseInvalid();
    }
    EXPECT_TRUE(counter == 4);
}