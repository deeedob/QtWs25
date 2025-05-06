import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

import Event
import Event.Proto

ApplicationWindow {
    id: root

    property event event        // from Event.Proto
    onEventChanged: serializer.update()
    property string data

    Serializer {                // from Event
        id: serializer
        onTypeChanged: update()
        function update() {
            root.data = serialize(root.event)
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 50

        Item { Layout.fillHeight: true }  // spacer

        RowLayout {
            Layout.fillWidth: true
            ComboBox {
                Layout.preferredWidth: 200
                model: [
                    { text: "UNKNOWN", value: Event.Type.UNKNOWN },
                    { text: "USER",    value: Event.Type.USER    },
                    { text: "SYSTEM",  value: Event.Type.SYSTEM  }
                ]
                textRole: "text"
                valueRole: "value"
                onActivated: root.event.type = currentValue
            }
            TextField {
                Layout.fillWidth: true
                text: root.event.name
                onTextEdited: root.event.name = text
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
                onActivated: serializer.type = currentValue
                textRole: "text"
                valueRole: "value"
            }
            TextField {
                Layout.fillWidth: true
                enabled: false
                text: serializer.display(root.data)
                color: Material.color(Material.Grey)
            }
            TextField {
                Layout.preferredWidth: 120
                enabled: false
                text: "size " + String(root.data).length
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
    Component.onCompleted: event.name = "Example.Event.QtWS"

    header: ToolBar {
        implicitHeight: 50
        Label {
            anchors.fill: parent
            text: "Event Serializer"
            font.pixelSize: 20
            font.bold: true
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
        }
    }
}
