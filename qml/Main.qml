import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 900
    height: 600
    title: "DiscordInQT"

    RowLayout {
        anchors.fill: parent

        Rectangle {
            Layout.preferredWidth: 200
            Layout.fillHeight: true
            color: "#2f3136"

            Column {
                anchors.fill: parent
                spacing: 5
                padding: 10

                Text {
                    text: "CANALES"
                    color: "lightgray"
                    font.bold: true
                }

                ListView {
                    id: channelList
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    model: ["general", "random"]

                    delegate: Rectangle {
                        width: parent.width
                        height: 40
                        color: ListView.isCurrentItem ? "gray" : "transparent"
                        radius: 5

                        Text {
                            text: modelData
                            color: "white"
                            anchors.centerIn: parent
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: channelList.currentIndex = index
                        }
                    }
                }
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true

            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "dimgray"

                ListView {
                    id: messageList
                    anchors.fill: parent
                    anchors.margins: 10

                    model: chatViewModel.messages

                    delegate: Rectangle {
                        width: parent.width
                        height: 50
                        color: "transparent"

                        Text {
                            text: modelData
                            color: "white"
                            wrapMode: Text.Wrap
                        }
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 60
                color: "gray"

                Row {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 10

                    TextField {
                        id: input
                        Layout.fillWidth: true
                        placeholderText: "Escribe un mensaje..."
                        color: "white"
                        background: Rectangle {
                            color: "black"
                            radius: 5
                        }
                    }

                    Button {
                        text: "Enviar"
                        onClicked: {
                            if (input.text !== "") {
                                chatViewModel.sendMessage(input.text)
                                input.text = ""
                            }
                        }
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        chatViewModel.connectToServer()
    }
}