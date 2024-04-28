#include "PrintingSystem.h"
#include "PrintingSystemImporter.h"

int main() {
    PrintingSystem printsystem;
    FileOutputStream fileOutputStream("testXMLs/ManuallyProcessTests/InvalidOutputTest/outputXML.txt");/*
    FileOutputStream fileOutputStream("testXMLs/error.txt");*/
    ImportEnum imp = PrintingSystemImporter::importPrintingSystem("testXMLs/ManuallyProcessTests/InvalidOutputTest/mptest3.xml", &fileOutputStream, printsystem);
    if (imp == ImportError) {
        std::cout << "error" << std::endl;
    } else {
        FileOutputStream c("testXMLs/error.txt");
        NoOutputStream n;
        for (auto& device : printsystem.getDevices()) {
            c.writeLine(device->getName());
            for (auto& job : device->getJobqueue()) {
                c.writeLine(std::to_string(job->getJobNR()));
            }
        }

        printsystem.saveOutput(&c);
    }
}
