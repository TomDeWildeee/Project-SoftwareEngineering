#include "DesignByContract.h"
#include "Job.h"
#include "Device.h"

//Job will never be constructed with invalid parameters, because we check for that in the importer
Job::Job(int jobNr, int pageCt, const std::string &userN) {
    jobNumber = jobNr;
    pageCount = pageCt;
    userName = userN;

    _initCheck = this;
    ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

Job::~Job() {
    REQUIRE(this->properlyInitialized(), "Job wasn't initialized when destructing job");
}

bool Job::properlyInitialized() {
    return _initCheck == this;
}

int Job::getJobNR() {
    REQUIRE(this->properlyInitialized(), "Job wasn't initialized when getting jobnumber");
    return jobNumber;
}

const std::string &Job::getUserName() {
    REQUIRE(this->properlyInitialized(), "Job wasn't initialized when getting username");
    return userName;
}

int Job::getPageCount() {
    REQUIRE(this->properlyInitialized(), "Job wasn't initialized when getting pagecount");
    return pageCount;
}

Device *Job::getDevice() {
    REQUIRE(this->properlyInitialized(), "Job wasn't initialized when getting processing device");
    return device;
}

void Job::setDevice(Device* processingDevice) {
    REQUIRE(this->properlyInitialized(), "Job wasn't initialized when setting processing device");
    Job::device = processingDevice;
    ENSURE(processingDevice == device, "Device wasn't allocated properly");
}

PrinterJob::PrinterJob(int jobNr, int pageCt, const std::string &userN) : Job(jobNr, pageCt, userN) {}

PrinterJob::~PrinterJob() {
    REQUIRE(this->properlyInitialized(), "PrinterJob wasn't initialized when destructing Job");
}

ScanJob::ScanJob(int jobNr, int pageCt, const std::string &userN) : Job(jobNr, pageCt, userN) {}

std::string ScanJob::getJobType() {
    REQUIRE(this->properlyInitialized(), "Job wasn't initialized when getting job type");
    return "scan";
}

ColorJob::ColorJob(int jobNr, int pageCt, const std::string &userN) : PrinterJob(jobNr, pageCt, userN) {}

std::string ColorJob::getJobType() {
    REQUIRE(this->properlyInitialized(), "Printer Job wasn't initialized when getting job type");
    return "color";
}

BWJob::BWJob(int jobNr, int pageCt, const std::string &userN) : PrinterJob(jobNr, pageCt, userN) {}

std::string BWJob::getJobType() {
    REQUIRE(this->properlyInitialized(), "Printer Job wasn't initialized when getting job type");
    return "bw";
}

