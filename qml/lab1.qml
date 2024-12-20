import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import CustomShapes 1.0

ApplicationWindow {
    visible: true
    width: 800
    height: 500

    Rectangle {
        id: rectangle
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        Canvas {
            id: canvas
            Layout.fillWidth: true
            Layout.preferredHeight: 400

            Component.onCompleted: {
                canvas.requestPaint();
            }

            onPaint: {
                var ctx = canvas.getContext("2d")
                ctx.clearRect(0, 0, canvas.width, canvas.height)
                ctx.beginPath()

                ctx.moveTo(100, 200);
                ctx.lineTo(776, 378);
                ctx.strokeStyle = "green";
                ctx.lineWidth = 2;
                ctx.stroke();

                for (var i = 0; i < rectangle.edges().length; ++i) {
                    var edge = rectangle.edges()[i]
                    var v1 = rectangle.vertices[edge.x]
                    var v2 = rectangle.vertices[edge.y]

                    if (i === 0) {
                        ctx.strokeStyle = "red"
                    } else {
                        ctx.strokeStyle = "black"
                    }

                    ctx.beginPath()
                    ctx.moveTo(v1.x, v1.y)
                    ctx.lineTo(v2.x, v2.y)
                    ctx.stroke()
                }
            }

            Connections {
                target: rectangle
                onVerticesChanged: canvas.requestPaint()
            }
        }

        Button {
            text: "reset"
            onClicked: rectangle.reset()
        }

        Button {
            text: "Rotate 90°"
            onClicked: rectangle.rotate(90)
        }

        Button {
            text: "Rotate until hit right edge"
            onClicked: {
                rotateUntilHitEdge();
            }
        }
    }

    Timer {
        id: rotationTimer
        interval: 500
        repeat: false
        onTriggered: {
            var rightBottomX = rectangle.vertices[rectangle.findBottomRightVertex()].x;
            var windowWidth = parent.width - 50;

            if (rightBottomX < windowWidth) {
                rectangle.rotate(90);
                rotationTimer.start();
            }
        }
    }

    function rotateUntilHitEdge() {
        rotationTimer.start();
    }
}
