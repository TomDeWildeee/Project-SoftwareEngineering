#include "DesignByContract.h"
#include "Device.h"
#include "Job.h"
#include <algorithm>
// Device will never be constructed with invalid parameters, because we check for that in the importer
Device::Device(const std::string &deviceName, int amountOfEmissions, int speedOfPrinter, int deviceCost) {
    name = deviceName;
    emissions = amountOfEmissions;
    speed = speedOfPrinter;
    cost = (float) deviceCost;

    _initCheck = this;
    ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

Device::~Device() {
    REQUIRE(this->properlyInitialized(), "Device wasn't initialized when destructing device");
    // Jobs already get deleted in printingsystem so no need to delete them from the queue here
}

bool Device::properlyInitialized() {
    return _initCheck == this;
}

const std::string &Device::getName() {
    REQUIRE(this->properlyInitialized(), "Device wasn't initialized when getting name");
    return name;
}

int Device::getEmissions() {
    REQUIRE(this->properlyInitialized(), "Device wasn't initialized when getting emissions");
    return emissions;
}

int Device::getSpeed() {
    REQUIRE(this->properlyInitialized(), "Device wasn't initialized when getting speed");
    return speed;
}

float Device::getCost() {
    REQUIRE(this->properlyInitialized(), "Device wasn't initialized when getting value");
    return cost;
}

int Device::calculatevalue(){
    REQUIRE(this->properlyInitialized(), "Device wasn't initialized when getting queue");
    int value = 0;
    for(auto job : jobqueue){
        value += job->getPageCount();
    }
    return value * emissions;
}

void Device::enqueue(Job* job){
    REQUIRE(this->properlyInitialized(), "Device wasn't initialized when adding to queue");
    jobqueue.push_back(job);
    auto find = std::find(jobqueue.begin(),jobqueue.end(), job);
    ENSURE(find != jobqueue.end(), "job wasn't added to the queue");
}

std::vector<Job*> Device::getJobqueue(){
    REQUIRE(this->properlyInitialized(), "Device wasn't initialized when getting queue");
    return jobqueue;
}

std::vector<Job*> Device::getFinishedjobs(){
    REQUIRE(this->properlyInitialized(), "Device wasn't initialized when getting finished jobs");
    return finishedjobs;
}

void Device::addFinishedJob(Job *finishedjob) {
    REQUIRE(this->properlyInitialized(), "Device wasn't initialized when adding finished job");
    jobqueue.erase(jobqueue.begin());
    finishedjobs.push_back(finishedjob);
    auto find = std::find(finishedjobs.begin(),finishedjobs.end(), finishedjob);
    ENSURE(find != finishedjobs.end(), "job wasn't added to the queue");
}

ColorDevice::ColorDevice(const std::string &deviceName, int amountOfEmissions, int speedOfPrinter, int deviceCost)
    : Device(deviceName, amountOfEmissions, speedOfPrinter, deviceCost) {}

std::string ColorDevice::getDeviceType() {
    REQUIRE(this->properlyInitialized(), "Device wasn't initialized when getting type");
    return "color";
}

bool ColorDevice::exceedslimit() {
    REQUIRE(this->properlyInitialized(), "Colored Device wasn't initialized checking if it exceeds the CO2 limit");
    return this->getEmissions() > 23;
}

BWDevice::BWDevice(const std::string &deviceName, int amountOfEmissions, int speedOfPrinter, int deviceCost) : Device(
        deviceName, amountOfEmissions, speedOfPrinter, deviceCost) {}

std::string BWDevice::getDeviceType() {
    REQUIRE(this->properlyInitialized(), "Device wasn't initialized when getting type");
    return "bw";
}

bool BWDevice::exceedslimit() {
    REQUIRE(this->properlyInitialized(), "B&W Device wasn't initialized checking if it exceeds the CO2 limit");
    return this->getEmissions() > 8;
}

ScanDevice::ScanDevice(const std::string &deviceName, int amountOfEmissions, int speedOfPrinter, int deviceCost)
        : Device(deviceName, amountOfEmissions, speedOfPrinter, deviceCost) {}

std::string ScanDevice::getDeviceType() {
    REQUIRE(this->properlyInitialized(), "wasn't initialized when getting type");
    return "scan";
}

bool ScanDevice::exceedslimit() {
    REQUIRE(this->properlyInitialized(), "Scanner wasn't initialized checking if it exceeds the CO2 limit");
    return this->getEmissions() > 12;
}
