#ifndef PROJECT_SOFTWAREENGINEERING_JOB_H
#define PROJECT_SOFTWAREENGINEERING_JOB_H

#include <string>
//#include "Device.h"

namespace JobType {
    enum JobTypeEnum {color, bw, scan};
}
class Device;
class Job {
public:
    bool properlyInitialized();
/**
 Job will never be constructed with invalid parameters, because we check for that in the importer
 ENSURE(this->properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Job(int jobNr, int pageCt, const std::string &userN);

/**
 REQUIRE(this->properlyInitialized(), "Job wasn't initialized when destructing job");
*/
    virtual ~Job();
/**
 REQUIRE(this->properlyInitialized(), "Job wasn't initialized when getting jobnumber");
*/
    int getJobNR();

/**
 REQUIRE(this->properlyInitialized(), "Job wasn't initialized when getting username");
*/
    const std::string &getUserName();

/**
 REQUIRE(this->properlyInitialized(), "Job wasn't initialized when getting pagecount");
*/
    int getPageCount();

/**
 REQUIRE(this->properlyInitialized(), "Job wasn't initialized when getting job type");
*/
    virtual std::string getJobType() = 0;

/**
 REQUIRE(this->properlyInitialized(), "Job wasn't initialized when getting processing device");
*/
    Device *getDevice();

/**
 REQUIRE(this->properlyInitialized(), "Job wasn't initialized when setting processing device");
 ENSURE(processingdevice == device, "Device wasn't allocated properly");
*/
    void setDevice(Device *processingDevice);

private:
    Job* _initCheck;
    int jobNumber;
    int pageCount;
    std::string userName;
    Device* device = nullptr;
};

/**
 Same contracts as job
*/

class ScanJob : public Job {
public:
    ScanJob(int jobNr, int pageCt, const std::string &userN);
    std::string getJobType() override;
};

class PrinterJob : public Job {
public:
    PrinterJob(int jobNr, int pageCt, const std::string &userN);
    virtual ~PrinterJob();
};

class ColorJob : public PrinterJob {
public:
    ColorJob(int jobNr, int pageCt, const std::string &userN);
    std::string getJobType() override;
};

class BWJob : public PrinterJob {
public:
    BWJob(int jobNr, int pageCt, const std::string &userN);
    std::string getJobType() override;
};

#endif //PROJECT_SOFTWAREENGINEERING_JOB_H