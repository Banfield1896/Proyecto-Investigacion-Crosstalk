#include <iostream>
#include "AppWindow.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    AppWindow window;
    window.show();
    return app.exec();

}
