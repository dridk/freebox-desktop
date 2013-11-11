import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

Rectangle {
    id:root
    color: "white"
    width: 500
    height: loader.height
    property alias title : label.text
    property alias content : loader.sourceComponent
    Row {
        anchors.fill: parent
        Item {
            id:lab
            width: 100
            height: parent.height
            Button {
                id:label
//                font.pixelSize: 14
//                font.bold: true
//                color: "darkgray"
            }

        }

        Item {
            width: root.width - lab.width
            height: parent.height
            Loader {
                id:loader
            }

        }


    }


}
