import QtQuick 2.3

Item {
    id: root
    property alias text: buttonLabel.text
    property alias fontSize: buttonLabel.font.pointSize
    property alias txtColor: buttonLabel.color
    property alias radius: rectangle.radius
    property alias border: rectangle.border
    property color borderColor: "white"
    property color buttonColor: "#6CB33F"
    property alias bold: buttonLabel.font.bold
    property alias contentHeight: buttonLabel.contentHeight
    property alias contentWidth: buttonLabel.contentWidth
    property alias hoverEnabled: mArea.hoverEnabled

    signal clicked

    implicitHeight: buttonLabel.font.pixelSize * 30
    implicitWidth: implicitHeight


    Rectangle {
        id: rectangle
        anchors.fill: parent

        border.color: borderColor
        color: mArea.pressed ? Qt.darker(buttonColor, 1.5) : buttonColor
        radius: 1
        border.width: 2
        anchors.margins: 5

        GuiText {
            id: buttonLabel
            anchors.fill: parent

            wrapMode: Text.WordWrap
            color: "#203030"
        }

        MouseArea {
            id: mArea
            anchors.fill: parent
            onClicked: console.log(buttonLabel.text + " clicked")

            hoverEnabled: true

            Component.onCompleted: mArea.clicked.connect(root.clicked)
        }

        states: [
            State {
                name: "hovered"
                when: mArea.containsMouse && hoverEnabled
                PropertyChanges { target: rectangle; border.color: "gold" }
            },
            State {
                name: "nonHovered"
                when: !mArea.containsMouse
                PropertyChanges { target: rectangle; border.color: borderColor }
            }
        ]
    }
}
