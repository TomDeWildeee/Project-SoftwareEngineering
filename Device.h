#ifndef PROJECT_SOFTWAREENGINEERING_DEVICE_H
#define PROJECT_SOFTWAREENGINEERING_DEVICE_H

#include <string>

namespace DeviceType {
    enum DeviceTypeEnum {color, bw, scan};
}

class Device {
public:
    bool properlyInitialized();
/**
 Device will never be constructed with invalid parameters, because we check for that in the importer
 ENSURE(this->properlyInitialized(), "constructor must end in properlyInitialized state");
*/

    Device(const std::string &deviceName, int amountOfEmissions, int speedOfPrinter, DeviceType::DeviceTypeEnum deviceType, int deviceCost);

/**
 REQUIRE(this->properlyInitialized(), "Device wasn't initialized when getting name");
*/
    const std::string &getName();

/**
 REQUIRE(this->properlyInitialized(), "Device wasn't initialized when getting emissions");
*/
    int getEmissions();

/**
 REQUIRE(this->properlyInitialized(), "Device wasn't initialized when getting speed");
*/
    int getSpeed();
/**
 REQUIRE(this->properlyInitialized(), "Device wasn't initialized when gettting value");
 */
    float getCost();

/**
 REQUIRE(this->properlyInitialized(), "Device wasn't initialized when getting type");
*/
    std::string getDeviceType();

private:
    Device* _initCheck;

    std::string name;
    int emissions;
    int speed;
    DeviceType::DeviceTypeEnum type;
    float cost;

};


#endif //PROJECT_SOFTWAREENGINEERING_DEVICE_H
