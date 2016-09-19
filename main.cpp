#include <QColor>
#include <QGuiApplication>
#include <QMap>
#include <QObject>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQmlError>
#include <QQuickItem>
#include <QQuickView>

void dumpErrors(const QString& aSite, QQmlComponent* aComponentPtr)
{
    printf("Dumping errors for %s\n", aSite.toLatin1().constData());
    if (aComponentPtr->isError()) {
        QList<QQmlError> myList = aComponentPtr->errors();
        for (auto& i : myList) {
            printf("  error: '%s'.\n", i.toString().toLatin1().constData());
        }
        exit(1);
    }
    printf("  no errors found.\n");
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView view(QStringLiteral("qrc:/main.qml"));
    view.show();

    QQmlEngine *myEnginePtr = view.engine();
    QQuickItem* myBlackRectPtr = view.rootObject()->findChild<QQuickItem*>("myrect1");
    if (nullptr == myBlackRectPtr) {
        printf("ERROR: no myrect1 found\n");
        exit(-1);
    }


    //
    //  *** APPROACH 1
    //
    QQmlComponent myNewComponent(myEnginePtr, QUrl("qrc:/RRect.qml"), view.rootObject());
    dumpErrors("myNewComponent", &myNewComponent);
    QQuickItem* myItemPtr = qobject_cast<QQuickItem*>(myNewComponent.create());
    myItemPtr->setParentItem(myBlackRectPtr);
    myItemPtr->setProperty("anchors.horizontalCenter", "parent.horizontalCenter"); // ignored - format is wrong
    myItemPtr->setProperty("color", "blue");
    myItemPtr->setProperty("y", "40");


    //
    //  *** APPROACH 2
    //
    QString myObjectDescription("import QtQuick 2.0; RRect { anchors.horizontalCenter: parent.horizontalCenter; anchors.verticalCenter: parent.verticalCenter; color: \"red\" }");
    QQmlContext myContext(myEnginePtr, myBlackRectPtr);

    QQmlComponent my2Component(myEnginePtr);
    dumpErrors("my2Component after construction", &my2Component);
    my2Component.setData("RRect { width: 300; height: 70; anchors.horizontalCenter: parent.horizontalCenter; anchors.verticalCenter: parent.verticalCenter; color: \"red\" }",
                          QUrl("qrc:/main.qml"));
    dumpErrors("my2Component after setData", &my2Component);
    QQuickItem* my2ItemPtr = qobject_cast<QQuickItem*>(my2Component.create(&myContext));
    dumpErrors("my2Component after create()", &my2Component);
    my2ItemPtr->setParentItem(myBlackRectPtr);

    return app.exec();
}
