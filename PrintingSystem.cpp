#include "DesignByContract.h"
#include "PrintingSystem.h"
#include <fstream>
#include <iostream>
#include <algorithm>

bool PrintingSystem::properlyInitialized() {
    return _initCheck == this;
}

PrintingSystem::PrintingSystem() {
    _initCheck = this;
    ENSURE(this->properlyInitialized(), "constructor must end in properlyInitialized state");
}


bool PrintingSystem::isUniqueJobNumber(const int jobNR) {
    REQUIRE(this->properlyInitialized(), "Printing system was not properly initialized when trying to check if a job number is unique");
    for (const auto &job : jobs) {
        if (job->getJobNR() == jobNR) return false;
    }
    return true;
}

void PrintingSystem::clearSystemBecauseInvalid() {
    REQUIRE(this->properlyInitialized(), "Printing system was not properly initialized when trying to clear it");
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

void PrintingSystem::addDevice(Device* device) {
    REQUIRE(this->properlyInitialized(), "Printing system was not properly initialized when trying to add a device");
    devices.push_back(device);
}

void PrintingSystem::addJob(Job* job) {
    REQUIRE(this->properlyInitialized(), "Printing system was not properly initialized when trying to add a job");
    jobs.push_back(job);
}

void PrintingSystem::saveOutput(OutputStream* outputStream) {
    REQUIRE(this->properlyInitialized(), "Printing system was not initialized while trying to save the output");

    outputStream->writeLine("Printers:");
    for (auto& device : devices) {
        std::string deviceInfo =  "\t" + device->getName() + " (CO2: " + std::to_string(device->getEmissions()) + " g/page, Speed: " + std::to_string(device->getSpeed()) + " pages/min)";
        outputStream->writeLine(deviceInfo);
    }

    outputStream->writeLine("Jobs:");
    for (auto& job : jobs) {
        std::string jobInfo =  "\t[#" + std::to_string(job->getJobNR()) + " | " + job->getUserName() + " | " + std::to_string(job->getPageCount()) + " pages]";
        outputStream->writeLine(jobInfo);
    }
}

void PrintingSystem::processJob(OutputStream* outputStream, int jobNR) {
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
       std::string errString = "ERR: JOB with job number: " + std::to_string(jobNR) + " can not be found";
       outputStream->writeLine(errString);
       return;
    }

    // We're taking the first printer at the moment (only device in specification 1.0)
    Device* device = devices[0];

    for (int i = 0; i < jobToProcess->getPageCount(); ++i) {
        std::string printString = + "Printing page " + std::to_string(i + 1);
        outputStream->writeLine(printString);
    }
    totalEmissions += jobToProcess->getPageCount() * device->getEmissions();
    outputStream->writeLine("Printer \"" + device->getName() + "\" finished job:");
    outputStream->writeLine("\t Number: " + std::to_string(jobToProcess->getJobNR()));
    outputStream->writeLine("\t Submitted by \"" + jobToProcess->getUserName() + "\"");
    outputStream->writeLine("\t " + std::to_string(jobToProcess->getPageCount()) + " pages");

    jobs.erase(std::remove(jobs.begin(), jobs.end(), jobToProcess), jobs.end());
    ENSURE(std::find(jobs.begin(), jobs.end(), jobToProcess) == jobs.end(), "Processed job wasn't deleted out of the system");
}

void PrintingSystem::processAllJobsAutomatically(OutputStream* outputStream) {
    REQUIRE(this->properlyInitialized(), "System was not properly initialized when trying to automatically process jobs");
    REQUIRE(!devices.empty(), "There has to be at least 1 printer available to process jobs automatically");
    REQUIRE(!jobs.empty(), "There are no jobs that can be processed by a device");

    while (!jobs.empty()) {
        processJob(outputStream, jobs[0]->getJobNR());
    }

    ENSURE(jobs.empty(), "Not all jobs were processed after trying to process all the jobs");
}

std::vector<Job*> PrintingSystem::getJobs() {
    REQUIRE(this->properlyInitialized(), "System was not properly initialized when trying to get jobs");
    return jobs;
}
int PrintingSystem::gettotalEmissions() {
    REQUIRE(this->properlyInitialized(), "System was not properly initialized when trying to get total emissions");
    return totalEmissions;
}
std::vector<Device*> PrintingSystem::getDevices() {
    REQUIRE(this->properlyInitialized(), "System was not properly initialized when trying to get devices");
    return devices;
}