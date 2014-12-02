#include "teststrategy.h"
#include "behavior/behaviorassignment.h"
#include "behavior/kicktogoal.h"
#include "behavior/defendoneonone.h"
#include "behavior/driveballandkick.h"
#include "behavior/mytestbehavior.h"
#include "behavior/defendclosetoball.h"
#include "behavior/defendfarfromball.h"
#include "behavior/attackmain.h"
#include "behavior/attacksupport.h"
#include "skill/stop.h"
#include "skill/kicktopoint.h"
#include "skill/kick.h"
#include "behavior/genericmovementbehavior.h"
#include "movement/movetype.h"
#include "model/gamemodel.h"
#include "behavior/passballsender.h"
#include "behavior/passballreceiver.h"
#include "behavior/simplebehaviors.h"


class TestBehavior : public Behavior
{
public:
    TestBehavior()
    {
        targetPoint = GameModel::getModel()->getPenaltyPoint();
        db = new Skill::KickToPoint(targetPoint);
    }

    void perform(Robot * robot)
    {
        db->perform(robot);
    }

private:
    Skill::Skill* db;
    Point targetPoint;
};

class TestBehavior2 : public GenericMovementBehavior
{
public:
    TestBehavior2()
    {
    }

    void perform(Robot *robot) override
    {
        setMovementTargets(GameModel::getModel()->getBallPoint(),
                           UNUSED_ANGLE_VALUE, true, false);
        GenericMovementBehavior::perform(robot, Movement::Type::SharpTurns);
    }
};

class ShamsiStrafe : public GenericMovementBehavior
{
    public:
    //The robot moves between (-2000,0) and (2000,0)
    //While constantly facing the ball

    enum {pos_one,pos_two} state = pos_one;

    void perform(Robot *robot) override
    {
        GameModel * gm = GameModel::getModel();
        Point rp = robot->getRobotPosition();
        Point bp = gm->getBallPoint();
        Point target_one = Point(-2000,0);
        Point target_two = Point(2000,0);
        double ori = Measurments::angleBetween(rp,bp);

        switch(state)
        {
        case pos_one:
            setMovementTargets(target_one,ori);
            if (Measurments::isClose(rp,target_one,100))
                state = pos_two;
            break;
        case pos_two:
            setMovementTargets(target_two,ori);
            if (Measurments::isClose(rp,target_two,100))
                state = pos_one;
        }

        GenericMovementBehavior::perform(robot, Movement::Type::facePoint);
    }

};

class ShamsiGoToPose : public GenericMovementBehavior
{
public:
    //Convenient to test motion. Just goes to the point specified
    void perform(Robot *robot) override
    {
        setMovementTargets(Point(0,0), 0);
        GenericMovementBehavior::perform(robot);
    }
};

class ShamsiKickToCenter : public Behavior
{
public:
    //Continuously kicks the ball to the center
    Skill::KickToPoint * kkkk;
    ShamsiKickToCenter()
    {
        kkkk = new Skill::KickToPoint(Point(0,0));
    }

    void perform(Robot *robot) override
    {
        kkkk->perform(robot);
    }
};

class ShamsiPass : public GenericMovementBehavior
{
    public:
    // Pass the ball to the other robot
    Skill::KickToPoint * pass;
    GameModel *gm;
    Point target;

    ShamsiPass()
    {
        pass = new Skill::KickToPoint(&target);
    }

    void perform(Robot *robot) override
    {
        gm = GameModel::getModel();
        target = gm->getMyTeam().at(1)->getRobotPosition();
        pass->perform(robot);
    }
};

class ShamsiPas1s : public GenericMovementBehavior
{
public:
    void perform(Robot *robot) override
    {
        Point ballPoint = GameModel::getModel()->getBallPoint();
        float targetBallAngle
            = Measurments::angleBetween(Point(0,0), ballPoint);
        float ballTargetAngle
            = Measurments::angleBetween(ballPoint, Point(0,0));
        Point behindBall
            = Point(300*cos(targetBallAngle), 300*sin(targetBallAngle))
              + ballPoint;

        setMovementTargets(behindBall, ballTargetAngle, true, true);
        GenericMovementBehavior::perform(robot);
    }
};

TestStrategy::TestStrategy()
{

}

bool TestStrategy::update()
{
    assignBeh();
    return false;
}

