import QtQuick 2.3

GuiButton {
    id: root
    width: height
    radius: width * 0.5
    text: ""
    txtColor: "white"
    border.width: 2

    implicitWidth: implicitHeight

    states: [
        State {
            name: "Yes"
            PropertyChanges { target: root; buttonColor: "limegreen" }
        },
        State {
            name: "No"
            PropertyChanges { target: root; buttonColor: "firebrick" }
        },
        State {
            name: "Ok"
            PropertyChanges { target: root; buttonColor: "royalblue" }
        },
        State {
            name: "Cold"
            PropertyChanges { target: root; buttonColor: "royalblue" }
        },
        State {
            name: "Hot"
            PropertyChanges { target: root; buttonColor: "firebrick" }
        }
    ]
}
