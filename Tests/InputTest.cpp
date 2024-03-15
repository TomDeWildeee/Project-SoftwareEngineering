#include "../PrintingSystem.h"
#include "../PrintingSystemImporter.h"
#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include "../Utils.h"

using namespace std;
class PrintingSystemImporterTest: public ::testing::Test{
protected:
    friend class PrintingSystem;
    void SetUp() override{
    }
    void TearDown() override {
    }

    PrintingSystem printsystem;
};

std::string inputSyntaxErrorsDirectory = "testXMLs/inputsyntaxerrors";

TEST_F(PrintingSystemImporterTest, inputsyntaxerrors){
    ASSERT_TRUE(DirectoryExists(inputSyntaxErrorsDirectory));
    ofstream myfile;
    ImportEnum importresult;
    int counter = 1;
    string filename = inputSyntaxErrorsDirectory + "/xmlsyntaxerror" + ToString(counter) + ".xml";
    string errorfilename;
    while(FileExists(filename)){
        myfile.open(inputSyntaxErrorsDirectory + "/xmlError.txt");
        importresult = PrintingSystemImporter::importPrintingSystem(filename.c_str(),myfile,printsystem);
        myfile.close();
        EXPECT_TRUE(importresult == ImportError);
        errorfilename = inputSyntaxErrorsDirectory + "/xmlsyntaxerror" + ToString(counter) + ".txt";
        EXPECT_TRUE(FileCompare(inputSyntaxErrorsDirectory + "/xmlError.txt", errorfilename));
        counter +=1;
        filename = inputSyntaxErrorsDirectory + "/xmlsyntaxerror" + ToString(counter) + ".xml";
    }
    EXPECT_TRUE(counter == 5);
}


std::string illegalInputDirectory = "testXMLs/illegalinput";

TEST_F(PrintingSystemImporterTest, inputillegalnumbers){
    ASSERT_TRUE(DirectoryExists(illegalInputDirectory));
    ofstream myfile;
    ImportEnum importresult;
    int counter = 1;
    string filename = illegalInputDirectory + "/inputillegal" + ToString(counter) + ".xml";
    string errorfilename;
    while(FileExists(filename)){
        myfile.open(illegalInputDirectory + "/inputillegal.txt");
        importresult = PrintingSystemImporter::importPrintingSystem(filename.c_str(),myfile,printsystem);
        myfile.close();
        EXPECT_TRUE(importresult == ImportError);
        errorfilename = illegalInputDirectory + "/inputillegal" + ToString(counter) + ".txt";
        EXPECT_TRUE(FileCompare(illegalInputDirectory + "/inputillegal.txt", errorfilename));
        counter += 1;
        filename = illegalInputDirectory + "/inputillegal" + ToString(counter) + ".xml";
    }
    EXPECT_TRUE(counter == 4);
}


std::string legalInputDirectory = "testXMLs/legalinput";

TEST_F(PrintingSystemImporterTest, inputlegal){
    ASSERT_TRUE(DirectoryExists(legalInputDirectory));
    ofstream myfile;
    ImportEnum importresult;
    int counter = 1;
    string filename = legalInputDirectory + "/inputlegal" + ToString(counter) + ".xml";
    string errorfilename;
    while(FileExists(filename)){
        myfile.open(legalInputDirectory + "/xmlError.txt");
        importresult = PrintingSystemImporter::importPrintingSystem(filename.c_str(),myfile,printsystem);
        myfile.close();
        EXPECT_TRUE(importresult == ImportSuccess);
        counter +=1;
        if(counter == 5){break;}
        filename = legalInputDirectory + "/inputlegal" + ToString(counter) + ".xml";
    }
    EXPECT_TRUE(counter == 5);
}