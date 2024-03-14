#include "PrintingSystem.h"
#include "PrintingSystemImporter.h"

int main() {
    PrintingSystem printingSystem;
    PrintingSystemImporter::importPrintingSystem("testXMLs/System1.xml", std::cout, printingSystem);
    printingSystem.saveOutput();
    printingSystem.processJob(89751, std::cout);
    printingSystem.saveOutput();
}