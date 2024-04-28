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
    void writeLine(const std::string& message) override;
    ~FileOutputStream() override;
};

class ConsoleOutputStream : public OutputStream {
public:
    void writeLine(const std::string& message) override;
};

class NoOutputStream : public OutputStream {
public:
    void writeLine(const std::string& message) override;
};