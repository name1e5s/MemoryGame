import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.3

Page {
    id: loginPage

    Material.theme: Material.Light
    Material.accent: Material.Teal
    Connections {
        target: game_client
        onLoginResult: {
            if(isSuccess) {
                if(gamerButton.checked)
                    stackView.push("qrc:/ui/ui/GamePage.qml",  {"userName" : userName,
                                                                "realName" : realName,
                                                                "levelPassed": levelPassed,
                                                                "experience": exp})
                else
                    stackView.push("qrc:/ui/ui/AdminPage.qml", {"userName" : userName,
                                       "realName" : realName,
                                       "levelPassed": levelPassed,
                                       "experience": exp})
            } else {
                popup.popMessage = "Login Failed!"
                popup.open()
            }
        }
    }

    Rectangle {
        id: logoRect
        width: parent.width
        height: parent.height * 0.5
        color: Material.background

        Text {
            id: logoText
            text: qsTr("\uf682")
            anchors.centerIn: parent
            font.pointSize: 130
            font.family: "fontawesome"
            color: Material.accent
        }
    }

    ColumnLayout {
        width: parent.width
        anchors.top: logoRect.bottom
        spacing: 15

        TextField {
            id: loginUsername
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
            Keys.onReturnPressed: {
                login()
            }
        }

        TextField {
            id: loginPassword
            placeholderText: qsTr("Password")
            Layout.preferredWidth: parent.width *0.7
            Layout.alignment: Qt.AlignHCenter
            font.pointSize: 14
            font.family: "fontawesome"
            leftPadding: 40
            echoMode: TextField.Password
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
            Keys.onReturnPressed: {
                login()
            }
        }

            RowLayout {
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                RadioButton {
                    id: gamerButton
                    text: qsTr("Gamer")
                    checked: true
                }
                RadioButton {
                    text: qsTr("Admin")
                }
            }


        Item {
            id: spaceItem
            height: 20
        }

        RowLayout {
            Layout.preferredWidth: parent.width * 0.6
            Layout.preferredHeight: 100
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            Button {
                Layout.preferredWidth: parent.width * 0.4
                Layout.preferredHeight: parent.height * 0.7
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                id: loginButton
                text: qsTr("Login")
                onClicked: login()
            }

            Button {
                Layout.preferredWidth: parent.width * 0.4
                Layout.preferredHeight: parent.height * 0.7
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                id: registerButton
                text: qsTr("Register")
                onClicked: {
                    stackView.push("qrc:/ui/ui/RegisterPage.qml")
                }
            }
        }
    }

    function login() {
        game_client.sendRequest("loginRequest", (gamerButton.checked? "1" : "0") + "$" +  loginUsername.text + "$" + loginPassword.text);
        loginUsername.clear()
        loginPassword.clear()
    }
}
