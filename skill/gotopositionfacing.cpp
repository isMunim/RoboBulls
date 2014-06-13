#include "gotopositionfacing.h"
#include "utilities/measurments.h"
#include "communication/robcomm.h"
#include "include/util.h"
#include "skill/rotate.h"
#include "skill/differential_control/closedloopcontrol.h"
#include "model/gamemodel.h"
#include <math.h>


namespace Skill {

GoToPositionFacing::GoToPositionFacing(Point target)
{
    targetPosition = target;
}

GoToPositionFacing::GoToPositionFacing(float tx, float ty)
{
    targetPosition = Point(tx, ty);
}

void GoToPositionFacing::perform(Robot * robot)
{
    cout<<"calling go to position with orientation!"<<endl;
    //********************************************************************
    //Checking shamsi's code
    RobComm *nxtbee = RobComm::getRobComm();
    Point robotPosition = robot->getRobotPosition();
    double robot_x = robotPosition.x;
    double robot_y = robotPosition.y;
    double robot_orientation = robot->getOrientation();
//    float finalOrientation = Measurments::slop(robotPosition, targetPosition);
    double finalOrientation = atan2(targetPosition.y-robot_y, targetPosition.x-robot_x);
    wheelvelocities wheelvelocity = ClosedLoopControl::closed_loop_control(robot_x, robot_y, robot_orientation, targetPosition.x, targetPosition.y, finalOrientation);

    float left_wheel_velocity = wheelvelocity.left;
    float right_wheel_velocity = wheelvelocity.right;

    cout<<"left Wheel Vel : "<<left_wheel_velocity << "\t right Wheel vel: " << right_wheel_velocity<<endl;

    nxtbee->sendVels(left_wheel_velocity, right_wheel_velocity, robot->getID());
    //********************************************************************
}

}