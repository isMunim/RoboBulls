#include "freekickstrategy.h"
#include "../normal_game_roles.h"

#include "strategy/behaviors/attackmain.h"
#include "strategy/behaviors/attacksupport.h"
#include "strategy/behaviors/goalie.h"
#include "strategy/behaviors/wall.h"
#include "strategy/behaviors/markbot.h"

#include "model/game_state.h"
#include "model/team.h"
#include "model/ball.h"
#include "model/field.h"
#include "robot/robot.h"


FreeKickStrategy::FreeKickStrategy(RobotTeam* _team)
    : Strategy(_team), initial_bp(_team->getGameState()->getBall()->getPosition())
{

}

void FreeKickStrategy::assignBehaviors()
{
    // Pointers to various robots
    Robot* wall1 = team->getRobotByRole(RobotRole::DEFEND1);
    Robot* wall2 = team->getRobotByRole(RobotRole::DEFEND2);
    Robot* attack1 = team->getRobotByRole(RobotRole::ATTACK1);
    Robot* attack2 = team->getRobotByRole(RobotRole::ATTACK2);

    // We are taking the free kick

    if ((team->getGameState()->getRefereeCommand() == 'F' && team->getColor() == ROBOT_TEAM_BLUE) ||
        (team->getGameState()->getRefereeCommand() == 'f' && team->getColor() == ROBOT_TEAM_YELLOW))
    {
        for(Robot* rob : team->getRobots())
            rob->clearBehavior();

        auto opponent_goal = Field::getGoalPosition(OPPONENT_SIDE);
        if(attack1)
        {
            attack1->assignSkill<Skill::KickToPointOmni>(opponent_goal);
            kicker = attack1;
        }
        else if(attack2)
        {
            attack2->assignSkill<Skill::KickToPointOmni>(opponent_goal);
            kicker = attack2;
        }
        else if(wall1)
        {
            wall1->assignSkill<Skill::KickToPointOmni>(opponent_goal);
            kicker = wall1;
        }
        else if(wall2)
        {
            wall2->assignSkill<Skill::KickToPointOmni>(opponent_goal);
            kicker = wall2;
        }

        if(wall1 && !wall1->hasBehavior())
            wall1->assignBeh<Wall>();
        if(wall2 && !wall2->hasBehavior())
            wall2->assignBeh<Wall>();
        if(attack1 && !attack1->hasBehavior())
            attack1->assignBeh<AttackMain>();
        if(attack2 && !attack2->hasBehavior())
            attack2->assignBeh<AttackSupport>();

        Robot* goalie = team->getRobotByRole(RobotRole::GOALIE);
        if(goalie) goalie->assignBeh<Goalie>();

    }
    // We are defending against a free kick
    else if ((team->getGameState()->getRefereeCommand() == 'f' && team->getColor() == ROBOT_TEAM_BLUE)
          || (team->getGameState()->getRefereeCommand() == 'F' && team->getColor() == ROBOT_TEAM_YELLOW))
    {
        if(wall1)
            wall1->assignBeh<Wall>();
        if(wall2)
            wall2->assignBeh<Wall>();
        if(attack1)
            attack1->assignBeh<MarkBot>();
        if(attack2)
            attack2->assignBeh<MarkBot>();

        Robot* goalie = team->getRobotByRole(RobotRole::GOALIE);
        if(goalie) goalie->assignBeh<Goalie>();
    }
}

int FreeKickStrategy::getStatus()
{
    if ((kicker && kicker->getKickSpeed() > 0)
    || !Measurements::isClose(initial_bp, team->getGameState()->getBall()->getPosition(), 70))
        return KICKING; // Go to normal game strategy
    else
        return KICKED;
}

std::string FreeKickStrategy::getName(){
    return "free kick";
}
