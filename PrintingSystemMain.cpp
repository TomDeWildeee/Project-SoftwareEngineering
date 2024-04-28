#include "PrintingSystem.h"
#include "PrintingSystemImporter.h"

int main() {
    PrintingSystem printsystem;
    FileOutputStream fileOutputStream("testXMLs/error.txt");
    ImportEnum imp = PrintingSystemImporter::importPrintingSystem("testXMLs/XML_test.xml", &fileOutputStream, printsystem);
    if (imp == ImportError) {
        std::cout << "error" << std::endl;
    } else {
        FileOutputStream c("testXMLs/error.txt");
        NoOutputStream n;
        printsystem.processJob(&n, printsystem.getJobs()[0]->getJobNR());
        printsystem.processJob(&n, printsystem.getJobs()[1]->getJobNR());

        printsystem.advancedOutput(&c);
    }

}
