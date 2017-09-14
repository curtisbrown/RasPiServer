import QtQuick 2.6
import QtQuick.Window 2.2
import com.ctdi.RasPiServer.CommsServer 1.0

Rectangle {
    id: frontPanelInfo
    visible: false
    color: "#14148c"
    property alias instruction: txt.text

    Column {
        id: root
        anchors.centerIn: parent
        width: parent.width
        spacing: 100

        GuiText {
            id: txt
            anchors.horizontalCenter: parent.horizontalCenter
            width: root.width

            font.bold: true
            font.pointSize: 80

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            wrapMode: Text.WordWrap
        }
    }
}
