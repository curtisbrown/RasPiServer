import QtQuick 2.6
import QtQuick.Window 2.2
import com.ctdi.RasPiServer.CommsServer 1.0

Rectangle {
    id: promptWindow
    visible: false
    color: "#14148c"
    property alias instruction: txt.text

    Column {
        id: root
        signal yes
        signal no

        anchors.centerIn: parent
        width: promptWindow.width
        spacing: 100

        GuiText {
            id: txt
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width

            font.bold: true
            font.pointSize: 60

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

    Connections {
        target: commServer
        onStopGuiPrompt: promptWindow.visible = false;
    }
}
