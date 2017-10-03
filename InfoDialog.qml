import QtQuick 2.3
import QtQuick.Layouts 1.1
import com.ctdi.RasPiServer.CommsServer 1.0

Rectangle {
    id: InfoDialogWindow
    visible: false
    color: "#14148c"
    property alias instruction: txt.text

    Column {
        id: root
        signal ok

        anchors.centerIn: parent
        spacing: 160

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
        GuiCircularBtn {
            id: okBtn
            anchors.horizontalCenter: parent.horizontalCenter
            Layout.maximumHeight: height
            state: "Ok"
        }
    }

    Component.onCompleted: { okBtn.clicked.connect(root.ok) }

    onOk: {
        commServer.setPromptAnswer(1);
        InfoDialogWindow.visible = false;
    }

    Connections {
        target: commServer
        onStopGuiPrompt: promptWindow.visible = false;
    }
}
