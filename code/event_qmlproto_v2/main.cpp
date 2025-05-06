#include <QtQml/QQmlApplicationEngine>

#include <QtGui/QGuiApplication>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.loadFromModule("Event", "Main");
    if (engine.rootObjects().isEmpty())
        return -1;
    return QGuiApplication::exec();
}
