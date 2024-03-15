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
    ASSERT_TRUE(DirectoryExists("testXMLs"));
    ofstream myfile;
    ImportEnum importresult;
    int counter = 1;
    string filename = "testXMLs/xmlsyntaxerror" + ToString(counter) + ".xml";
    string errorfilename;
    while(FileExists(filename)){
        myfile.open("testXMLs/xmlError.txt");
        importresult = PrintingSystemImporter::importPrintingSystem(filename.c_str(),myfile,printsystem);
        myfile.close();
        EXPECT_TRUE(importresult == ImportError);
        errorfilename = "testXMLs/xmlsyntaxerror" + ToString(counter) + ".txt";
        EXPECT_TRUE(FileCompare("testXMLs/xmlError.txt", errorfilename));
        counter +=1;
        filename = "testXMLs/xmlsyntaxerror" + ToString(counter) + ".xml";
    }
    EXPECT_TRUE(counter == 5);
}
/*
TEST_F(PrintingSystemTest, inputillegalnumbers){
    ASSERT_TRUE(DirectoryExists("testXMLs"));
    ofstream myfile;
    ImportEnum importresult;
    int counter = 1;
    string filename = "testXMLs/inputillegal" + ToString(counter) + ".xml";
    string errorfilename;
    while(FileExists(filename)){
        myfile.open("testXMLs/inputillegal.txt");
        importresult = PrintingSystemImporter::importPrintingSystem(filename.c_str(),myfile,printsystem);
        myfile.close();
        EXPECT_TRUE(importresult == ImportError);
        errorfilename = "testXMLs/inputillegal" + ToString(counter) + ".txt";
        EXPECT_TRUE(FileCompare("testXMLs/inputillegal.txt", errorfilename));
        counter +=1;
        filename = "testXMLs/inputillegal" + ToString(counter) + ".xml";
    }
    EXPECT_TRUE(counter == 5);
}
 */
TEST_F(PrintingSystemTest, inputlegal){
    ASSERT_TRUE(DirectoryExists("testXMLs"));
    ofstream myfile;
    ImportEnum importresult;
    int counter = 1;
    string filename = "testXMLs/inputlegal" + ToString(counter) + ".xml";
    string errorfilename;
    while(FileExists(filename)){
        myfile.open("testXMLs/xmlError.txt");
        importresult = PrintingSystemImporter::importPrintingSystem(filename.c_str(),myfile,printsystem);
        myfile.close();
        EXPECT_TRUE(importresult == ImportSuccess);
        counter +=1;
        if(counter == 5){break;}
        std::cout << filename << std::endl;
        filename = "testXMLs/inputlegal" + ToString(counter) + ".xml";
    }
    EXPECT_TRUE(counter == 5);
}