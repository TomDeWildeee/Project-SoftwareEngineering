#ifndef PROJECT_SOFTWAREENGINEERING_PRINTINGSYSTEM_H
#define PROJECT_SOFTWAREENGINEERING_PRINTINGSYSTEM_H

#include <iostream>
#include <vector>
#include "Device.h"
#include "Job.h"

class PrintingSystem {
public:
    PrintingSystem();
    bool properlyInitialized();
    bool isUniqueJobNumber(int jobNR);
    void clearSystemBecauseInvalid();

    void addDevice(Device* device);
    void addJob(Job* job);

    void processJob(int jobNR, std::ostream &outputStream);
    void processAllJobsAutomatically(std::ostream &outputStream);

    void saveOutput();

private:
    std::vector<Device*> devices;
    std::vector<Job*> jobs;
    PrintingSystem* _initCheck;

};


#endif //PROJECT_SOFTWAREENGINEERING_PRINTINGSYSTEM_H
