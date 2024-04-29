#include <QApplication>
#include <iostream>
#include <fstream>
#include "PrintingSystemGUI.h"
#include "PrintingSystemImporter.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    PrintingSystemGUI window;
    window.setWindowTitle("Printing System GUI");

    window.show();

    return QApplication::exec();
}
