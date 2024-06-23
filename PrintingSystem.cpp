#include "DesignByContract.h"
#include "PrintingSystem.h"
#include <iostream>
#include <algorithm>
#include <cmath>

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
    auto find  = std::find(devices.begin(), devices.end(), device);
    ENSURE(find != devices.end(), "Device wasn't added to the printing system");
}

void PrintingSystem::addJob(Job* job) {
    REQUIRE(this->properlyInitialized(), "Printing system was not properly initialized when trying to add a job");
    jobs.push_back(job);
    auto find = std::find(jobs.begin(),jobs.end(), job);
    ENSURE(find != jobs.end(), "Job wasn't added to the printing system");
}

void PrintingSystem::saveOutput(OutputStream* outputStream) {
    REQUIRE(this->properlyInitialized(), "Printing system was not initialized while trying to save the output");

    outputStream->writeSystemReportHeader();

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
        int intCost = std::round(device->getCost());
        std::string deviceSpeed = "* Speed: " + std::to_string(device->getSpeed()) + " pages/minute";
        std::string deviceCost = "* Cost: " + std::to_string(intCost) + " cents/page";
        std::string deviceEmission = "* CO2: " + std::to_string(device->getEmissions()) + " g/page\n";

        outputStream->writeSystemReportDeviceInfo(deviceType, deviceName, deviceSpeed, deviceCost, deviceEmission);
    }
    outputStream->writeSystemReportJobsHeader();
    if (jobs.empty()) {
        outputStream->writeSystemReportNoPendingJobs();
    } else {
        for (auto &job: jobs) {
            std::string jobName = "[Job #" + std::to_string(job->getJobNR()) + "]";
            std::string jobUser = "* User: " + job->getUserName();
            std::string jobPageCount = "* Total Pages: " + std::to_string(job->getPageCount());
            std::string jobDevice = "* Device: " + (job->getDevice() ? job->getDevice()->getName() : "None");


            std::string jobCost = "* Total Cost: ";
            if (job->getDevice()) {
                int intCost = std::round(job->getDevice()->getCost());
                jobCost += std::to_string(intCost * job->getPageCount()) + " cents";
            } else {
                jobCost += "Needs device to calculate";
            }
            std::string jobEmission = "* Total CO2: " + (job->getDevice() ? std::to_string(job->getDevice()->getEmissions() * job->getPageCount()) + " g CO2": "Needs device to calculate");

            outputStream->writeSystemReportJobInfo(jobName, jobUser, jobPageCount, jobDevice, jobEmission, jobCost);
        }
    }
    outputStream->writeSystemReportFooter();
}

void PrintingSystem::advancedOutput(OutputStream *outputStream) {
    REQUIRE(this->properlyInitialized(), "Printing system was not initialized while trying to show the advanced output");

    outputStream->writeSystemDiagnosticTitle();

    for (auto& device : devices) {

        std::string jobqueue = "* Queued:";
        for (auto& job : device->getJobqueue()) {
            jobqueue += " [#" + std::to_string(job->getJobNR()) + " | " + std::to_string(job->getPageCount()) + "p]";
        }

        std::string jobfinished = "* Completed:";
        for (auto& job : device->getFinishedjobs()) {
            jobfinished += " [#" + std::to_string(job->getJobNR()) + " | " + std::to_string(job->getPageCount()) + "p]";
        }

        outputStream->writeAdvancedPerDeviceOutput(device->getDeviceType(), device->getName(),
                                                   jobqueue, jobfinished);
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
       outputStream->writeErrorJobNrNotFound(jobNR);
       return;
    }
    Device* processingdevice = jobToProcess->getDevice();

    if (!processingdevice) {
        outputStream->writeErrorNoDeviceOfCorrectType();
        return;
    }
    for (int i = 0; i < jobToProcess->getPageCount(); ++i) {
        outputStream->writePrintingPageNumber(i + 1);
    }
    processingdevice->addFinishedJob(jobToProcess);
    totalEmissions += jobToProcess->getPageCount() * processingdevice->getEmissions();

    outputStream->writeDeviceFinishedJob(jobToProcess->getJobType(), jobToProcess->getJobNR(),
                                         jobToProcess->getPageCount(),
                                         jobToProcess->getUserName(),
                                         processingdevice->getName());

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

void PrintingSystem::queueJobs() {
    REQUIRE(this->properlyInitialized(), "System was not properly initialized when trying to queue jobs");
    Device* currentdevice;
    for(auto job : jobs){
        currentdevice = nullptr;
        if (job->getDevice()) continue;
        for(auto device : devices){
            if(device->getDeviceType() == job->getJobType() && currentdevice == nullptr && !device->exceedslimit()){
                currentdevice = device;
            }
            if(device->getDeviceType() == job->getJobType() && !device->exceedslimit()){
                if(currentdevice->calculatevalue() > device->calculatevalue()){
                    currentdevice = device;
                }
            }
        }

        job->setDevice(currentdevice);
        if (currentdevice) {
            currentdevice->enqueue(job);
        }
    }
}

PrintingSystem::~PrintingSystem() {
    clearSystemBecauseInvalid();
}
