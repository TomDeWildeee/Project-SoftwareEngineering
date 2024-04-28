#include "PrintingSystem.h"
#include "PrintingSystemImporter.h"

int main() {
    PrintingSystem printsystem;
    FileOutputStream fileOutputStream("testXMLs/InputTests/inputsyntaxerrors/xmlError.txt");/*
    FileOutputStream fileOutputStream("testXMLs/error.txt");*/
    ImportEnum imp = PrintingSystemImporter::importPrintingSystem("testXMLs/InputTests/inputsyntaxerrors/xmlsyntaxerror4.xml", &fileOutputStream, printsystem);
    if (imp == ImportError) {
        std::cout << "error" << std::endl;
    } else {
        printsystem.processAllJobsAutomatically(&fileOutputStream);

    }
}
