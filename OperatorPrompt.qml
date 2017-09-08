import QtQuick 2.6
import QtQuick.Window 2.2
import com.ctdi.RasPiServer.CommsServer 1.0

Window {
    id: promptWindow
    visible: false
    width: 1920
    height: 1080
    flags: Qt.FramelessWindowHint
    color: "#14148c"
    property alias instruction: txt.text

    Column {
        id: root
        signal yes
        signal no

        anchors.centerIn: parent
        width: parent.width
        spacing: 100

        GuiText {
            id: txt
            anchors.horizontalCenter: parent.horizontalCenter
            width: root.width

            font.bold: true
            font.pointSize: 40

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            wrapMode: Text.WordWrap
        }
        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 150
            GuiCircularBtn { id: noBtn; state: "No" }
            GuiCircularBtn { id: yesBtn; state: "Yes" }
        }

        Component.onCompleted: {
            yesBtn.clicked.connect(root.yes)
            noBtn.clicked.connect(root.no)
        }

        onYes: {
            commServer.setPromptAnswer(1);
            promptWindow.visible = false;
        }
        onNo: {
            commServer.setPromptAnswer(0);
            promptWindow.visible = false;
        }
    }
}
