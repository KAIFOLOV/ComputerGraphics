import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 800
    height: 600

    Canvas {
        id: canvas
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d");
            ctx.clearRect(0, 0, width, height);

            // Центрирование на экране
            var centerX = width / 2;
            var centerY = height / 2;

            // Рисуем вершины
            ctx.strokeStyle = "black";
            ctx.lineWidth = 2;
            console.log("_vertexModel.PositionRole:", _vertexModel.PositionRole);

            for (var i = 0; i < _vertexModel.rowCount(); i++) {
                var index = _vertexModel.index(i, 0);
                var vertex = _vertexModel.data(index, _vertexModel.PositionRole);

                console.log("vertex", vertex)

                // Конвертация в 2D (убираем Z)
                var x = centerX + vertex.x * 10; // Масштабируем координаты
                var y = centerY - vertex.y * 10;

                // Рисуем точки (или линии между точками)
                if (i === 0) {
                    ctx.beginPath();
                    ctx.moveTo(x, y);
                } else {
                    ctx.lineTo(x, y);
                }
            }
            ctx.closePath();
            ctx.stroke();
        }
    }

    Button {
        text: "Rotate X"
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: {
            _pencil.rotateX(10);
            canvas.requestPaint();
        }
    }
}



