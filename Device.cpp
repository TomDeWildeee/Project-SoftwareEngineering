#include "DesignByContract.h"
#include "Device.h"

// Device will never be constructed with invalid parameters, because we check for that in the importer
Device::Device(const std::string &deviceName, int amountOfEmissions, int speedOfPrinter) {
    name = deviceName;
    emissions = amountOfEmissions;
    speed = speedOfPrinter;

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
