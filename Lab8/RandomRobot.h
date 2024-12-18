#ifndef RANDOM_ROBOT_H
#define RANDOM_ROBOT_H

#include "Robot.h"
#include "Maze.h"

class RandomRobot : public Robot {
public:
    void move(Maze& maze) override;
};

#endif