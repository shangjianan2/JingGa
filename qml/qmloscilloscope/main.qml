/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0

import QtQuick 2.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

//![1]
Item {
    id: main
    width: 1200
    height: 400

    Image {
        id: img
        source: "qrc:/timg.jpg"  // 要显示的图片

		x : -200; y : -200

	    Timer {
	        id: refreshTimer
	        interval: 100 // 60 Hz
	        running: true
	        repeat: true
	        onTriggered: {
	            switch(ur.return_gr()){
	            case 0:
	                rectangle.color = 'green';
	                break;
	            case 1:
	                rectangle.color = 'red';
	                break;
	            case 2:
	                rectangle2.color = 'green';
	                break;
	            case 3:
	                rectangle2.color = 'red';
	                break;
	            }
	        }
	    }


        Rectangle{
            id: rectangle
            color: 'red'
            width: 10; height: 10
            x: img.width / 2; y: img.height / 2
        }

        Rectangle{
            id: rectangle2
            color: 'red'
            width: 10; height: 10
            x: img.width / 3; y: img.height / 3
        }

        MouseArea {     // 鼠标响应
            id: dragArea;
            anchors.fill: parent;   // 在父容器内才响应
            drag.target: img        // id为img的对象可以被拖动
            onClicked: {            // 点击事件
                console.debug("点击了图片")  // 打印信息
//                if(0 == n){         // 根据变量切换图片
//                 img.source="qrc:/ani.jpg";
//                    n = 1
//                }else{
//                 img.source="qrc:/av1.jpg";
//                    n=0;
//                }
            }

            onWheel: {
                if (wheel.angleDelta.y > 0) {
                    img.width += 20;
                    img.x -= 8

                    img.height += 20;
                    img.y -= 8
                }
                else {
                    img.width -= 20;
                    img.x += 8

                    img.height -= 20;
                    img.y += 8
                }
            }

        }
    }

    Rectangle {
        id: rectangle_main
        anchors.top: main.top
        anchors.bottom: main.bottom
        anchors.right: main.right
        anchors.left: controlPanel.right
        height: main.height
		color: 'black'

//        onOpenGLSupportedChanged: {
//            if (!openGLSupported) {
//                controlPanel.openGLButton.enabled = false
//                controlPanel.openGLButton.currentSelection = 0
//            }
//        }

        TextField {
            id: textInput1
            x: 0
            y: parent.height / 2
            width: 300
            height: 25
            placeholderText: qsTr("Send Data")
            font.pixelSize: 12
        }
        Button{
            id:sendData
            x: textInput1.width
            y: parent.height / 2
            width: 60
            text: "Send"
            onClicked: {
                console.log("sendData is pressed")
                ur.sendto("a","a","a")
            }
        }
    }


    ControlPanel {
        id: controlPanel
        width: 326
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 10
//![1]

//        onSignalSourceChanged: {
//            if (source == "sin")
//                dataSource.generateData(0, signalCount, sampleCount);
//            else
//                dataSource.generateData(1, signalCount, sampleCount);
//            scopeView.axisX().max = sampleCount;
//            console.log("signalCount:" + signalCount);
//        }
//        onSeriesTypeChanged: scopeView.changeSeriesType(type);
//        onRefreshRateChanged: scopeView.changeRefreshRate(rate);
//        onAntialiasingEnabled: scopeView.antialiasing = enabled;
//        onOpenGlChanged: {
//            scopeView.openGL = enabled;
//        }
    }

//![2]
    ScopeView {
        id: scopeView
        anchors.top: main.top
        //anchors.bottom: main.bottom / 2
        anchors.right: main.right
        anchors.left: controlPanel.right
        height: main.height / 2
        //width: main.width / 2

        onOpenGLSupportedChanged: {
            if (!openGLSupported) {
                controlPanel.openGLButton.enabled = false
                controlPanel.openGLButton.currentSelection = 0
            }
        }
    }
//![2]

}
