#include "DesignByContract.h"
#include "PrintingSystem.h"
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

    outputStream->writeLine("╔════════════════ [ System Diagnostic ] ════════════════╗\n");
    outputStream->writeLine("──── Devices ────\n");
    for (auto& device : devices) {
        std::string deviceName = device->getName() + ":";
        std::string deviceType = "* Type: ";
        if (device->getDeviceType() == "color") {
            deviceType += "Color printer";
        } else if (device->getDeviceType() == "bw") {
            deviceType += "Black-and-white printer";
        } else {
            deviceType += "Scanner";
        }
        std::string deviceSpeed = "* Speed: " + std::to_string(device->getSpeed()) + " pages/minute";
        std::string deviceCost = "* Cost: " + std::to_string(device->getCost()) + "cents/page";
        std::string deviceEmission = "* CO2: " + std::to_string(device->getEmissions()) + " g/page\n";

        outputStream->writeLine(deviceName);
        outputStream->writeLine(deviceType);
        outputStream->writeLine(deviceSpeed);
        outputStream->writeLine(deviceCost);
        outputStream->writeLine(deviceEmission);
    }
    outputStream->writeLine("───── Jobs ─────\n");
    for (auto& job : jobs) {
        std::string jobName = "[Job #" + std::to_string(job->getJobNR()) + "]";
        std::string jobUser = "* User: " + job->getUserName();
        std::string jobPageCount = "* Total Pages: " + std::to_string(job->getPageCount());

        outputStream->writeLine(jobName);
        outputStream->writeLine(jobUser);
        outputStream->writeLine(jobPageCount);
    }
    outputStream->writeLine("\n╚════════════════ [ System Diagnostic ] ════════════════╝");
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
    /*Device* device = devices[0];
    `*/
    Device* processingdevice = nullptr;
    for (Device* device : devices){
        if(device->getDeviceType() == jobToProcess->getJobType()){
            processingdevice = device;
            break;
        }
    }
    if (!processingdevice) {
        outputStream->writeLine("ERR: There is no device of the correct type to process job");
        return;
    }
    for (int i = 0; i < jobToProcess->getPageCount(); ++i) {
        std::string printString = + "Printing page " + std::to_string(i + 1);
        outputStream->writeLine(printString);
    }
    std::string typestring;
    if(jobToProcess->getJobType() == "color"){
        typestring = "color-printing";
    }
    if(jobToProcess->getJobType() == "bw"){
        typestring = "black-and-white-printing";
    }
    if(jobToProcess->getJobType() == "scan"){
        typestring = "scanning";
    }
    totalEmissions += jobToProcess->getPageCount() * processingdevice->getEmissions();
    outputStream->writeLine("Printer \"" + processingdevice->getName() + "\" finished " + typestring + " job:");
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

    std::vector<Job*> savedJobs = jobs;

    for (auto job : savedJobs) {
        processJob(outputStream, job->getJobNR());
    }

    ENSURE(jobs.empty(), "Not all jobs were processed after trying to process all the jobs, check if the devices have the right types");
}

std::vector<Job*> PrintingSystem::getJobs() {
    REQUIRE(this->properlyInitialized(), "System was not properly initialized when trying to get jobs");
    return jobs;
}
int PrintingSystem::getTotalEmissions() {
    REQUIRE(this->properlyInitialized(), "System was not properly initialized when trying to get total emissions");
    return totalEmissions;
}
std::vector<Device*> PrintingSystem::getDevices() {
    REQUIRE(this->properlyInitialized(), "System was not properly initialized when trying to get devices");
    return devices;
}