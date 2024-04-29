#include <string>
#include <fstream>
#include <iostream>
#include "DesignByContract.h"

class OutputStream {
    OutputStream* _initCheck;
public:
    OutputStream();
    bool properlyInitialized();
    virtual void writeLine(const std::string& message) = 0;
    virtual ~OutputStream() = default;
};

class FileOutputStream : public OutputStream {
private:
    std::ofstream outputFile;
public:
    explicit FileOutputStream(const std::string& filename = "output.txt") : outputFile(filename) {}
/**
 REQUIRE(this->properlyInitialized(), "FileOutputStream wasn't initialized when writing line");
 */
    void writeLine(const std::string& message) override;
    ~FileOutputStream() override;
};

class ConsoleOutputStream : public OutputStream {
public:
/**
 REQUIRE(this->properlyInitialized(), "ConsoleOutputStream wasn't initialized when writing line");
 */
    void writeLine(const std::string& message) override;
};

class NoOutputStream : public OutputStream {
public:
/**
 REQUIRE(this->properlyInitialized(), "NoOutputStream wasn't initialized when writing line");
 */
    void writeLine(const std::string& message) override;
};