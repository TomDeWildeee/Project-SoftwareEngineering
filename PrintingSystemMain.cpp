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
        printsystem.processJob(&fileOutputStream, printsystem.getJobs()[2]->getJobNR());
        printsystem.processJob(&fileOutputStream, printsystem.getJobs()[3]->getJobNR());
        auto devices = printsystem.getDevices();
        for(auto device : devices){
            auto jobqueue = device->getJobqueue();
            for(auto job : jobqueue){
                std::cout << job->getJobNR();
            }
        }
    }
}
