#ifndef PROJECT_SOFTWAREENGINEERING_DEVICE_H
#define PROJECT_SOFTWAREENGINEERING_DEVICE_H

#include <string>
#include <vector>
namespace DeviceType {
    enum DeviceTypeEnum {color, bw, scan};
}
class Job;
class Device {
public:
    bool properlyInitialized();
/**
 Device will never be constructed with invalid parameters, because we check for that in the importer
 ENSURE(this->properlyInitialized(), "constructor must end in properlyInitialized state");
*/

    Device(const std::string &deviceName, int amountOfEmissions, int speedOfPrinter, int deviceCost);

/**
 REQUIRE(this->properlyInitialized(), "Device wasn't initialized when destructing device");
*/
    virtual ~Device();
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
    virtual std::string getDeviceType() = 0;
/**
  REQUIRE(this->properlyInitialized(), "Device wasn't initialized checking if it exceeds the CO2 limit");
 */
    virtual bool exceedslimit() = 0;

/**
 REQUIRE(this->properlyInitialized(), "Device wasn't initialized when calculating value");
*/
    int calculatevalue();
/**
 REQUIRE(this->properlyInitialized(), "Device wasn't initialized when adding to queue");
 ENSURE(find != jobqueue.end(), "job wasn't added to the queue");
 */
    void enqueue(Job*);
/**
 REQUIRE(this->properlyInitialized(), "Device wasn't initialized when getting queue");
 */
    std::vector<Job*> getJobqueue();
/**
 REQUIRE(this->properlyInitialized(), "Device wasn't initialized when getting finished jobs");
 */
    std::vector<Job*> getFinishedjobs();
/**
 REQUIRE(this->properlyInitialized(), "Device wasn't initialized when adding finished job");
 ENSURE(find != finishedjobs.end(), "job wasn't added to the queue");
 */
    void addFinishedJob(Job* finishedjob);

private:
    Device* _initCheck;

    std::string name;
    int emissions;
    int speed;
    float cost;
    std::vector<Job*> jobqueue;
    std::vector<Job*> finishedjobs;
};

/**
 Same contracts as device
*/

class ColorDevice : public Device {
public:
    ColorDevice(const std::string &deviceName, int amountOfEmissions, int speedOfPrinter, int deviceCost);
    std::string getDeviceType() override;
    bool exceedslimit() override;
};

class BWDevice : public Device {
public:
    BWDevice(const std::string &deviceName, int amountOfEmissions, int speedOfPrinter, int deviceCost);
    std::string getDeviceType() override;
    bool exceedslimit() override;
};

class ScanDevice : public Device {
public:
    ScanDevice(const std::string &deviceName, int amountOfEmissions, int speedOfPrinter, int deviceCost);
    std::string getDeviceType() override;
    bool exceedslimit() override;
};


#endif //PROJECT_SOFTWAREENGINEERING_DEVICE_H
