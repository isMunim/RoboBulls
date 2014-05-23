#include "robot.h"

Robot::Robot()
{
}

void Robot::setRobotPosition(Point rbtPoint)
{
    robotPosition = rbtPoint;
}

void Robot:: setOrientation(float ornt)
{
    orientation = ornt;
}

void Robot::setID(int ID)
{
    id = ID;
}

void Robot::setL(float left)
{
    L = left;
}

void Robot::setR(float right)
{
    R= right;
}

void Robot::setCurrentBeh(Behavior *currentBeh)
{
    currentBehavior = currentBeh;
    hasBeh = true;
}

////*******************************************************
////Testing Shamsi's code
//void Robot::setRightWheelVelocity(int rVel)
//{
//    right_wheel_vel = rVel;
//}

//void Robot::setLeftWheelVelocity(int lVel)
//{
//    left_wheel_vel = lVel;
//}

////*******************************************************


Point Robot::getRobotPosition()
{
    return robotPosition;
}

float Robot::getOrientation()
{
    return orientation;
}

int Robot::getID()
{
    return id;
}

int Robot::getL()
{
    return L;
}

int Robot::getR()
{
    return R;
}

Behavior * Robot::getCurrentBeh()
{
    return currentBehavior;
}

////*******************************************************
////Testing Shamsi's code
//int Robot::getRightWheelVelocity()
//{
//    return right_wheel_vel;
//}

//int Robot::getLeftWheelVelocity()
//{
//    return left_wheel_vel;
//}

////*******************************************************


stringstream& Robot::toString()
{
    stringstream myString;

    myString << "\t" << getRobotPosition().toString().str() << "\t ID: " << getID() << "\t Orientation: "<< getOrientation();

    return myString;

}
