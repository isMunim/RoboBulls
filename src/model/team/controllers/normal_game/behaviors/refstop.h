#ifndef REFSTOP_H
#define REFSTOP_H

#include "model/robot/behaviors/genericmovementbehavior.h"
#include "utilities/comparisons.h"
#include "utilities/region/defencearea.h"

/*!
 * @file
 * @author Muhaimen Shamsi
 * @brief Moves the robots 500mm away from the ball and stops them.
 *
 * Also moves them out of the defence areas.
 *
 * The is designed to be compliant with the "Stop" signal from refbox.
 * It is assigned by the "Stop" strategy to every robot except the goalie.
 */

class RefStop : public GenericMovementBehavior
{
public:
    RefStop(Robot* robot);
    bool perform() override;
    bool isFinished() override;
    string getName() override;
private:
    bool finished;
};

#endif // REFSTOP_H
