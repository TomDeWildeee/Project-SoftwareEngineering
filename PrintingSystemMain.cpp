#include "PrintingSystem.h"
#include "PrintingSystemImporter.h"

int main() {
    PrintingSystem printsystem;
    FileOutputStream fileOutputStream = FileOutputStream("testXMLs/InputTests/legalinput/xmlError.txt");
    ImportEnum imp = PrintingSystemImporter::importPrintingSystem("testXMLs/InputTests/legalinput/inputlegal1.xml", &fileOutputStream ,printsystem);
    if (imp == ImportError){
        std::cout << "error" << std::endl;
    }
    else{std::cout << "success" << std::endl;
        FileOutputStream fileoutput = FileOutputStream("testXMLs/InputTests/legalinput/xmlError.txt");
        printsystem.saveOutput(&fileoutput);
        std::cout << printsystem.getDevices()[0]->getCost();
        printsystem.processJob(&fileoutput, printsystem.getJobs()[0]->getJobNR());
        std::cout << printsystem.getDevices()[0]->getCost();
        printsystem.saveOutput(&fileoutput);
        std::cout << printsystem.gettotalEmissions();
    }
}

