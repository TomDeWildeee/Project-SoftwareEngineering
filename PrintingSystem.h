#ifndef PROJECT_SOFTWAREENGINEERING_PRINTINGSYSTEM_H
#define PROJECT_SOFTWAREENGINEERING_PRINTINGSYSTEM_H

#include <iostream>
#include <vector>
#include "Device.h"
#include "Job.h"

enum ImportEnum {ImportSuccess, ImportError};

class PrintingSystem {
public:
    PrintingSystem();
    bool properlyInitialized();

    ImportEnum importPrintingSystem(const char* filename, std::ostream &errStream);

private:
    std::vector<Device*> devices;
    std::vector<Job*> jobs;
    PrintingSystem* _initCheck;

    bool isUniqueJobNumber(int jobNR);
    void clearSystemBecauseInvalid();
};


#endif //PROJECT_SOFTWAREENGINEERING_PRINTINGSYSTEM_H
