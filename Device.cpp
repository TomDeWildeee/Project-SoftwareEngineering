#include "DesignByContract.h"
#include "Device.h"

// Device will never be constructed with invalid parameters, because we check for that in the importer
Device::Device(const std::string &deviceName, int amountOfEmissions, int speedOfPrinter, DeviceType::DeviceTypeEnum deviceType, int deviceCost) {
    name = deviceName;
    emissions = amountOfEmissions;
    speed = speedOfPrinter;
    type = deviceType;
    cost = deviceCost;

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

DeviceType::DeviceTypeEnum Device::getDeviceType() {
    REQUIRE(this->properlyInitialized(), "Device wasn't initialized when getting type");
    return type;
}

float Device::getCost() {
    REQUIRE(this->properlyInitialized(), "Device wasn't initialized when getting value");
    return cost;
}
