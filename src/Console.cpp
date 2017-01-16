/#include "Console.h"  // <-- ADD THIS
#include <QSettings>  // <-- ADD THIS
#include "applicationui.hpp"
#include <bb/cascades/Application>
#include <QLocale>
#include <QTranslator>
#include <Qt/qdeclarativedebug.h>

using namespace bb::cascades;

void myMessageOutput(QtMsgType type, const char* msg) {  // <-- ADD THIS
    Q_UNUSED(type);  // <-- ADD THIS
    fprintf(stdout, "%s\n", msg);  // <-- ADD THIS
    fflush(stdout);  // <-- ADD THIS

    QSettings settings;  // <-- ADD THIS
    if (settings.value("sendToConsoleDebug", true).toBool()) {  // <-- ADD THIS -- Put this value to false if you want to stop sending logs to ConsoleDebug
        Console* console = new Console();  // <-- ADD THIS
        console->sendMessage("ConsoleThis$$" + QString(msg));  // <-- ADD THIS
        console->deleteLater();  // <-- ADD THIS
    }  // <-- ADD THIS
}  // <-- ADD THIS

Q_DECL_EXPORT int main(int argc, char **argv)
{
    Application app(argc, argv);

    qInstallMsgHandler(myMessageOutput);  // <-- ADD THIS

...
}
