import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import com.ctdi.RasPiServer.CommsServer 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 1920
    height: 1080
    flags: Qt.FramelessWindowHint

    CommsServer { id: commServer }

    // Background
    Rectangle {
        anchors.fill: parent
        Image {
            id: background
            anchors.centerIn: parent
            width: root.width
            height:root.height
            fillMode: Image.PreserveAspectFit
            source: "images/ctdiLogo.png"
        }
    }

    Connections {
        target: commServer
        onDisplayOperatorPrompt: {
            operatorPrompt.instruction = commServer.promptQuestion;
            operatorPrompt.visible = true;
        }
        onDisplayFrontPanelInfo: {
            frontPanel.instruction = commServer.frontPanelInfo;
            frontPanel.visible = true;
        }
        onStopFrontPanelInfo: frontPanel.visible = false;
    }


    /******PANELS******/
    OperatorPrompt {
        id: operatorPrompt
        anchors.fill: parent
        visible: false
    }
    FrontPanelInfo {
        id: frontPanel
        anchors.fill: parent
        visible: false
    }
}
