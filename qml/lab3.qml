import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "Graphic Viewer"

    Canvas {
        id: canvas
        anchors.fill: parent

        property int highlightedEdge: 0

        // Массив цветов для граней
        property var colors: [
            "rgba(255, 0, 0, 0.3)",   // Красный
            "rgba(0, 255, 0, 0.3)",   // Зеленый
            "rgba(0, 0, 255, 0.3)",   // Синий
            "rgba(255, 255, 0, 0.3)", // Желтый
            "rgba(0, 255, 255, 0.3)", // Голубой
            "rgba(255, 0, 255, 0.3)"  // Фиолетовый
        ]

        onPaint: {
            var ctx = getContext("2d");
            ctx.clearRect(0, 0, canvas.width, canvas.height);

            for (var i = 0; i < dataModel.faces.length; i++) {
                var face = dataModel.faces[i];

                ctx.beginPath();
                ctx.moveTo(face[0].x, face[0].y);

                for (var j = 1; j < face.length; j++) {
                    ctx.lineTo(face[j].x, face[j].y);
                }
                ctx.closePath();

                // Устанавливаем цвет из массива
                ctx.fillStyle = colors[i % colors.length];
                ctx.fill();

                ctx.strokeStyle = "black";
                ctx.lineWidth = 1;
                ctx.stroke();
            }
        }

        Connections {
            target: dataModel
            onVerticesChanged: canvas.requestPaint()
            onFacesChanged: canvas.requestPaint()
        }

        Component.onCompleted: requestPaint()
    }
}
