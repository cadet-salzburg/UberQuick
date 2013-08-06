.pragma library
function Bezier(p1, p2, canvasMargin)
{
    this.update(p1,p2,canvasMargin);
}
Bezier.prototype.update = function(p1, p2, canvasMargin)
{
    this.p1 = p1;
    this.p2 = p2;

    this.canvasMargin = canvasMargin;

    this.width  = Math.abs(p1.x - p2.x) + 2*canvasMargin;
    this.height = Math.abs(p1.y - p2.y) + 2*canvasMargin;
    this.boundingRect = Qt.rect(Math.min(p1.x,p2.x) - canvasMargin, Math.min(p1.y, p2.y) - canvasMargin,this.width, this.height);

    this.start = Qt.point(0,0);
    this.end = Qt.point(0,0);
    this.cpStart = Qt.point(0,0);
    this.cpEnd = Qt.point(0,0);


    if(p1.x <= p2.x
    && p1.y <= p2.y){
        this.start = Qt.point( this.canvasMargin, this.canvasMargin);
        this.end   = Qt.point(this.width-this.canvasMargin, this.height -this.canvasMargin )
    }
    if(p1.x <= p2.x
    && p1.y > p2.y){
        this.start = Qt.point( this.canvasMargin, this.height - this.canvasMargin );
        this.end   = Qt.point( this.width - this.canvasMargin, this.canvasMargin );
    }
    if(p1.x > p2.x
    && p1.y <= p2.y){
        this.start = Qt.point( this.width - this.canvasMargin, this.canvasMargin );
        this.end   = Qt.point( this.canvasMargin, this.height - this.canvasMargin );
    }
    if(p1.x > p2.x
    && p1.y > p2.y){
        this.start = Qt.point( this.width - this.canvasMargin, this.height - this.canvasMargin );
        this.end   = Qt.point( this.canvasMargin, this.canvasMargin );
    }

    var offset = 0.5*( this.height - 2*this.canvasMargin );
    this.cpStart = Qt.point(this.start.x, this.start.y + offset);
    this.cpEnd = Qt.point(this.end.x, this.end.y - offset);
}

Bezier.prototype.getCanvasPosition = function()
{
    return Qt.point(this.boundingRect.x, this.boundingRect.y )
}
Bezier.prototype.getCanvasWidth = function()
{
    return this.boundingRect.width;
}
Bezier.prototype.getCanvasHeight = function()
{
    return this.boundingRect.height;
}
