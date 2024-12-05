#ifndef Maze_h
#define Maze_h

#include <iostream>
#include <fstream>

class Maze
{
    public:
        Maze (void);
        Maze (std::fstream &fs);
        
        constexpr std::vector<std::vector<char>> GRID;
        void insert_maze (std::fstream &fs);
        
        bool is_exits(int position);
        
        constexpr int starting_position;
    
    private:
        std::vector<int> exit_positions;
};

#endif