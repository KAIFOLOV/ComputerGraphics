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

        onPaint: {
            var ctx = getContext("2d");
            ctx.clearRect(0, 0, width, height);

            // Рисуем ребра

            console.log(dataModel.edges.length)

            for (var i = 0; i < dataModel.edges.length; i++) {
                var edge = dataModel.edges[i];
                var start = dataModel.vertices[edge.x];
                var end = dataModel.vertices[edge.y];

                ctx.strokeStyle = "black";
                ctx.lineWidth = 2;

                ctx.beginPath();
                ctx.moveTo(start.x, start.y);
                ctx.lineTo(end.x, end.y);
                ctx.stroke();
            }

            // Рисуем вершины
            ctx.fillStyle = "red";
            for (var j = 0; j < dataModel.vertices.length; j++) {
                var vertex = dataModel.vertices[j];
                ctx.beginPath();
                ctx.arc(vertex.x, vertex.y, 5, 0, 2 * Math.PI);
                ctx.fill();
            }
        }

        Connections {
            target: dataModel
            onVerticesChanged: canvas.requestPaint()
            onEdgesChanged: canvas.requestPaint()
        }

        Component.onCompleted: requestPaint()
    }
}
