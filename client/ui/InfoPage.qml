import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.3

Page {
    id: infoPage

    Material.theme: Material.Light
    Material.accent: Material.Teal

    property string userName: "野獣先輩"
    property string realName: "田所 浩二"
    property int levelPassed: 114514
    property int experience: 114514
    property string levelText: "Total Level Passed: "
    property int utype: 1

    onUtypeChanged: {
        if(utype === 1)
            levelText = "Total Level Passed: "
        else
            levelText = "Total Word Added: "
    }

    ColumnLayout {
        width: parent.width
        spacing: 15
        anchors.centerIn: parent
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

        Rectangle {
            id: infoRect
            Layout.preferredWidth: 125
            Layout.preferredHeight: 125
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            color: Material.background

            Text {
                id: infoText
                text: qsTr("\uf6e2")
                anchors.centerIn: parent
                font.pointSize: 50
                font.family: "fontawesome"
                color: Material.accent
            }
        }

        Text {
            id: infoUserNameText
            text: userName
            font.pointSize: 30
            Layout.preferredHeight: 60
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        Text {
            id: infoUserRealNameText
            text: "Real Name: " + realName
            font.pointSize: 14
            Layout.preferredHeight: 40
            Layout.alignment: Qt.AlignHCenter
        }

        Text {
            id: infoUserExpText
            text: "Total Exp: " + experience
            font.pointSize: 14
            Layout.preferredHeight: 40
            Layout.alignment: Qt.AlignHCenter
        }

        Text {
            id: infoUserLevelText
            text: levelText + levelPassed
            font.pointSize: 14
            Layout.preferredHeight: 40
            Layout.alignment: Qt.AlignHCenter
        }

        Button {
            text: "OK"
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            onClicked: stackView.pop()
        }
    }
}
