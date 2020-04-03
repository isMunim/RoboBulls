#include "scontroller_normal_game.h"
#include <iostream>
#include "../strategies/stopstrategy.h"
#include "../strategies/kickoffstrategy.h"
#include "../strategies/freekickstrategy.h"
#include "../strategies/normalgamestrategy.h"
#include "../strategies/penaltystrategy.h"
#include "../strategies/indirectkickstrategy.h"
#include "../strategies/haltstrategy.h"

using std::cout;
using std::endl;
using std::make_pair;

namespace  {
    enum ControllerState { INITIAL,
                           STOP,
                           PENALTY,
                           KICK_OFF,
                           FREE_KICK,
                           INDIRECT_KICK,
                           HALT,
                           NORMAL_GAME
                         };
}

SControllerNormalGame::SControllerNormalGame(RobotTeam* team, YAML::Node c_node)
 : StrategyController(team,c_node)
{
    // assign a state for the controller for eash refbox command
    cmd_to_state[Referee_Command_STOP] = STOP; // stop game
    cmd_to_state[Referee_Command_GOAL_YELLOW] = STOP; // Yellow goal
    cmd_to_state[Referee_Command_GOAL_BLUE] = STOP; // Blue goal

    cmd_to_state[Referee_Command_PREPARE_PENALTY_YELLOW] = PENALTY; // Yellow penalty kick
    cmd_to_state[Referee_Command_PREPARE_PENALTY_BLUE] = PENALTY; // Blue penalty kick

    cmd_to_state[Referee_Command_PREPARE_KICKOFF_YELLOW] = KICK_OFF; // Yellow kick off
    cmd_to_state[Referee_Command_PREPARE_KICKOFF_BLUE] = KICK_OFF; // Blue kick off

    cmd_to_state[Referee_Command_DIRECT_FREE_YELLOW] = FREE_KICK; // Yellow free kick
    cmd_to_state[Referee_Command_DIRECT_FREE_BLUE] = FREE_KICK; // Blue free kick

    cmd_to_state[Referee_Command_INDIRECT_FREE_YELLOW] = INDIRECT_KICK; // Yellow indirect kick
    cmd_to_state[Referee_Command_INDIRECT_FREE_BLUE] = INDIRECT_KICK; // Blue indirect kick

    cmd_to_state[Referee_Command_TIMEOUT_YELLOW] = HALT; // Yellow time out ??
    cmd_to_state[Referee_Command_TIMEOUT_BLUE] = HALT; // Blue time out ??
    cmd_to_state[Referee_Command_HALT] = HALT; // Halt

    cmd_to_state[Referee_Command_NORMAL_START] = NORMAL_GAME; // normal game play
    cmd_to_state[Referee_Command_FORCE_START] = NORMAL_GAME; // force start

    //TODO: add states for the following messages:
//    Referee_Command_BALL_PLACEMENT_YELLOW = 16,
//    Referee_Command_BALL_PLACEMENT_BLUE = 17

    // assign controller state transitions for each state
    // first create empty maps
    state_transitions[HALT] = map<int,int>();
    state_transitions[STOP] = map<int,int>();
    state_transitions[PENALTY] = map<int,int>();
    state_transitions[KICK_OFF] = map<int,int>();
    state_transitions[FREE_KICK] = map<int,int>();
    state_transitions[INDIRECT_KICK] = map<int,int>();
    state_transitions[NORMAL_GAME] = map<int,int>();


    // now define the state transitions
    // TODO: so far a lot of logic is embued into each strategy
    // each strategy should be simplified and transitions should be implemented
    // through the controller instead. This will make the code more reusable,
    // modular, and understandable.
    state_transitions[FREE_KICK][FreeKickStrategy::KICKED] = NORMAL_GAME;
    state_transitions[INDIRECT_KICK][IndirectKickStrategy::KICKED] = NORMAL_GAME;





}


int SControllerNormalGame::getControllerState(Referee_Command game_command) {
    auto it = cmd_to_state.find(game_command);
    return it != cmd_to_state.end() ? it->second : STOP;
}


int SControllerNormalGame::getNextControllerState(int current_state,int strategy_status){
    if (current_state == UNINITIALIZED_STATE) return UNINITIALIZED_STATE; // state gets initialized by refbox

    auto state_map = state_transitions.find(current_state)->second;
    auto result = state_map.find(strategy_status);
    if(result == state_map.end()){
        cout<< "ERROR: Strategy controller did not define transition: ("
            << current_state << "," << strategy_status <<")" <<endl;
    }
    return result->second;
}


Strategy* SControllerNormalGame::loadStateStrategy(int state){
    switch (state) {
    case INITIAL :       return new StopStrategy(team);
    case STOP :          return new StopStrategy(team);
    case PENALTY :       return new PenaltyStrategy(team);
    case KICK_OFF :      return new KickOffStrategy(team);
    case FREE_KICK :     return new FreeKickStrategy(team);
    case INDIRECT_KICK : return new IndirectKickStrategy(team);
    case HALT :          return new HaltStrategy(team);
    case NORMAL_GAME :   return new NormalGameStrategy(team);
    }
    return new HaltStrategy(team);
}


