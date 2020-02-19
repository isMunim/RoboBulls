﻿#define _USE_MATH_DEFINES
#include <cmath>
#include "objectposition.h"
#include "fieldpanel.h"
#include "gamepanel.h"
#include "src/model/game_state.h"
#include "mainwindow.h"
#include "src/model/ball.h"

//Helper Classes
#include "guiscene.h"

ObjectPosition::ObjectPosition(MainWindow * mw) {
    dash = mw;
}

void ObjectPosition::setupPastBotPoints() {
    for (int i=0; i<dash->teamSize_blue; i++) {
        auto* roboti = dash->getSelectedTeam()->getRobot(i);
        if (roboti != NULL) {
            pastBotPoints[i].x = 0;
            pastBotPoints[i].y = 0;
            // also, let's fill the oldSpeeds array
            oldSpeeds[i] = 0;
        }
    }
}

void ObjectPosition::getPastBotPoints() {
//    if (dash->gamepanel->tick && dash->gamepanel->seconds%2 == 0) {
//    if (dash->gamepanel->tick) {
        for (int i=0; i<dash->teamSize_blue; i++) {
            auto* roboti = dash->getSelectedTeam()->getRobot(i);
            if (roboti != NULL) {
                pastBotPoints[i].x = roboti->getPosition().x;
                pastBotPoints[i].y = roboti->getPosition().y;
            }
        }
//    }
}

void ObjectPosition::getNewBotPoints() {
    for (int i=0; i<dash->teamSize_blue; i++) {
        auto* roboti = dash->getSelectedTeam()->getRobot(i);
        if (roboti != NULL) {
            newBotPoints[i].x = roboti->getPosition().x;
            newBotPoints[i].y = roboti->getPosition().y;
        }
    }
}

void ObjectPosition::getBotSpeeds() {
    for (int i=0; i<dash->teamSize_blue; i++) {
        auto* roboti = dash->getSelectedTeam()->getRobot(i);
        if (roboti != NULL) {
            float s = 0;
            float c;
            Point currentPos;
            Point pastPos;
            currentPos.x = newBotPoints[i].x;
            currentPos.y = newBotPoints[i].y;
            pastPos.x = pastBotPoints[i].x;
            pastPos.y = pastBotPoints[i].y;

//            c = ( pow((currentPos.x - pastPos.x), 2) + pow((currentPos.y - pastPos.y), 2) );
            c = Measurements::distance(currentPos,pastPos);

            s = sqrt(c);
            botSpeeds[dash->getSelectedTeamId()][i] = s;
        }
    }

}

void ObjectPosition::getOldSpeeds() {
    for (int i=0; i<dash->teamSize_blue; i++) {
        auto* roboti = dash->getSelectedTeam()->getRobot(i);
        if (roboti != NULL) {
            oldSpeeds[i] = botSpeeds[dash->getSelectedTeamId()][i];
        }
    }
}

//void ObjectPosition::updateBotSpeedsRecord() {
//    botSpeedsRecord.push_front(botSpeeds);
//    if (botSpeedsRecord.size() > 10) {
//        botSpeedsRecord.pop_back();
//    }
//}

int ObjectPosition::getVelocity(int id) {
    int velocity = 0;
    int wheels = 0;
    int LF = 0;
    int RF = 0;
    int LB = 0;
    int RB = 0;

    auto* robot = dash->getSelectedTeam()->getRobot(id);
    if(robot == NULL)
        return 0;

    if (robot->getDriveType() == fourWheelOmni ) {
            LF = robot->getLF();
            RF = robot->getRF();
            LB = robot->getLB();
            RB = robot->getRB();
            velocity += LF;
            wheels++;
            velocity += RF;
            wheels++;
            velocity += LB;
            wheels++;
            velocity += RB;
            wheels++;
    } else if ( robot->getDriveType() == differential ) {
            LF = robot->getL();
            RF = robot->getR();
            velocity += LF;
            wheels++;
            velocity += RF;
            wheels++;
    } else if ( robot->getDriveType() == threeWheelOmni ) {
            LF = robot->getLF();
            RF = robot->getRF();
        int b = robot->getB();
            velocity += LF;
            wheels++;
            velocity += RF;
            wheels++;
            velocity += b;
            wheels++;
    }

    if (velocity != 0 && wheels != 0)
        velocity /= wheels;

    return velocity;
}


QString ObjectPosition::getBotOrientString(Robot* robot) {
    auto o = robot->getOrientation()*180/M_PI;
    std::string sOrient = std::to_string(int(o));
    QString qOrient = QString::fromStdString(sOrient);
    return qOrient;
}

double ObjectPosition::getBotOrientDouble(Robot* robot) {
    return robot->getOrientation()*180/M_PI;
}


float ObjectPosition::getBotSpeed(int id) {
    float s = 0;
    double c;
    Point currentPos;
    Point pastPos;
    //TODO: verify I can comment the if statement (myTeam used to be a function parameter)
//    if (myTeam) {
        currentPos.x = newBotPoints[id].x;
        currentPos.y = newBotPoints[id].y;
        pastPos.x = pastBotPoints[id].x;
        pastPos.y = pastBotPoints[id].y;
//    }

    c = ( pow((currentPos.x - pastPos.x), 2) + pow((currentPos.y - pastPos.y), 2) );

    s = sqrt(c);


    return s;
}

int ObjectPosition::getBallCoordX() {
    int b;
    b = Ball::getPosition().x;

    return b;
}

int ObjectPosition::getBallCoordY() {
    int b;
    b = Ball::getPosition().y;
    return b;
}

int ObjectPosition::getMouseCoordX() {
    int x = dash->fieldpanel->scene->mousePoint.x()-100;
    return x;
}

int ObjectPosition::getMouseCoordY() {
    int y = dash->fieldpanel->scene->mousePoint.y()-100;
    return y;
}

QStringList ObjectPosition::getKeyWords(std::string behavior) {
/** Takes a behavior title, parses it for keywords, and returns a list of them
 * */

    QStringList keywords;
    QString title = QString::fromStdString(behavior);

    if (title.contains("no behavior", Qt::CaseInsensitive)) {
        keywords.push_back("no behavior");
    }
    if (title.contains("ball", Qt::CaseInsensitive)) {
        keywords.push_back("ball");
    }
    if (title.contains("mov", Qt::CaseInsensitive)) {
        keywords.push_back("moving");
    }
    if (title.contains("pass", Qt::CaseInsensitive)) {
        keywords.push_back("passing");
    }
    if (title.contains("send", Qt::CaseInsensitive)) {
        keywords.push_back("sending");
    }
    if (title.contains("receiv", Qt::CaseInsensitive)) {
        keywords.push_back("receiving");
    }
    if (title.contains("defend", Qt::CaseInsensitive)) {
        keywords.push_back("defending");
    }
    if (title.contains("attack", Qt::CaseInsensitive)) {
        keywords.push_back("attacking");
    }
    if (title.contains("farfrom", Qt::CaseInsensitive)) {
        keywords.push_back("far from");
    }
    if (title.contains("nearto", Qt::CaseInsensitive)) {
        keywords.push_back("near to");
    }
    if (title.contains("penalty", Qt::CaseInsensitive)) {
        keywords.push_back("penalty");
    }
    if (title.contains("simple", Qt::CaseInsensitive)) {
        keywords.push_back("simple");
    }



    return keywords;
}