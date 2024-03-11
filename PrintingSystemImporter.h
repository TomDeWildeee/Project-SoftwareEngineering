#ifndef PROJECT_SOFTWAREENGINEERING_PRINTINGSYSTEMIMPORTER_H
#define PROJECT_SOFTWAREENGINEERING_PRINTINGSYSTEMIMPORTER_H

#include "PrintingSystem.h"

enum ImportEnum {ImportSuccess, ImportError};

class PrintingSystemImporter {
public:
    static ImportEnum importPrintingSystem(const char* filename, std::ostream &errStream, PrintingSystem &printingSystem);
};


#endif //PROJECT_SOFTWAREENGINEERING_PRINTINGSYSTEMIMPORTER_H
