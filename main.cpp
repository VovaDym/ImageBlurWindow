#include <QApplication>
#include "./ui_blurWindow.h"
#include "blurmainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    BlurMainWindow window(nullptr);
    Ui::MainWindow blurWindow;
    blurWindow.setupUi(&window);
    window.label = blurWindow.label;
    window.horizontalSlider = blurWindow.horizontalSlider;
    window.horizontalSlider->setMaximum(10);
    window.horizontalSlider->setMinimum(0);
    window.resize(400, 600);
    window.show();
    return QApplication::exec();
}
