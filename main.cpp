#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "commsserver.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<CommsServer>("com.ctdi.RasPiServer.CommsServer", 1, 0, "CommsServer");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
