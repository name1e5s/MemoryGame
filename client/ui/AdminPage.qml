import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.3
import com.name1e5s.game 1.0

Page {
    id: adminPage

    Material.theme: Material.Light
    Material.accent: Material.Teal
    property string userName: ""
    property string realName: ""
    property int levelPassed: 0
    property int experience: 0
    property int level: 0
    property variant colname: ["Word\n(word)", "Difficulty\n(dificulty = 1/2/3)", "Add User\n(uname)"]

    Connections {
        target: game_client
        onAddWordResult: {
            if(isSuccess) {
                experience += (level + 1) * 10
                levelPassed ++
                updateUser()
            } else {
                popup.popMessage = "Add word Failed!"
                popup.open()
            }
        }
    }

    onExperienceChanged: {
        level = (Math.sqrt(1 + 8 * experience / 50) + 1)/2 + 1
    }

    onVisibleChanged: {
        updateUser()
    }

    RowLayout {
        width: parent.width
        height: parent.height

        TableView {
                id: adminTableView

                columnWidthProvider: function (column) { return (width - 70) / 3; }
                rowHeightProvider: function (column) { return 60; }
                Layout.preferredHeight: parent.height
                Layout.preferredWidth: parent.width * 0.6
                leftMargin: rowsHeader.implicitWidth
                topMargin: columnsHeader.implicitHeight
                model: wordTableModel
                delegate: Item {
                    Text {
                        text: display
                        anchors.fill: parent
                        anchors.margins: 10

                        color: '#000000'
                        font.pixelSize: 15
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                }
                Rectangle { // mask the headers
                    z: 3
                    color: Material.accent
                    y: adminTableView.contentY
                    x: adminTableView.contentX
                    width: adminTableView.leftMargin
                    height: adminTableView.topMargin
                }

                Row {
                    id: columnsHeader
                    y: adminTableView.contentY
                    z: 2
                    Repeater {
                        model: adminTableView.columns > 0 ? adminTableView.columns : 1
                        Label {
                            width: adminTableView.columnWidthProvider(modelData)
                            height: 50
                            text: colname[modelData]
                            color: Material.background
                            font.pixelSize: 15
                            padding: 10
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter

                            background: Rectangle { color: Material.accent }
                        }
                    }
                }
                Column {
                    id: rowsHeader
                    x: adminTableView.contentX
                    z: 2
                    Repeater {
                        model: adminTableView.rows > 0 ? adminTableView.rows : 1
                        Label {
                            width: 70
                            height: adminTableView.rowHeightProvider(modelData)
                            text: "No. " + (modelData + 1)
                            color: Material.background
                            font.pixelSize: 15
                            padding: 10
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter

                            background: Rectangle { color: Material.accent }
                        }
                    }
                }

                ScrollIndicator.horizontal: ScrollIndicator { }
                ScrollIndicator.vertical: ScrollIndicator { }
            }

        ColumnLayout {
            Layout.preferredWidth: parent.width * 0.4
            Layout.alignment: Qt.AlignRight

            Text {
                text: "SELECT * FROM word WHERE..."
                color:  Material.color(Material.BlueGrey)
                Layout.alignment: Qt.AlignHCenter
            }

            TextField {
                id: searchBox
                placeholderText: qsTr("SQL query here ...")
                Layout.preferredWidth: parent.width * 0.8
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
                        text: "\uf1c0"
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
                Keys.onReturnPressed: {
                    searchWord()
                }
            }

            ColumnLayout {
                Layout.preferredWidth: parent.width * 0.8
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                TextField {
                    id: wordBox
                    placeholderText: qsTr("Add word...")
                    Layout.preferredWidth: parent.width
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
                            text: "\uf067"
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
                    Keys.onReturnPressed: {
                        addWord()
                    }
                }
            }

            RowLayout {
                Layout.preferredWidth: parent * 0.7
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                Button {
                    text: '\uf067'
                    Layout.alignment: Qt.AlignCenter
                    font.pointSize: 14
                    font.family: "fontawesome"
                    onClicked: {
                        addWord()
                    }
                }

                Button {
                    text: '\uf689'
                    Layout.alignment: Qt.AlignCenter
                    font.pointSize: 14
                    font.family: "fontawesome"
                    onClicked: {
                        searchWord()
                    }
                }

                Button {
                    text: "\uf129"
                    Layout.alignment: Qt.AlignCenter
                    font.pointSize: 14
                    font.family: "fontawesome"
                    onClicked: {
                        stackView.push("qrc:/ui/ui/InfoPage.qml", {"userName" : userName,
                                                                   "realName" : realName,
                                                                "levelPassed" : levelPassed,
                                                                 "experience" : experience,
                                                                 "utype"      : 0})
                    }
                }

                Button {
                    text: "\uf0c0"
                    Layout.alignment: Qt.AlignCenter
                    font.pointSize: 14
                    font.family: "fontawesome"
                    onClicked: {
                        stackView.push("qrc:/ui/ui/UsersPage.qml")
                    }
                }

                Button {
                    text: "\uf2f5"
                    Layout.alignment: Qt.AlignCenter
                    font.pointSize: 14
                    font.family: "fontawesome"
                    onClicked: {
                        game_client.sendRequest("logoutRequest", userName)
                        stackView.pop()
                    }
                }
            }
        }
    }

    function addWord() {
        if(wordBox.text === "") {
            popup.popMessage = "Add word Failed!"
            popup.open()
        } else {
            wordTableModel.addWord(wordBox.text, userName)
        }
        wordBox.clear()
    }

    function searchWord() {
        wordTableModel.searchWords(searchBox.text === ""? "1 ORDER BY difficulty" : searchBox.text)
        searchBox.clear()
    }

    function updateUser() {
        game_client.sendRequest("updateUserRequest", userName + "$" + levelPassed.toString() + "$" + experience.toString())
    }
}
