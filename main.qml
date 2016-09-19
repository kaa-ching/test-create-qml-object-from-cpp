import QtQuick 2.5
import QtQuick.Window 2.2

Item {
    visible: true
    width: 640
    height: 480

    Rectangle {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        id: myrect1
        objectName: "myrect1"
        border.color: "black"
        width: 400
        height: 200
        gradient:
            Gradient {
            GradientStop {position: 0.3; color: "#303030" }
            GradientStop {position: 0.7; color: "#707070" }
        }

        Text {
            text: "We should get smaller BLUE and RED rounded rectangles inside..."
        }

    }

}
