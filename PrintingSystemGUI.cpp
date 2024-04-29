#include "PrintingSystemGUI.h"
#include "PrintingSystemImporter.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QInputDialog>

// Heb redelijk wat moeten opzoeken om Qt te leren en deze GUI te maken. Veel van officiële documentatie
// maar ook van guicode van de Schaaktaak vorig semester

PrintingSystemGUI::PrintingSystemGUI(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    QFormLayout *formLayout = new QFormLayout();
    usernameEdit = new QLineEdit();
    jobTypeCombo = new QComboBox();
    jobTypeCombo->addItem("Black and White Printing");
    jobTypeCombo->addItem("Color Printing");
    jobTypeCombo->addItem("Scanning");
    pageCountSpin = new QSpinBox();
    deviceComboBox = new QComboBox();
    formLayout->addRow("Username:", usernameEdit);
    formLayout->addRow("Job Type:", jobTypeCombo);
    formLayout->addRow("Page Count:", pageCountSpin);
    formLayout->addRow("Device:", deviceComboBox);

    QVBoxLayout *buttonLayout = new QVBoxLayout();
    fileSelectButton = new QPushButton("Select XML File");
    outputSelectButton = new QPushButton("Select Output File");
    processSpecificJobButton = new QPushButton("Process Specific Job");
    processAllJobsButton = new QPushButton("Process All Jobs");
    saveOutputButton = new QPushButton("Save Output");
    submitButton = new QPushButton("Add Job");
    buttonLayout->addWidget(outputSelectButton);
    buttonLayout->addWidget(fileSelectButton);
    buttonLayout->addWidget(processSpecificJobButton);
    buttonLayout->addWidget(processAllJobsButton);
    buttonLayout->addWidget(saveOutputButton);

    jobDisplayBox = new QTextEdit();
    jobDisplayBox->setReadOnly(true);

    layout->addLayout(formLayout);
    layout->addWidget(submitButton);
    layout->addWidget(jobDisplayBox);

    QWidget *buttonWidget = new QWidget();
    buttonWidget->setLayout(buttonLayout);
    layout->addWidget(buttonWidget);

    fileSelectButton->setEnabled(false);
    processSpecificJobButton->setEnabled(false);
    processAllJobsButton->setEnabled(false);
    saveOutputButton->setEnabled(false);
    submitButton->setEnabled(false);

    connect(submitButton, &QPushButton::clicked, this, &PrintingSystemGUI::submitJob);
    connect(fileSelectButton, &QPushButton::clicked, this, &PrintingSystemGUI::selectXMLFile);
    connect(outputSelectButton, &QPushButton::clicked, this, &PrintingSystemGUI::selectOutputFile);
    connect(processSpecificJobButton, &QPushButton::clicked, this, &PrintingSystemGUI::processSpecificJob);
    connect(processAllJobsButton, &QPushButton::clicked, this, &PrintingSystemGUI::processAllJobs);
    connect(saveOutputButton, &QPushButton::clicked, this, &PrintingSystemGUI::saveOutput);
    connect(jobTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &PrintingSystemGUI::jobTypeComboIndexChanged);


    setLayout(layout);
}

PrintingSystemGUI::~PrintingSystemGUI() {
    delete fileOutputStream;
}

void PrintingSystemGUI::submitJob() {
    QString username = usernameEdit->text();
    QString jobType = jobTypeCombo->currentText();
    int pageCount = pageCountSpin->value();

    if (username.isEmpty() || pageCount <= 0) {
        QMessageBox::warning(this, "Warning", "Please fill in all fields correctly.");
        return;
    }
    auto jobTypeEnum = JobType::JobTypeEnum::bw;

    if (jobType == "Color Printing") {
        jobTypeEnum = JobType::JobTypeEnum::color;
    } else if (jobType == "Scanning") {
        jobTypeEnum = JobType::JobTypeEnum::scan;
    }

    QString selectedDeviceName = deviceComboBox->currentText();
    Device* selectedDevice = nullptr;
    for (const auto& device : printingSystem.getDevices()) {
        if (device->getName().c_str() == selectedDeviceName) {
            selectedDevice = device;
            break;
        }
    }

    if (!selectedDevice) {
        QMessageBox::warning(this, "Warning", "Please select a device.");
        return;
    }

    while(!printingSystem.isUniqueJobNumber(currentJobNumber)) {
        currentJobNumber++;
    }

    Job* job = new Job(currentJobNumber, pageCount, username.toStdString(), jobTypeEnum);
    job->setDevice(selectedDevice);
    selectedDevice->enqueue(job);
    printingSystem.addJob(job);

    updateJobs();

    QMessageBox::information(this, "Success", "Job submitted successfully!");
}

