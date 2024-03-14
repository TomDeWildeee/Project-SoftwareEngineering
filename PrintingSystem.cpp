#include "DesignByContract.h"
#include "PrintingSystem.h"
#include <fstream>
#include <iostream>
#include <thread>
#include <algorithm>
#include "PrintingSystemImporter.h"

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

void PrintingSystem::processJob(int jobNR, std::ostream &outputStream) {
    REQUIRE(this->properlyInitialized(), "System was not properly initialized when trying to process a job");
    REQUIRE(!devices.empty(), "There has to be at least 1 printer available to process a job");
    REQUIRE(!jobs.empty(), "There are no jobs that can be processed by a device");

    Job* jobToProcess = nullptr;
    for (const auto &job : jobs) {
        if (job->getJobNR() == jobNR) {
            jobToProcess = job;
            break;
        }
    }

    if (jobToProcess == nullptr) {
       outputStream << "ERR: JOB with job number: " << jobNR << " can not be found" << std::endl;
       return;
    }

    // We're taking the first printer at the moment
    Device* device = devices[0];

    // Searched up how to sleep in c++ to make the processing more realistic
    for (int i = 0; i < jobToProcess->getPageCount(); ++i) {
        outputStream << "Printing page " << i + 1 << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(device->getSpeed() * 10));
    }

    outputStream << "Printer \"" << device->getName() << "\" finished job:" << std::endl;
    outputStream << "\t Number: " << jobToProcess->getJobNR() << std::endl;
    outputStream << "\t Submitted by \"" << jobToProcess->getUserName() << "\"" << std::endl;
    outputStream <<  "\t " << jobToProcess->getPageCount() << " pages" << std::endl;

    jobs.erase(std::remove(jobs.begin(), jobs.end(), jobToProcess), jobs.end());

}

void PrintingSystem::processAllJobsAutomatically(std::ostream &outputStream) {
    REQUIRE(this->properlyInitialized(), "System was not properly initialized when trying to automatically process jobs");
    REQUIRE(!devices.empty(), "There has to be at least 1 printer available to process jobs automatically");
    REQUIRE(!jobs.empty(), "There are no jobs that can be processed by a device");

    while (!jobs.empty()) {
        processJob(jobs[0]->getJobNR(), outputStream);
    }
}
