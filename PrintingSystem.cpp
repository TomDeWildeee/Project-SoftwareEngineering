#include "DesignByContract.h"
#include "PrintingSystem.h"
#include <fstream>
#include <iostream>

bool PrintingSystem::properlyInitialized() {
    return _initCheck == this;
}

PrintingSystem::PrintingSystem() {
    _initCheck = this;
    ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}


bool PrintingSystem::isUniqueJobNumber(const int jobNR) {
    for (const auto &job : jobs) {
        if (job->getJobNR() == jobNR) return false;
    }
    return true;
}

void PrintingSystem::clearSystemBecauseInvalid() {
    for (auto device : devices) {
        delete device;
    }

    for (auto job : jobs) {
        delete job;
    }
    devices.clear();
    jobs.clear();

    ENSURE(devices.empty(), "Devices vector wasn't empty after clearing system");
    ENSURE(jobs.empty(), "Jobs vector wasn't empty after clearing system");
}

void PrintingSystem::addDevice(Device *device) {
    devices.push_back(device);
}

void PrintingSystem::addJob(Job *job) {
    jobs.push_back(job);
}

void PrintingSystem::saveOutput() {
    std::ofstream outputFile ("output.txt");

    outputFile << "Printers: " << std::endl;
    for (auto& device : devices) {
        outputFile << "\t" << device->getName() << " (CO2: " << device->getEmissions() << " g/page, Speed: "<< device->getSpeed() << " pages/min)" << std::endl;
    }

    outputFile << "Jobs: " << std::endl;
    for (auto& job : jobs) {
        outputFile << "\t[#" << job->getJobNR() << " | " << job->getUserName() << " | " << job->getPageCount() << " pages]" << std::endl;
    }

    outputFile.close();
}