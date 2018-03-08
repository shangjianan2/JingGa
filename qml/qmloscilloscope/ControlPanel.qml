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

import QtQuick 2.1
import QtQuick.Layouts 1.0

ColumnLayout {
    property alias openGLButton: openGLButton
    property alias antialiasButton: antialiasButton
    spacing: 8
    Layout.fillHeight: true
    signal animationsEnabled(bool enabled)
    signal seriesTypeChanged(string type)
    signal refreshRateChanged(variant rate);
    signal signalSourceChanged(string source, int signalCount, int sampleCount);
    signal antialiasingEnabled(bool enabled)
    signal openGlChanged(bool enabled)

//    Text {
//        text: "Scope"
//        font.pointSize: 18
//        color: "white"
//    }
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


    Image {
        id: img
        source: "qrc:/timg.jpg"  // 要显示的图片

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
                if(0 == n){         // 根据变量切换图片
                 img.source="qrc:/ani.jpg";
                    n = 1
                }else{
                 img.source="qrc:/av1.jpg";
                    n=0;
                }
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

    MultiButton {
        id: openGLButton
        x: -2
        y: 11
        width: 21
        height: 21
        text: "OpenGL: "
        visible: false
        items: ["false", "true"]
        currentSelection: 1
        onSelectionChanged: openGlChanged(currentSelection == 1);
    }

    MultiButton {
        y: 83
        width: 20
        height: 20
        text: "Graph: "
        visible: false
        items: ["line", "scatter"]
        currentSelection: 0
        onSelectionChanged: seriesTypeChanged(items[currentSelection]);
    }

    MultiButton {
        id: signalSourceButton
        text: "Source: "
        visible: false
        items: ["sin", "linear"]
        currentSelection: 0
        onSelectionChanged: signalSourceChanged(
                                selection,
                                5,
                                sampleCountButton.items[sampleCountButton.currentSelection]);
    }

    MultiButton {
        id: sampleCountButton
        text: "Samples: "
        visible: false
        items: ["6", "128", "1024", "10000"]
        currentSelection: 2
        onSelectionChanged: signalSourceChanged(
                                signalSourceButton.items[signalSourceButton.currentSelection],
                                5,
                                selection);
    }

    MultiButton {
        text: "Refresh rate: "
        visible: false
        items: ["1", "24", "60"]
        currentSelection: 2
        onSelectionChanged: refreshRateChanged(items[currentSelection]);
    }

    MultiButton {
        id: antialiasButton
        text: "Antialias: "
        visible: false
        items: ["OFF", "ON"]
        enabled: true
        currentSelection: 0
        onSelectionChanged: antialiasingEnabled(currentSelection == 1);
    }
}
