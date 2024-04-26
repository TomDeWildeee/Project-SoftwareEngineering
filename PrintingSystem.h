#ifndef PROJECT_SOFTWAREENGINEERING_PRINTINGSYSTEM_H
#define PROJECT_SOFTWAREENGINEERING_PRINTINGSYSTEM_H

#include <iostream>
#include <vector>
#include "Device.h"
#include "Job.h"
#include "Output.h"

class PrintingSystem {
public:
    bool properlyInitialized();
/**
 ENSURE(this->properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    PrintingSystem();

/**
 REQUIRE(this->properlyInitialized(), "Printing system was not properly initialized when trying to check if a job number is unique");
*/
    bool isUniqueJobNumber(int jobNR);

/**
 REQUIRE(this->properlyInitialized(), "Printing system was not properly initialized when trying to clear it");
 ENSURE(devices.empty(), "Devices vector wasn't empty after clearing system");
 ENSURE(jobs.empty(), "Jobs vector wasn't empty after clearing system");
*/
    void clearSystemBecauseInvalid();

/**
 REQUIRE(this->properlyInitialized(), "Printing system was not properly initialized when trying to add a device");
*/
    void addDevice(Device* device);

/**
 REQUIRE(this->properlyInitialized(), "Printing system was not properly initialized when trying to add a job");
*/
    void addJob(Job* job);

/**
 REQUIRE(this->properlyInitialized(), "Printing system was not initialized while trying to save the output");
 ENSURE(!outputFile.is_open(), "File was not closed after writing out to it");
*/
    void saveOutput(OutputStream* outputStream);

/**
 REQUIRE(this->properlyInitialized(), "System was not properly initialized when trying to process a job");
 REQUIRE(!devices.empty(), "There has to be at least 1 printer available to process a job");
 REQUIRE(!jobs.empty(), "There are no jobs that can be processed by a device");
 ENSURE(std::find(jobs.begin(), jobs.end(), jobToProcess) == jobs.end(), "Processed job wasn't deleted out of the system");
*/
    void processJob(OutputStream* outputStream, int jobNR);

/**
 REQUIRE(this->properlyInitialized(), "System was not properly initialized when trying to automatically process jobs");
 REQUIRE(!devices.empty(), "There has to be at least 1 printer available to process jobs automatically");
 REQUIRE(!jobs.empty(), "There are no jobs that can be processed by a device");
 ENSURE(jobs.empty(), "Not all jobs were processed after trying to process all the jobs");
*/
    void processAllJobsAutomatically(OutputStream* outputStream);
/**
 REQUIRE(this->properlyInitialized(), "System was not properly initialized when trying to get jobs");
*/
    std::vector<Job*> getJobs();

private:
    PrintingSystem* _initCheck;

    std::vector<Device*> devices;
    std::vector<Job*> jobs;

};


#endif //PROJECT_SOFTWAREENGINEERING_PRINTINGSYSTEM_H
