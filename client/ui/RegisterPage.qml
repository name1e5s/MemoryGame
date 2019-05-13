import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.3

Page {
    Material.theme: Material.Light
    Material.accent: Material.Teal
    Connections {
        target: game_client
        onRegisterResult: {
            if(isSuccess) {
                stackView.pop()
            } else {
                popup.popMessage = "Register Failed!"
                popup.open()
            }
        }
    }
    ColumnLayout {
        width: parent.width
        spacing: 15
        anchors.centerIn: parent
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

        TextField {
            id: registerUsername
            placeholderText: qsTr("User name")
            Layout.preferredWidth: parent.width * 0.7
            Layout.alignment: Qt.AlignHCenter

            font.pointSize: 14
            font.family: "fontawesome"
            leftPadding: 40
            background: Rectangle {
                implicitWidth: 200
                implicitHeight: 50
                radius: implicitHeight / 2
                color: "transparent"

                Text {
                    text: "\uf007"
                    font.pointSize: 14
                    font.family: "fontawesome"
                    color: Material.accent
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 10
                }

                Rectangle {
                    width: parent.width - 10
                    height: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    color: Material.accent
                }
            }
        }

        TextField {
            id: registerRealName
            placeholderText: qsTr("Real Name")
            Layout.preferredWidth: parent.width * 0.7
            Layout.alignment: Qt.AlignHCenter

            font.pointSize: 14
            font.family: "fontawesome"
            leftPadding: 40
            background: Rectangle {
                implicitWidth: 200
                implicitHeight: 50
                radius: implicitHeight / 2
                color: "transparent"
                Text {
                    text: "\uf05a"
                    font.pointSize: 13
                    font.bold: true
                    font.family: "fontawesome"
                    color: Material.accent
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 10
                }

                Rectangle {
                    width: parent.width - 10
                    height: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    color: Material.accent
                }
            }
        }

        TextField {
            id: registerPassword
            placeholderText: qsTr("Password")
            Layout.preferredWidth: parent.width * 0.7
            Layout.alignment: Qt.AlignHCenter

            font.pointSize: 14
            font.family: "fontawesome"
            leftPadding: 40
            echoMode: TextField.PasswordEchoOnEdit
            background: Rectangle {
                implicitWidth: 200
                implicitHeight: 50
                radius: implicitHeight / 2
                color: "transparent"
                Text {
                    text: "\uf023"
                    font.pointSize: 14
                    font.family: "fontawesome"
                    color: Material.accent
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 10
                }

                Rectangle {
                    width: parent.width - 10
                    height: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    color: Material.accent
                }
            }
        }

        TextField {
            id: registerPassword2
            placeholderText: qsTr("Confirm Password")
            Layout.preferredWidth: parent.width * 0.7
            Layout.alignment: Qt.AlignHCenter

            font.pointSize: 14
            font.family: "fontawesome"
            leftPadding: 40
            echoMode: TextField.PasswordEchoOnEdit
            background: Rectangle {
                implicitWidth: 200
                implicitHeight: 50
                radius: implicitHeight / 2
                color: "transparent"
                Text {
                    text: "\uf023"
                    font.pointSize: 14
                    font.family: "fontawesome"
                    color: Material.accent
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 10
                }

                Rectangle {
                    width: parent.width - 10
                    height: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    color: Material.accent
                }
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            RadioButton {
                id: regGamer
                text: qsTr("Gamer")
                checked: true
            }
            RadioButton {
                text: qsTr("Admin")
            }
        }

        RowLayout {
            Layout.preferredWidth: parent.width * 0.6
            Layout.preferredHeight: 100
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            Button {
                Layout.preferredWidth: parent.width * 0.4
                Layout.preferredHeight: parent.height * 0.7
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                id: confirmRegisterButton
                text: qsTr("Register")
                onClicked: {
                    var uname = registerUsername.text
                    var pass1 = registerPassword.text
                    var pass2 = registerPassword2.text
                    var rname = registerRealName.text
                    if(uname === "" || pass1 === "" || pass2 === "" || rname === "") {
                        popup.popMessage = "More infomation needed!"
                        popup.open()
                    } else if(pass1 !== pass2) {
                        popup.popMessage = "Password unmatch!"
                        popup.open()
                    } else {
                        game_client.sendRequest("registerRequest", (regGamer.checked? "1" : "0") + "$" + uname + "$" + rname + "$" + pass1)
                    }
                }
            }

            Button {
                Layout.preferredWidth: parent.width * 0.4
                Layout.preferredHeight: parent.height * 0.7
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                id: cancelRegisterButton
                text: qsTr("Cancel")
                onClicked: stackView.pop()
            }
        }

    }
}
