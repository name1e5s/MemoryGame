import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.3
import com.name1e5s.game 1.0

Page {
    id: gamePage

    Material.theme: Material.Light
    Material.accent: Material.Teal

    property string userName: ""
    property string realName: ""
    property int levelPassed: 0
    property int experience: 0
    property int level: 1
    property int cycles: 0
    property int rounds: 0
    property string resultWord: ""
    property string faceString: '\uf4da'
    property string answerString: '\uf058'

    Connections {
        target: game_client
        onGetWordResult: {
                resultWord = word
                gameText.text = word
                faceText.text = '\uf35b'
                inputTextField.enabled = false
                gameTextChangedTimer.interval = (3 - difficultySpinBox.value) * 1000
                gameTextChangedTimer.start()
                startGameButton.enabled = false
        }
    }

    onVisibleChanged: {
        cycles = 0
    }

    onExperienceChanged: {
        level = (Math.sqrt(1 + 8 * experience / 50) + 1)/2 + 1
    }

    onCyclesChanged: {
        if(Math.abs(cycles) < 5)
            faceString = '\uf5a4'
        else if(Math.abs(cycles) < 10) {
            if(cycles > 0)
                faceString = '\uf580'
            else
                faceString = '\uf11a'
        } else {
            if(cycles > 0)
                faceString = '\uf585'
            else
                faceString = '\uf567'
        }
        faceText.text = faceString
    }

    Timer {
        id: gameTextChangedTimer
        interval: 2000
        onTriggered: {
            gameText.text = "Type It !"
            faceText.text = faceString
            inputTextField.enabled = true
            inputTextField.focus = true;
        }
    }

    ColumnLayout {
        width: parent.width
        height: parent.height
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        spacing: 0

        RowLayout {
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: parent.height * 0.1
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            Text {
                id: gameText
                Layout.preferredHeight: parent.height
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                text: "Welcome!"
                font.pointSize: 50
            }
        }


        ColumnLayout {
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: parent.height * 0.9
            Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom

            TextField {
                id: inputTextField
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredWidth: parent.width * 0.9
                Layout.preferredHeight: parent.height
                font.pointSize: 120
                background: null
                enabled: false
                horizontalAlignment: TextInput.AlignHCenter
                Keys.onReturnPressed: {
                    // Check Answer
                    if(text === resultWord) {
                        answerString = '\uf058'
                        answerText.color = Material.accent
                        experience = experience + level * (difficultySpinBox.value + 1) * 5
                        cycles += 1
                        levelPassed += 1
                        rounds -= 1
                        console.log(rounds)
                        if(rounds === 0) {
                            inputTextField.enabled = false
                            gameText.text = "You Win!"
                            updateUser()
                            startGameButton.enabled = true
                            levelPassed ++
                        } else {
                            newGame()
                        }
                    } else {
                        answerString = '\uf057'
                        answerText.color = Material.color(Material.Red)
                        cycles -= 1
                    }
                    inputTextField.clear()
                }
            }
        }

        ColumnLayout{
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: parent.height * 0.1
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            RowLayout {
                Layout.preferredHeight: parent.height * 2 / 3
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                Text {
                    id: faceText
                    Layout.preferredHeight: parent.height
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    text: faceString
                    font.family: "fontawesome"
                    font.pointSize: 40
                    color: Material.accent
                }

                Rectangle {
                    Layout.preferredWidth: 50
                    Layout.preferredHeight: parent.height
                    color: Material.background
                }

                Text {
                    id: answerText
                    Layout.preferredHeight: parent.height
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    text: answerString
                    font.family: "fontawesome"
                    font.pointSize: 40
                    color: Material.accent
                }
            }

            Rectangle {
                Layout.preferredHeight: parent.height / 3
            }
        }

        RowLayout {
            id: gamePageControlLayout
            width: parent.width
            height: 50
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            RowLayout {
                id: userInfoLayout
                Layout.preferredWidth: parent.width * 0.4
                Layout.preferredHeight: 50
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                spacing: 0

                Text {
                    id: userNameText
                    Layout.preferredWidth: parent.width * 0.5
                    text: "Name: " + userName
                    font.pointSize: 12
                }
                Text {
                    id: userLevelText
                    Layout.preferredWidth: parent.width * 0.2
                    text: "Level: " + level
                    font.pointSize: 12
                }
                Text {
                    id: userExperienceText
                    Layout.preferredWidth: parent.width * 0.2
                    text: "Exp: " + experience
                    font.pointSize: 12
                }
            }

            RowLayout {
                id: gameControlLayout
                Layout.preferredWidth: parent.width * 0.6
                Layout.preferredHeight: parent.height
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                spacing: 0

                Text {
                    Layout.preferredWidth: parent.width * 0.1
                    text: "Difficulty: "
                    font.pointSize: 12
                }

                SpinBox {
                    id: difficultySpinBox
                    Layout.preferredWidth: parent.width * 0.3
                    Layout.preferredHeight: parent.height
                    from: 0
                    to: items.length - 1
                    value: 1

                    property var items: ["Easy", "Normal", "Hard"]

                    validator: RegExpValidator {
                        regExp: new RegExp("(Easy|Normal|Hard)", "i")
                    }

                    textFromValue: function(value) {
                        return items[value];
                    }

                    valueFromText: function(text) {
                        for (var i = 0; i < items.length; ++i) {
                            if (items[i].toLowerCase().indexOf(text.toLowerCase()) === 0)
                                return i
                        }
                        return sb.value
                    }
                }

                Button {
                    id: startGameButton
                    Layout.preferredWidth: parent.width * 0.1
                    Layout.preferredHeight: parent.height
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    text: "\uf04b"
                    font.pointSize: 14
                    font.family: "fontawesome"
                    onClicked: {
                        rounds = level
                        updateUser()
                        newGame()
                    }
                }
                Button {
                    id: endGameButton
                    Layout.preferredWidth: parent.width * 0.1
                    Layout.preferredHeight: parent.height
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    text: "\uf04d"
                    font.pointSize: 14
                    font.family: "fontawesome"
                    onClicked: {
                        inputTextField.enabled = false
                        gameText.text = "Welcome!"
                        updateUser()
                        startGameButton.enabled = true
                    }
                }
                Button {
                    id: userInfoButton
                    Layout.preferredWidth: parent.width * 0.1
                    Layout.preferredHeight: parent.height
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    text: "\uf129"
                    font.pointSize: 14
                    font.family: "fontawesome"
                    onClicked: {
                        updateUser()
                        stackView.push("qrc:/ui/ui/InfoPage.qml", {"userName" : userName,
                                                                   "realName" : realName,
                                                                "levelPassed" : levelPassed,
                                                                 "experience" : experience,
                                                                 "utype"      : 1})
                    }
                }
                Button {
                    id: usersListButton
                    Layout.preferredWidth: parent.width * 0.1
                    Layout.preferredHeight: parent.height
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    text: "\uf0c0"
                    font.pointSize: 14
                    font.family: "fontawesome"
                    onClicked: {
                        updateUser()
                        stackView.push("qrc:/ui/ui/UsersPage.qml")
                    }
                }
                Button {
                    id: exitGameButton
                    Layout.preferredWidth: parent.width * 0.1
                    Layout.preferredHeight: parent.height
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    text: "\uf2f5"
                    font.pointSize: 14
                    font.family: "fontawesome"
                    onClicked: {
                        updateUser()
                        logOut()
                        stackView.pop()
                    }
                }
            }
        }
    }

    function newGame() {
        game_client.sendRequest("getWordRequest", (difficultySpinBox.value + 1).toString())
    }

    function updateUser() {
        game_client.sendRequest("updateUserRequest", userName + "$" + levelPassed.toString() + "$" + experience.toString())
    }

    function logOut() {
        game_client.sendRequest("logoutRequest", userName)
    }
}
