#include 'Maze.h'
#include <iostream>
#include <fstream>

Maze::Maze (void) {}
Maze::Maze (std::fstream &fs)
{
    insert_maze(fs);
}

void Maze::insert_maze (std::fstream &fs)
{
    char temp_char;
    for (int i = 0; i < 9; i++)
    {
        for (int k = 0; k < 9; k++)
        {
            temp_char = (char)fs.get();
            if (temp_char == "E")
                exits_position.push_back(i*9+k);
            if (temp_char == "S")
                starting_position = i*9+k;
            GRID[i][k] = temp_char;
        }
    }
}

bool Maze::is_exits (int position)
{
    for (int i : exits_position)
        if (i == position)
            return true;
    
    return false;
}