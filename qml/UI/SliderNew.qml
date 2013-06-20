import QtQuick 2.0
import "../Block/"

BaseBlock {
    id: slider
    property real value: 0
    onValueChanged: updatePos();
    property real maximum: 50
    property real minimum: 0
    property real handleWidth: 5
    property real handlePos: 0
    property int xMax: sliderFrame.width - handleWidth
    onXMaxChanged: updatePos();
    onMinimumChanged: updatePos();
    function updatePos() {
        if (maximum > minimum) {
            var pos = (value - minimum) * slider.xMax / (maximum - minimum);
            pos = Math.min(pos, width - handleWidth );
            pos = Math.max(pos, 0);
            handlePos = pos;
        } else {
            handlePos = 0;
        }
        console.log(value)
    }
    Rectangle {
        id: sliderFrame
        anchors.verticalCenter: slider.verticalCenter
        anchors.horizontalCenter: slider.horizontalCenter
        width: slider.width - 2*slider.radius - 2*slider.border.width
        height: slider.height - 2*slider.border.width - 2
        color: "#66EFEFEF"
        Rectangle {
            id: handle;
            smooth: true
            anchors.verticalCenter: sliderFrame.verticalCenter
            width: 5;
            height: sliderFrame.height;
            color: "#8F8F8F"

            MouseArea {
                id: mouse
                anchors.fill: parent;
                drag.target: parent
                drag.axis: Drag.XAxis;
                drag.minimumX: 0;
                drag.maximumX: slider.xMax
                onPositionChanged: {
                    value = (maximum - minimum) * (handle.x-2) / slider.xMax + minimum;
                }
            }
        }
    }
}
