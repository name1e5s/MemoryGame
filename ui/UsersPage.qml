import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.3
import com.name1e5s.game 1.0

Page {
    id: usersPage

    Material.theme: Material.Light
    Material.accent: Material.Teal

    property variant colname: ["User\n(uname)", "Real Name\n(rname)", "Experience\n(exp)", "Level Passed\n(level)"]

    RowLayout {
        width: parent.width
        height: parent.height

        TableView {
                id: tableView

                columnWidthProvider: function (column) { return width / 5; }
                rowHeightProvider: function (column) { return 60; }
                Layout.preferredHeight: parent.height
                Layout.preferredWidth: parent.width * 0.7
                leftMargin: rowsHeader.implicitWidth
                topMargin: columnsHeader.implicitHeight
                model: UserTableModel {
                    id: gamerTable
                    column: 4
                }
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
                    y: tableView.contentY
                    x: tableView.contentX
                    width: tableView.leftMargin
                    height: tableView.topMargin
                }

                Row {
                    id: columnsHeader
                    y: tableView.contentY
                    z: 2
                    Repeater {
                        id: columnsRepeater
                        model: tableView.columns > 0 ? tableView.columns : 1
                        Label {
                            width: tableView.columnWidthProvider(modelData)
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
                    x: tableView.contentX
                    z: 2
                    Repeater {
                        model: tableView.rows > 0 ? tableView.rows : 1
                        Label {
                            width: 70
                            height: tableView.rowHeightProvider(modelData)
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
                text: "SELECT * FROM users WHERE..."
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
                    searchGamer()
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

            RowLayout {
                Layout.preferredWidth: parent * 0.7
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                Button {
                    id: usersSearch
                    text: qsTr("Search")
                    Layout.alignment: Qt.AlignCenter
                    onClicked: {
                        searchGamer()
                    }
                }

                Button {
                    id: usersCancel
                    text: qsTr("Cancel")
                    Layout.alignment: Qt.AlignCenter
                    onClicked: stackView.pop()
                }
            }
        }
    }

    function searchGamer() {
        if(gamerButton.checked) {
            columnsRepeater.itemAt(3).text = "Level Passed\n(level)"
            gamerTable.searchGamer(searchBox.text === ""? "1 ORDER BY exp DESC" : searchBox.text)
        } else {
            columnsRepeater.itemAt(3).text = "Word Added\n(level)"
            gamerTable.searchAdmin(searchBox.text === ""? "1 ORDER BY exp DESC" : searchBox.text)
        }

        searchBox.clear()
    }
}
