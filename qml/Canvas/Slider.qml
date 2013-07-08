import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
BaseBlock {
    id: slider
    Slider {
        anchors.centerIn: parent
        stepSize: object.step
        minimumValue: object.minimum
        maximumValue: object.maximum
        style: SliderStyle {
            groove: Rectangle {
                id: groove
                implicitWidth: slider.width - 2*slider.radius - 2*slider.border.width
                implicitHeight: slider.height - 2*slider.border.width - 2
                color: "#66EFEFEF"
            }
            handle: Rectangle {
                anchors.centerIn: parent
                smooth: true
                width: 5;
                height: slider.height - 2*slider.border.width - 2
                color: control.pressed ? "black" :"#8F8F8F"
            }
        }
        activeFocusOnPress: false
        onValueChanged: {
            pressed ? print("Pressed") : print("not pressed")
            console.log(value);
        }
    }
//    Rectangle {
//        anchors.centerIn: parent
//        width: slider.width - 2*slider.radius - 2*slider.border.width
//        height: slider.height - 2*slider.border.width - 2
//        color: "#66EFEFEF"
//    }
}
