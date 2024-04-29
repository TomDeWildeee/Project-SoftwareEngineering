#include "../PrintingSystem.h"
#include "../PrintingSystemImporter.h"
#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include "../Utils.h"

using namespace std;
class DeviceTest: public ::testing::Test{
protected:
    void SetUp() override{
    }
    void TearDown() override {
    }
    PrintingSystem printsystem;
};

TEST_F(DeviceTest, ConstructorTest) {
    auto* device = new Device("Printer1", 20, 5, DeviceType::DeviceTypeEnum::color, 5);
    EXPECT_NE(device->getName(), "Printer8");
    EXPECT_EQ(device->getName(), "Printer1");
    EXPECT_NE(device->getEmissions(), 10);
    EXPECT_EQ(device->getEmissions(), 20);
    EXPECT_NE(device->getSpeed(), 10);
    EXPECT_EQ(device->getSpeed(), 5);
    delete device;
}

string QueueHappyDayDirectory = "testXMLs/DeviceTests/JobQueueHappyDay";
TEST_F(DeviceTest, JobQueueHappyDay) {
    ASSERT_TRUE(DirectoryExists(QueueHappyDayDirectory));
    int counter = 1;
    string filename = QueueHappyDayDirectory + "/jobqueuehappyday" + to_string(counter) + ".xml";
    string outputfilename;
    while (FileExists(filename)) {
        FileOutputStream errStream = FileOutputStream(QueueHappyDayDirectory + "/jobqueuehappyday.txt");
        PrintingSystemImporter::importPrintingSystem(filename.c_str(),&errStream,printsystem);
        FileOutputStream fileOutputStream = FileOutputStream(QueueHappyDayDirectory + "/jobqueuehappyday.txt");

        for (auto& device : printsystem.getDevices()) {
            fileOutputStream.writeLine(device->getName());
            for (auto& job : device->getJobqueue()) {
                fileOutputStream.writeLine(to_string(job->getJobNR()));
            }
        }
        outputfilename = QueueHappyDayDirectory + "/jobqueuehappyday" + ToString(counter) + ".txt";
        EXPECT_TRUE(FileCompare(QueueHappyDayDirectory + "/jobqueuehappyday.txt", outputfilename));
        counter += 1;
        filename = QueueHappyDayDirectory + "/jobqueuehappyday" + ToString(counter) + ".xml";
        printsystem.clearSystemBecauseInvalid();
    }
    EXPECT_TRUE(counter == 5);
}

string QueueInvalidDirectory = "testXMLs/DeviceTests/JobQueueInvalid";
TEST_F(DeviceTest, JobQueueInvalid) {
    ASSERT_TRUE(DirectoryExists(QueueInvalidDirectory));
    int counter = 1;
    string filename = QueueInvalidDirectory + "/jobqueueinvalid" + to_string(counter) + ".xml";
    string outputfilename;
    while (FileExists(filename)) {
        FileOutputStream errStream = FileOutputStream(QueueInvalidDirectory + "/jobqueueinvalid.txt");
        PrintingSystemImporter::importPrintingSystem(filename.c_str(),&errStream,printsystem);
        FileOutputStream fileOutputStream = FileOutputStream(QueueInvalidDirectory + "/jobqueueinvalid.txt");

        for (auto& device : printsystem.getDevices()) {
            fileOutputStream.writeLine(device->getName());
            for (auto& job : device->getJobqueue()) {
                fileOutputStream.writeLine(to_string(job->getJobNR()));
            }
        }
        outputfilename = QueueInvalidDirectory + "/jobqueueinvalid" + ToString(counter) + ".txt";
        EXPECT_FALSE(FileCompare(QueueInvalidDirectory + "/jobqueueinvalid.txt", outputfilename));
        counter += 1;
        filename = QueueInvalidDirectory + "/jobqueueinvalid" + ToString(counter) + ".xml";
        printsystem.clearSystemBecauseInvalid();
    }
    EXPECT_TRUE(counter == 5);
}