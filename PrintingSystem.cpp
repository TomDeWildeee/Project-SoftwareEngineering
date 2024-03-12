#include "DesignByContract.h"
#include "PrintingSystem.h"
<<<<<<< HEAD
#include "tinyxml.h"
#include <fstream>
#include <iostream>
=======
>>>>>>> 48f61dece6a1754b633bc4fb1addf0b8fbe48ee6

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

    for (auto& device : devices) {
        outputFile << device->getName() << " (CO2: " << device->getEmissions() << "g/page):" << std::endl;
    }
    for (auto& job : jobs) {
        if (job == jobs.front()) {
            outputFile << "\t* Current: \n\t\t[#" << job->getJobNR() << "|" << job->getUserName() << "]" << std::endl;
            outputFile << "\t* Queue:" << std::endl;
        } else {
            outputFile << "\t\t[#" << job->getJobNR() << "|" << job->getUserName() << "]" << std::endl;
        }
    }

    outputFile.close();
}