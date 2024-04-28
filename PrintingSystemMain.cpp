#include "PrintingSystem.h"
#include "PrintingSystemImporter.h"

int main() {
    PrintingSystem printsystem;
    FileOutputStream fileOutputStream("testXMLs/error.txt");
    ImportEnum imp = PrintingSystemImporter::importPrintingSystem("testXMLs/XML_test.xml", &fileOutputStream, printsystem);
    if (imp == ImportError) {
        std::cout << "error" << std::endl;
    } else {
        FileOutputStream c("testXMLs/test.txt");
        NoOutputStream n;
        printsystem.processAllJobsAutomatically(&n);

        printsystem.advancedOutput(&c);
    }
}
