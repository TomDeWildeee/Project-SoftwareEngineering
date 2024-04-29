#ifndef PRINTINGSYSTEMGUI_H
#define PRINTINGSYSTEMGUI_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QFileDialog>
#include <QTextEdit>
#include "PrintingSystem.h"

// Heb redelijk wat moeten opzoeken om Qt te leren en deze GUI te maken. Veel van officiële documentatie
// maar ook van guicode van de Schaaktaak vorig semester

class PrintingSystemGUI : public QWidget {
public:
    PrintingSystemGUI(QWidget *parent = nullptr);
    ~PrintingSystemGUI();

private slots:
    void submitJob();
    void selectXMLFile();
    void selectOutputFile();
    void processSpecificJob();
    void processAllJobs();
    void saveOutput();
    void updateJobs();
    void updateDeviceBox();
    void jobTypeComboIndexChanged(int index);

private:
    QComboBox* jobTypeCombo;
    QComboBox* deviceComboBox;
    QTextEdit* jobDisplayBox;
    QPushButton* submitButton;
    QLineEdit* usernameEdit;
    QSpinBox* pageCountSpin;
    QPushButton* fileSelectButton;
    QPushButton* outputSelectButton;
    QPushButton* processSpecificJobButton;
    QPushButton* processAllJobsButton;
    QPushButton* saveOutputButton;
    QString selectedFilePath;
    QString outputFilePath;
    int currentJobNumber = 0;

    FileOutputStream *fileOutputStream;
    PrintingSystem printingSystem;
};

#endif // PRINTINGSYSTEMGUI_H