void PrintingSystemGUI::selectXMLFile() {
    selectedFilePath = QFileDialog::getOpenFileName(this, tr("Open XML File"), "", tr("XML Files (*.xml)"));
    if (selectedFilePath.isEmpty()) return;
    printingSystem.clearSystemBecauseInvalid();
    PrintingSystemImporter::importPrintingSystem(selectedFilePath.toStdString().c_str(), fileOutputStream, printingSystem);
    submitButton->setEnabled(true);
    saveOutputButton->setEnabled(true);
    processSpecificJobButton->setEnabled(true);
    processAllJobsButton->setEnabled(true);

    updateJobs();
    deviceComboBox->clear();

    jobTypeCombo->clear();
    jobTypeCombo->addItem("Black and White Printing");
    jobTypeCombo->addItem("Color Printing");
    jobTypeCombo->addItem("Scanning");


}

void PrintingSystemGUI::selectOutputFile() {
    outputFilePath = QFileDialog::getOpenFileName(this, tr("Open txt File"), "", tr("txt Files (*.txt)"));
    if (outputFilePath.isEmpty()) return;
    fileOutputStream = new FileOutputStream(outputFilePath.toStdString());
    fileSelectButton->setEnabled(true);
}

void PrintingSystemGUI::processSpecificJob() {
    bool ok;
    QString jobNRString = QInputDialog::getText(this, tr("Process Specific Job"),tr("Enter the Job Number:"), QLineEdit::Normal,"", &ok);
    if (ok && !jobNRString.isEmpty()) {
        int jobNR = jobNRString.toInt();

        printingSystem.processJob(fileOutputStream, jobNR);
        QMessageBox::information(this, "Success", "Job processed successfully!");
    }

    updateJobs();
}

void PrintingSystemGUI::processAllJobs() {
    printingSystem.processAllJobsAutomatically(fileOutputStream);
    QMessageBox::information(this, "Success", "All jobs processed successfully!");

    updateJobs();
}

void PrintingSystemGUI::saveOutput() {
    printingSystem.saveOutput(fileOutputStream);
    QMessageBox::information(this, "Success", "Output saved successfully!");
}

void PrintingSystemGUI::updateJobs() {
    jobDisplayBox->clear();

    std::vector<Device*> devices = printingSystem.getDevices();

    for (const auto& device : devices) {

        const std::vector<Job*>& queuedJobs = device->getJobqueue();
        for (const auto& job : queuedJobs) {
            jobDisplayBox->append("Job #" + QString::number(job->getJobNR()) + " - Status: Queued");
            jobDisplayBox->append("User: " + QString::fromStdString(job->getUserName()));
            jobDisplayBox->append("Page Count: " + QString::number(job->getPageCount()));
            jobDisplayBox->append("Device: " + QString::fromStdString(device->getName()));
            jobDisplayBox->append("--------");
        }

        const std::vector<Job*>& finishedJobs = device->getFinishedjobs();
        for (const auto& job : finishedJobs) {
            jobDisplayBox->append("Job #" + QString::number(job->getJobNR()) + " - Status: Printed");
            jobDisplayBox->append("User: " + QString::fromStdString(job->getUserName()));
            jobDisplayBox->append("Page Count: " + QString::number(job->getPageCount()));
            jobDisplayBox->append("Device: " + QString::fromStdString(device->getName()));
            jobDisplayBox->append("--------");
        }
    }
}

void PrintingSystemGUI::updateDeviceBox() {
    std::vector<Device*> devices = printingSystem.getDevices();
    for (const auto& device : devices) {
        std::string abbreviatedType;
        if (jobTypeCombo->currentText().toStdString() == "Black and White Printing") {
            abbreviatedType = "bw";
        } else if (jobTypeCombo->currentText().toStdString() == "Color Printing") {
            abbreviatedType = "color";
        } else {
            abbreviatedType = "scan";
        }

        if (device->getDeviceType() == abbreviatedType) {
            deviceComboBox->addItem(QString::fromStdString(device->getName()));
        } else {
            int index = deviceComboBox->findText(QString::fromStdString(device->getName()));
            if (index != -1) {
                deviceComboBox->removeItem(index);
            }
        }
    }
}

void PrintingSystemGUI::jobTypeComboIndexChanged(int index) {
    updateDeviceBox();
}


