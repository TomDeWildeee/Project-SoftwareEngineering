#include "PrintingSystem.h"
#include "PrintingSystemImporter.h"

int main() {
    PrintingSystem printsystem;
    FileOutputStream fileOutputStream = FileOutputStream("testXMLs/error.txt");
    ImportEnum imp = PrintingSystemImporter::importPrintingSystem("testXMLs/XML_test.xml", &fileOutputStream ,printsystem);
    if (imp == ImportError){
        std::cout << "error" << std::endl;
    }
    else{
        FileOutputStream fileoutput = FileOutputStream("testXMLs/error.txt");
        printsystem.saveOutput(&fileoutput);
        std::cout << printsystem.getDevices()[0]->getCost() << std::endl;
        printsystem.processJob(&fileoutput, 123);
        std::cout << printsystem.getDevices()[0]->getCost() << std::endl;
        printsystem.saveOutput(&fileoutput);
        std::cout << printsystem.gettotalEmissions();
    }
}

