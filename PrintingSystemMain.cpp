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
        auto devices2 = printsystem.getDevices();
        for(auto device : devices2){
            auto jobs = device->getFinishedjobs();
            for(auto job : jobs){
                std::cout << job->getJobNR() << std::endl;
            }
        }
    }
}
