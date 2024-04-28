#include "../PrintingSystem.h"
#include "../PrintingSystemImporter.h"
#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include "../Utils.h"


using namespace std;
class EmissionsTest: public ::testing::Test{
protected:
    friend class PrintingSystem;
    void SetUp() override{
    }
    void TearDown() override {
    }
    PrintingSystem printsystem;
};

string emissionsHappyDayDirectory = "testXMLs/EmissionsTests/EmissionsHappyDay";

TEST_F(EmissionsTest, EmissionsHappyDay) {
    ASSERT_TRUE(DirectoryExists(emissionsHappyDayDirectory));
    int counter = 1;
    string filename = emissionsHappyDayDirectory + "/emissionshappyday" + ToString(counter) + ".xml";
    string outputfilename;
    while(FileExists(filename)){
        FileOutputStream errStream = FileOutputStream(emissionsHappyDayDirectory + "/output.txt");
        PrintingSystemImporter::importPrintingSystem(filename.c_str(),&errStream,printsystem);

        FileOutputStream fileOutputStream = FileOutputStream(emissionsHappyDayDirectory + "/output.txt");
        fileOutputStream.writeLine("System has emitted: " + std::to_string(printsystem.getTotalEmissions()) + "grams of CO2");
        NoOutputStream n;
        printsystem.processJob(&n, printsystem.getJobs()[0]->getJobNR());
        fileOutputStream.writeLine("System has emitted: " + std::to_string(printsystem.getTotalEmissions()) + "grams of CO2");

        printsystem.processJob(&n, printsystem.getJobs()[0]->getJobNR());
        fileOutputStream.writeLine("System has emitted: " + std::to_string(printsystem.getTotalEmissions()) + "grams of CO2");

        outputfilename = emissionsHappyDayDirectory + "/emissionshappyday" + ToString(counter) + ".txt";
        EXPECT_TRUE(FileCompare(emissionsHappyDayDirectory + "/output.txt", outputfilename));
        counter += 1;
        filename = emissionsHappyDayDirectory + "/emissionshappyday" + ToString(counter) + ".xml";
        printsystem.clearSystemBecauseInvalid();
    }
    EXPECT_TRUE(counter == 4);
}