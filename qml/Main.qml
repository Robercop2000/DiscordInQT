import QtQuick
import QtQuick.Controls

ApplicationWindow {
    visible: true
    width: 400
    height: 600
    title: "DiscordInQT"

    Column {
        anchors.fill: parent
        spacing: 10

        ListView {
            id: listView
            height: parent.height - inputRow.height - 60
            width: parent.width
            model: chatViewModel.messages

            delegate: Rectangle {
                width: parent.width
                height: 40

                Text {
                    text: modelData
                    anchors.centerIn: parent
                }
            }
        }

        Row {
            id: inputRow
            width: parent.width
            height: 50
            spacing: 5

            TextField {
                id: input
                width: parent.width * 0.7
            }

            Button {
                text: "Send"
                onClicked: {
                    chatViewModel.sendMessage(input.text)
                    input.text = ""
                }
            }
        }

        Button {
            text: "Connect"
            onClicked: chatViewModel.connectToServer()
        }
    }
}