#ifndef HALTSTRATEGY_H
#define HALTSTRATEGY_H
#include "src/strategy/strategy.h"

/*! @brief Strategy to implement the Halt game state 'H'
 *  @author Narges G */

class HaltStrategy : public Strategy
{
public:
    HaltStrategy(Team* _team);
    void assignBeh();
};

#endif // HALTSTRATEGY_H