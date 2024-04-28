#include "PrintingSystem.h"
#include "PrintingSystemImporter.h"

int main() {
    PrintingSystem printsystem;
    FileOutputStream fileOutputStream("testXMLs/error.txt");
    ImportEnum imp = PrintingSystemImporter::importPrintingSystem("testXMLs/XML_test.xml", &fileOutputStream, printsystem);
    if (imp == ImportError) {
        std::cout << "error" << std::endl;
    } else {
        printsystem.saveOutput(&fileOutputStream);
        printsystem.processAllJobsAutomatically(&fileOutputStream);
        printsystem.saveOutput(&fileOutputStream);

        ConsoleOutputStream c;
        printsystem.advancedOutput(&c);
    }
}
