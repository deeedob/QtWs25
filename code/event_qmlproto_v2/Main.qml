import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

import Event
import Event.Proto

ApplicationWindow {
    id: root

    Serializer {
        id: serializer
        type: serializeSelector.currentValue
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 50

        Item { Layout.fillHeight: true } // spacer

        RowLayout {
            Layout.fillWidth: true
            ComboBox {
                Layout.preferredWidth: 200
                model: [
                    { text: "UNKNOWN", value: Event.Type.UNKNOWN },
                    { text: "USER",    value: Event.Type.USER    },
                    { text: "SYSTEM",  value: Event.Type.SYSTEM  }
                ]
                onActivated: serializer.event.type = currentValue
                textRole: "text"
                valueRole: "value"
            }
            TextField {
                Layout.fillWidth: true
                text: serializer.event.name
                onTextChanged: serializer.event.name = text
            }
        }

        RowLayout {
            Layout.fillWidth: true
            ComboBox {
                id: serializeSelector
                model: [
                    { text: "Proto", value: Serializer.Proto },
                    { text: "Json", value: Serializer.Json },
                ]
                textRole: "text"
                valueRole: "value"
            }
            TextField {
                Layout.fillWidth: true
                text: serializer.display(serializer.data)
                enabled: false
                font.bold: true
                color: Material.color(Material.Grey)
            }
            TextField {
                Layout.preferredWidth: 120
                enabled: false
                text: "size " + String(serializer.data).length
                font.bold: true
            }
        }

        Item { Layout.fillHeight: true } // spacer
    }

    width: 800
    height: 500
    visible: true
    Material.theme: Material.Light
    Material.accent: Material.Purple
    Component.onCompleted: serializer.event.name = "Example.Event"

    header: ToolBar {
        implicitHeight: 50
        Label {
            anchors.fill: parent
            text: "Event Serializer v2"
            font.pixelSize: 20
            font.bold: true
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
        }
    }
}
