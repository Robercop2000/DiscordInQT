import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 900
    height: 600
    title: "DiscordInQT"

    ColumnLayout {
        anchors.fill: parent

        Rectangle {
            Layout.fillWidth: true
            height: 50
            color: "black"

            Row {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 10

                Button {
                    text: "Conectar"
                    onClicked: chatViewModel.connectToServer()
                }

                Text {
                    text: chatViewModel.isConnected ? "Conectado" : "Desconectado"
                    color: chatViewModel.isConnected ? "lightgreen" : "red"
                }

                TextField {
                    id: usernameInput
                    width: 150
                    placeholderText: "Usuario"
                    text: chatViewModel.username

                    onEditingFinished: chatViewModel.username = text
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true

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
                        anchors.fill: parent
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

                    Column {
                        anchors.fill: parent

                        ListView {
                            id: messageList
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.top: parent.top
                            anchors.bottom: parent.bottom
                            anchors.margins: 10

                            model: chatViewModel.messages

                            delegate: Text {
                                width: messageList.width
                                text: modelData
                                color: "white"
                                wrapMode: Text.Wrap
                            }
                        }

                        Text {
                            id: typingText
                            width: parent.width
                            text: chatViewModel.typingUser !== "" ?
                                  chatViewModel.typingUser + " está escribiendo..." : ""
                            color: "lightgray"
                        }
                    }
                }

                Rectangle {
                    Layout.fillWidth: true
                    height: 60
                    color: "gray"

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 10
                        spacing: 10

                        TextField {
                            id: input
                            Layout.fillWidth: true
                            placeholderText: "Escribe un mensaje..."
                            color: "black"

                            onTextChanged: {
                                if (text.length > 0)
                                    chatViewModel.sendTyping(chatViewModel.username)
                                else
                                    chatViewModel.sendTyping("")
                            }

                            onActiveFocusChanged: {
                                if (!activeFocus)
                                    chatViewModel.sendTyping("")
                            }

                            onAccepted: {
                                if (text !== "") {
                                    chatViewModel.sendMessage(text)
                                    chatViewModel.sendTyping("")
                                    text = ""
                                }
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
    }
}