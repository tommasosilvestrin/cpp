#ifndef ROBOT_H
#define ROBOT_H

#include <Maze.h>

class Robot
{

    public:
        virtual void move (Maze& maze) = 0;
        virtual ~Robot() = default;
};

#endif