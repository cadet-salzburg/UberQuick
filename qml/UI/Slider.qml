import QtQuick 2.0
import "../Block/"

 Item {
     id: slider
     width:          150
     height:         30
     property real value: 0
     onValueChanged: updatePos();
     property real maximum: 50
     property real minimum: 0
     property int xMax: width - handle.width - 4
     onXMaxChanged: updatePos();
     onMinimumChanged: updatePos();
     function updatePos() {
         if (maximum > minimum) {
             var pos = 2 + (value - minimum) * slider.xMax / (maximum - minimum);
             pos = Math.min(pos, width - handle.width - 2);
             pos = Math.max(pos, 2);
             handle.x = pos;
         } else {
             handle.x = 2;
         }
         console.log(value)
     }
     Rectangle {
         id: backgroundRect
         anchors.fill: parent
         radius:         12
         color:          "#FFFCFCFC"
         border.color:   "#FFAFAFAF"
         border.width:   3
         antialiasing:   true
//         border.color: "white"; border.width: 0; radius: 12
//         gradient: Gradient {
//             GradientStop { position: 0.0; color: "#66343434" }
//             GradientStop { position: 1.0; color: "#66000000" }
//         }
         MouseArea {
             anchors.fill: parent
             drag.target: slider
             drag.axis: Drag.XAndYAxis
         }
     }
     Node
     {
         x: backgroundRect.radius/2 + backgroundRect.border.width
         y: slider.height / 2 +  1.5*backgroundRect.border.width
         thickness: 3
     }

     Rectangle {
         id: handle; smooth: true
         anchors.verticalCenter: backgroundRect.verticalCenter
         width: 6;
         height: slider.height-3*backgroundRect.border.width;
         //radius: 4
         color: "#8F8F8F"

         MouseArea {
             id: mouse
             anchors.fill: parent;
             drag.target: parent
             drag.axis: Drag.XAxis;
             drag.minimumX: 2;
             drag.maximumX: slider.xMax+2
             onPositionChanged: {
                 value = (maximum - minimum) * (handle.x-2) / slider.xMax + minimum;
             }
         }
     }

 }