void TestStrategy::assignBeh()
{
//*************************************************************
//  Shamsi Code
    BehaviorAssignment<TestBehavior2> assignment1(true);
    assignment1.assignBeh();

//    BehaviorAssignment<ShamsiPass> assignment2(true);
//    assignment2.assignBeh({2});

//    BehaviorAssignment<ShamsiKickToCenter> assignment2(true);
//    assignment2.assignBeh({2});

//      BehaviorAssignment<ShamsiKickToCenter> assignment2(true);
//      assignment2.assignBeh({2});



    //james code
//    GameModel* gm = GameModel::getModel();
//#if SIMULATED
//    Robot* r0 = gm->find(0, gm->getMyTeam());
//    Robot* r1 = gm->find(1, gm->getMyTeam());
//#else
//    Robot* r0 = gm->find(3, gm->getMyTeam());
//    Robot* r1 = gm->find(8, gm->getMyTeam());
//#endif
//    if(!r0 || !r1) return;


//    //if(r0 != NULL) {
//     //   BehaviorAssignment<TestBehavior> ass;
//     //   ass.assignBeh(r0);
//   // }

//    //BehaviorAssignment<DriveBallAndKick> assignment;
//    GameModel * gm = GameModel::getModel();
//    BehaviorAssignment<TestBehavior> assignment;
//    assignment.setSingleAssignment(true);
//    assignment.assignBeh({0, 1});

//    BehaviorAssignment<ShamsiKickToPoint> assignment(true);
//    assignment.assignBeh({1});

//************************************************************
//    Narges code testing DriveBallAndKick
//    BehaviorAssignment<DriveBallAndKick> assignment;
//    assignment.setSingleAssignment(true);
//    assignment.assignBeh(gm->getMyTeam().at(0));

//**************************************************************
//     Narges code testing DriveBallAndKick
    /*
    Point ballPos = gm->getBallPoint();
    vector<Robot*> myTeam = gm->getMyTeam();
    BehaviorAssignment<TestBehavior> assignment(true);
    assignment.setSingleAssignment(true);

    BehaviorAssignment<SimpleBehaviors> simpleAssignment;
    simpleAssignment.setSingleAssignment(true);

    BehaviorAssignment<DefendFarFromBall> golieAssignment;
    golieAssignment.setSingleAssignment(true);

    for (Robot* rob: myTeam)
    {
        if (rob->getID() == 5)
            golieAssignment.assignBeh(rob);
    }


    Robot *closestRobot;
    int closestRobotID;

    //Finds the closest robot to the penalty point and its ID
    if (myTeam.size() > 1)
    {
        if (myTeam.at(0)->getID() != 5)
            closestRobot = myTeam.at(0);
        else
            closestRobot = myTeam.at(1);

        for (unsigned i = 1; i < myTeam.size(); i++)
        {
            if (myTeam.at(i)->getID() != 5)
            {
                Point iPos = myTeam.at(i)->getRobotPosition();
                Point closestPos = closestRobot->getRobotPosition();
                if (Measurments::distance(iPos, ballPos) < Measurments::distance(closestPos, ballPos))
                    closestRobot = myTeam.at(i);
            }
        }
        closestRobotID = closestRobot->getID();
    }
//    cout << closestRobotID << endl;

    assignment.assignBeh(closestRobot);  // assigns penalty behavior to closest robot to the penalty point

    if (myTeam.size() > 1)  // assigns simple behavior to the rest of robots
    {
        for (unsigned i = 0; i < myTeam.size(); i++)
        {
            if (myTeam.at(i)->getID() != closestRobotID && myTeam.at(i)->getID() != 5)
                simpleAssignment.assignBeh(myTeam.at(i));
        }
    }
*/
//***********************************************************************************


////    Narges code testing defendCloseToBall
//    BehaviorAssignment<DefendCloseToBall> assignment;
//    assignment.setSingleAssignment(true);
//    assignment.assignBeh();


////    Narges code testing defendfarfromball
//    BehaviorAssignment<DefendFarFromBall> assignment;
//    assignment.setSingleAssignment(true);
////    for (Robot* rob: gm->getMyTeam())
////    {
////        if (rob->getID() == 5)
//            assignment.assignBeh();
////    }

////    Narges testing myTestBehavior
//    BehaviorAssignment<myTestBehavior> assignment;
//    assignment.setSingleAssignment(true);
//    assignment.assignBeh(gm->getMyTeam().at(0));


////     Narges testing passSender
//    BehaviorAssignment<PassBallSender> assignment;
//    assignment.setSingleAssignment(true);
//    assignment.assignBeh(gm->getMyTeam().at(0));

////     Narges testing passReceiver
//    BehaviorAssignment<PassBallReceiver> assignment;
//    assignment.setSingleAssignment(true);
//    assignment.assignBeh(gm->getMyTeam().at(0));

////    BehaviorAssignment<DriveBallAndKick> assignment;
//    GameModel * gm = GameModel::getModel();
//    BehaviorAssignment<TestBehavior> assignment;
//    assignment.setSingleAssignment(true);
//    assignment.assignBeh({0, 1});

//    BehaviorAssignment<ShamsiKickToPoint> assignment(true);
//    assignment.assignBeh({1});

//************************************************************
}
