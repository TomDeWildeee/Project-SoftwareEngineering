#ifndef PROJECT_SOFTWAREENGINEERING_DEVICE_H
#define PROJECT_SOFTWAREENGINEERING_DEVICE_H

#include <string>

class Device {
public:
    Device(const std::string &deviceName, int amountOfEmissions, int speedOfPrinter);
    bool properlyInitialized();

    const std::string &getName() const;

    int getEmissions() const;

    int getSpeed() const;

private:
    Device* _initCheck;

    std::string name;
    int emissions;
    int speed;
};


#endif //PROJECT_SOFTWAREENGINEERING_DEVICE_H
