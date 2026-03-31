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

                ColumnLayout {
                    anchors.fill: parent
                    spacing: 5

                    Text {
                        text: "CANALES"
                        color: "lightgray"
                        font.bold: true
                    }

                    ListView {
                        id: channelList
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        model: ["General", "Juegos", "AFK"]

                        delegate: Rectangle {
                            width: ListView.view.width
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

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    spacing: 2

                    Rectangle {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        color: "dimgray"

                        ListView {
                            id: messageList
                            anchors.fill: parent
                            anchors.margins: 10

                            model: chatViewModel.messages

                            delegate: Text {
                                width: messageList.width
                                text: modelData
                                color: "white"
                                wrapMode: Text.Wrap
                            }

                            onCountChanged: positionViewAtEnd()
                        }
                    }

                    Text {
                        Layout.fillWidth: true
                        Layout.leftMargin: 10
                        text: chatViewModel.typingText
                        visible: chatViewModel.typingText !== ""
                        color: "black"
                        font.italic: true
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

                            property bool isTyping: false

                            Timer {
                                id: typingTimer
                                interval: 2000
                                repeat: false

                                onTriggered: {
                                    input.isTyping = false
                                    chatViewModel.sendTyping(chatViewModel.username, false)
                                }
                            }

                            onTextChanged: {

                                if (!isTyping) {
                                    isTyping = true
                                    chatViewModel.sendTyping(chatViewModel.username, true)
                                }

                                typingTimer.restart()
                            }

                            onAccepted: {

                                if (text !== "") {

                                    chatViewModel.sendMessage(text)

                                    chatViewModel.sendTyping(chatViewModel.username, false)

                                    text = ""
                                    isTyping = false

                                    typingTimer.stop()
                                }
                            }

                            onActiveFocusChanged: {

                                if (!activeFocus && isTyping) {

                                    isTyping = false
                                    chatViewModel.sendTyping(chatViewModel.username, false)

                                    typingTimer.stop()
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