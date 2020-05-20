#include <iostream>

#include "graphics_robot_label.h"
#include "model/constants.h"
#include "gui/data/gui_robot.h"
using std::cout, std::endl;


GraphicsLabel::GraphicsLabel(int team, int id) : robot(&GuiRobot::proxies[team][id]) {
    int radius = boundingRect().width() / 2;
    setTransformOriginPoint(radius,radius);
    setScale(2.5);
}


QRectF GraphicsLabel::boundingRect() const
{
    const int diameter = 200;
    return QRectF(0,0,diameter,diameter);
}

void GraphicsLabel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    if( !robot->isInField()) return;

//    gui_l->setRotation(currentFieldAngle);
//    gui_l->show();

//    setTransform(flipLabel, false);
    setX(robot->getCurrentPosition().x);
    setY(robot->getCurrentPosition().y);
    //    gui_l->setY(gui_r->robot->getCurrentPosition().y);
    //    gui_l->hidden = !check_showIDs->isChecked();


    if(robot->hasBall()) // does this robot have the ball?
    {
        // set static to avoid creating the brush / rect each time
        static QBrush brush(QColor::fromRgb(255,69,0,255), Qt::SolidPattern);
        static QRectF b(100, 0, -50, -50);
        painter->setBrush(brush);
        painter->drawEllipse(b);
    }

    //Setting color of drawn ID
    static auto c_blue  = QColor::fromRgb(0,255,255);
    static auto c_yellow = QColor::fromRgb(255,215,0);
    auto color = robot->team == ROBOT_TEAM_BLUE ? c_blue : c_yellow;
    painter->setPen(QPen(color, 12, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin));


    QString label = QString::number(robot->id);
    if(robot->isControlled())
        label += "(" + QString::number(robot->getMoveStatus()) + ")";

    static QFont sansFont("Courier", 50, QFont::Bold);
    static QRectF rect(0,0,200,200);
    painter->setFont(sansFont);
    painter->drawText(rect,label);




}
