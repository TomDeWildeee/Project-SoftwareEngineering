#include "PrintingSystem.h"
#include "PrintingSystemImporter.h"

int main() {
    PrintingSystem printingSystem;
    PrintingSystemImporter importer;
    importer.importPrintingSystem("testXMLs/System1.xml", std::cout,printingSystem);
}