#include "DesignByContract.h"
#include "Device.h"
#include "Job.h"
#include <algorithm>
// Device will never be constructed with invalid parameters, because we check for that in the importer
Device::Device(const std::string &deviceName, int amountOfEmissions, int speedOfPrinter, DeviceType::DeviceTypeEnum deviceType, int deviceCost) {
    name = deviceName;
    emissions = amountOfEmissions;
    speed = speedOfPrinter;
    type = deviceType;
    cost = (float)deviceCost;

    _initCheck = this;
    ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
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

std::string Device::getDeviceType() {
    REQUIRE(this->properlyInitialized(), "Device wasn't initialized when getting type");
    if (type == DeviceType::color) {
        return "color";
    } else if (type == DeviceType::bw) {
        return "bw";
    } else {
        return "scan";
    }
}

float Device::getCost() {
    REQUIRE(this->properlyInitialized(), "Device wasn't initialized when getting value");
    return cost;
}

bool Device::exceedslimit() {
    REQUIRE(this->properlyInitialized(), "Device wasn't initialized checking if it exceeds the CO2 limit");
    if (type == DeviceType::color) {
        return this->getEmissions() > 23;
    } else if (type == DeviceType::bw) {
        return this->getEmissions() > 8;
    } else {
        return this->getEmissions() > 12;
    }
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
