#include "penaltystrategy.h"

#include "src/model/field.h"

PenaltyStrategy::PenaltyStrategy(Team* _team) : Strategy(_team) {

}

void PenaltyStrategy::assignBeh()
{
    // If we are taking the penalty kick
    char gs = GameState::getState();
    if ((gs == 'P' && team->getColor() == TEAM_BLUE) || (gs == 'p' && team->getColor() == TEAM_YELLOW))
    {
        // One of the defenders will take the penalty and move back
        Robot* kicker = team->getRobotByRole(RobotRole::DEFEND1);
        if(kicker){
            auto opponent_goal = Field::getGoalPosition(team->getOpponentSide());
            kicker->assignBeh<GenericMovementBehavior>(Point(opponent_goal - Point(1300,0)), 0);
        }

        // Position the usual attackers behind the 400 mm mark
        Robot* attack1 = team->getRobotByRole(RobotRole::ATTACK1);
        Robot* attack2 = team->getRobotByRole(RobotRole::ATTACK2);
        if(attack1)
            attack1->assignBeh<GenericMovementBehavior>(Point(-500, 1000), 0);
        if(attack2)
            attack2->assignBeh<GenericMovementBehavior>(Point(-500,-1000), 0);

        // The other defender walls our goal
        Robot* def = team->getRobotByRole(RobotRole::DEFEND2);
        if(def)
            def->assignBeh<Wall>();

        // Goalie
        NormalGameStrategy::assignGoalieIfOk(team);

    }
    // If we are on the receiving end of a penalty kick
    else
    {
        auto gp = Field::getGoalPosition(team->getSide());
        // All robots move behind the 400mm mark
        for(Robot* robot: team->getRobots())
        {
            if(robot != nullptr)
                robot->assignBeh<GenericMovementBehavior>(gp + Point(2000,(robot->getID() - 3)*300), 0);

        }
        // Position Goalie
        Robot* goalie = team->getRobotByRole(RobotRole::GOALIE);
        if(goalie)
        {
            goalie->clearBehavior();
            goalie->assignBeh<GenericMovementBehavior>(gp + Point(ROBOT_RADIUS,0),0);
        }


    }
}