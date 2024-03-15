#include "../PrintingSystem.h"
#include "../PrintingSystemImporter.h"
#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include "../Utils.h"

using namespace std;
class PrintingSystemTest: public ::testing::Test{
protected:
    friend class PrintingSystem;
    void SetUp() override{
    }
    void TearDown() override {
    }

    PrintingSystem printsystem;
};



TEST_F(PrintingSystemTest, inputsyntaxerrors){
    ASSERT_TRUE(DirectoryExists("testXMLs/inputsyntaxerrors"));
    ofstream myfile;
    ImportEnum importresult;
    int counter = 1;
    string filename = "testXMLs/inputsyntaxerrors/xmlsyntaxerror" + ToString(counter) + ".xml";
    string errorfilename;
    while(FileExists(filename)){
        myfile.open("testXMLs/inputsyntaxerrors/xmlError.txt");
        importresult = PrintingSystemImporter::importPrintingSystem(filename.c_str(),myfile,printsystem);
        myfile.close();
        EXPECT_TRUE(importresult == ImportError);
        errorfilename = "testXMLs/inputsyntaxerrors/xmlsyntaxerror" + ToString(counter) + ".txt";
        EXPECT_TRUE(FileCompare("testXMLs/inputsyntaxerrors/xmlError.txt", errorfilename));
        counter +=1;
        filename = "testXMLs/inputsyntaxerrors/xmlsyntaxerror" + ToString(counter) + ".xml";
    }
    EXPECT_TRUE(counter == 5);
}



std::string illegalInputDirectory = "testXMLs/illegalinput";

TEST_F(PrintingSystemTest, inputillegalnumbers){
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



TEST_F(PrintingSystemTest, inputlegal){
    ASSERT_TRUE(DirectoryExists("testXMLs/legalinput"));
    ofstream myfile;
    ImportEnum importresult;
    int counter = 1;
    string filename = "testXMLs/legalinput/inputlegal" + ToString(counter) + ".xml";
    string errorfilename;
    while(FileExists(filename)){
        myfile.open("testXMLs/legalinput/xmlError.txt");
        importresult = PrintingSystemImporter::importPrintingSystem(filename.c_str(),myfile,printsystem);
        myfile.close();
        EXPECT_TRUE(importresult == ImportSuccess);
        counter +=1;
        if(counter == 5){break;}
        filename = "testXMLs/legalinput/inputlegal" + ToString(counter) + ".xml";
    }
    EXPECT_TRUE(counter == 5);
}