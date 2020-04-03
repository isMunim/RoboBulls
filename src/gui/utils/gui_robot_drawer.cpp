#define _USE_MATH_DEFINES
#include "gui_robot_drawer.h"
#include "model/team.h"
#include "utilities/measurements.h"
#include <QLabel>
#include <QString>

GuiRobotDrawer::GuiRobotDrawer(int team, int id) : robot(&GuiRobot::proxies[team][id]) {
    setToolTip("Robot " + QString::number(robot->id));
    setFlag(ItemIsSelectable);
    icon = false;

    int radius = boundingRect().width() / 2;
    setTransformOriginPoint(radius,radius);
}






QRectF GuiRobotDrawer::boundingRect() const
{
    int diameter = 200;
//    int radius = diameter/2;
    return QRectF(0,0,diameter,diameter);
}



void GuiRobotDrawer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);


    QRectF rec = boundingRect();
    QRectF base(30,25,150,150);

    QBrush brush(Qt::magenta, Qt::SolidPattern);
    // ID circles colors
    QBrush topRtBrush(Qt::magenta, Qt::SolidPattern);
    QBrush topLtBrush(Qt::magenta, Qt::SolidPattern);
    QBrush lowRtBrush(Qt::magenta, Qt::SolidPattern);
    QBrush lowLtBrush(Qt::magenta, Qt::SolidPattern);

    // Setting ID circles' diameters to fractions of the robot's diameter
    int cornerDiam = boundingRect().width() / 3.8 ;
    int centerDiam = boundingRect().width() / 3 ;

    QRectF topRtCircle(0,0,cornerDiam,cornerDiam);
    QRectF topLtCircle(0,0,cornerDiam,cornerDiam);
    QRectF lowRtCircle(0,0,cornerDiam,cornerDiam);
    QRectF lowLtCircle(0,0,cornerDiam,cornerDiam);
    QRectF centerCircle(0,0,centerDiam, centerDiam);
    // Circle centerpoints based on the robot's front facing Right
    QPointF topRtpt(135,45);
    QPointF topLtpt(135,155);
    QPointF lowRtpt(45,55);
    QPointF lowLtpt(45,145);
    QPointF centerpt(95,100);
    // Setting circles to their coordinates
    topRtCircle.moveCenter(topRtpt);
    topLtCircle.moveCenter(topLtpt);
    lowRtCircle.moveCenter(lowRtpt);
    lowLtCircle.moveCenter(lowLtpt);
    centerCircle.moveCenter(centerpt);

    if(robot->Pressed) {
        //brush.setColor(Qt::red);
    } else {
        //brush.setColor(Qt::magenta);
    }
    // Setting ID circles' colors
    if (robot->id == 0) {
        lowLtBrush.setColor(Qt::green);
    } else if (robot->id == 1) {
        lowLtBrush.setColor(Qt::green);
        topLtBrush.setColor(Qt::green);
    } else if (robot->id == 2) {
        lowLtBrush.setColor(Qt::green);
        topLtBrush.setColor(Qt::green);
        topRtBrush.setColor(Qt::green);
    } else if (robot->id == 3) {
        topRtBrush.setColor(Qt::green);
        lowLtBrush.setColor(Qt::green);
    } else if (robot->id == 4) {
        lowRtBrush.setColor(Qt::green);
    } else if (robot->id == 5) {
        topLtBrush.setColor(Qt::green);
        lowRtBrush.setColor(Qt::green);
    } else if (robot->id == 6) {
        topLtBrush.setColor(Qt::green);
        lowRtBrush.setColor(Qt::green);
        topRtBrush.setColor(Qt::green);
    } else if (robot->id == 7) {
        lowRtBrush.setColor(Qt::green);
        topRtBrush.setColor(Qt::green);
    } else if (robot->id == 8) {
        lowLtBrush.setColor(Qt::green);
        topLtBrush.setColor(Qt::green);
        topRtBrush.setColor(Qt::green);
        lowRtBrush.setColor(Qt::green);
    }
    painter->setRenderHint(QPainter::Antialiasing, true);

    // Robot body
    if (robot->isKicking()) {
        painter->setPen(QPen(Qt::gray, 0, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin));
        painter->setBrush(QBrush(Qt::red, Qt::SolidPattern));
    } else if (robot->isDribbling()) {
        painter->setPen(QPen(Qt::gray, 0, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin));
        painter->setBrush(QBrush(QColor::fromRgb(255,153,0,255), Qt::SolidPattern));
    } else {
        painter->setPen(QPen(Qt::gray, 0, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin));
        painter->setBrush(QBrush(Qt::gray, Qt::SolidPattern));
    }
    if (robot->enabled) {
        painter->drawRoundedRect(base,15,15);
    }

    // Robot hat
    painter->setPen(QPen(Qt::black, 0, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin));
    painter->setBrush(QBrush(Qt::black, Qt::SolidPattern));

    if (robot->overridden){
        painter->setBrush(QBrush(Qt::darkRed, Qt::SolidPattern));
    }

    if (robot->highlighted) {
        auto color = robot->team == ROBOT_TEAM_BLUE ? Qt::cyan : QColor::fromRgb(255,215,0,255);
        painter->setBrush(QBrush(color, Qt::SolidPattern));

    }
    if (robot->overridden && robot->highlighted) {
        painter->setBrush(QBrush(Qt::red, Qt::SolidPattern));
    }
    int startAngle = 50 * 16;
    int spanAngle = 260 * 16;
    painter->drawChord(rec, startAngle, spanAngle);
    // Corner ID circles
    painter->setPen(QPen(Qt::black, 0, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin));
    painter->setBrush(topRtBrush);
        painter->drawEllipse(topRtCircle);
    painter->setBrush(topLtBrush);
        painter->drawEllipse(topLtCircle);
    painter->setBrush(lowRtBrush);
        painter->drawEllipse(lowRtCircle);
    painter->setBrush(lowLtBrush);
        painter->drawEllipse(lowLtCircle);
    // Center circle

    auto c = robot->team == ROBOT_TEAM_BLUE ? Qt::blue : Qt::yellow;
    painter->setBrush(QBrush(c, Qt::SolidPattern));

    painter->drawEllipse(centerCircle);


}


void GuiRobotDrawer::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    robot->Pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void GuiRobotDrawer::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    robot->Pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void GuiRobotDrawer::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    robot->doubleClicked = true;
    update();
    QGraphicsItem::mouseDoubleClickEvent(event);
}


