#include <QColor>
#include <QGuiApplication>
#include <QMap>
#include <QObject>
#include <QQuickItem>
#include <QQuickView>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView view(QStringLiteral("qrc:/main.qml"));

    view.show();
    return app.exec();
}
