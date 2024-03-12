#include "DesignByContract.h"
#include "Device.h"

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

const std::string &Device::getName() const {
    return name;
}

int Device::getEmissions() const {
    return emissions;
}

int Device::getSpeed() const {
    return speed;
}
