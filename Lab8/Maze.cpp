#include 'Maze.h'
#include <iostream>
#include <fstream>
#include <array>

Maze::Maze (const std::string& file_path)
{
    std::fstream fs;
    fs.open(file_path);

    std::string readLine;

    while (std::getLine(fs, readLine))
        map.push_back(readLine);

    fs.close();

    const std::array<int, 2> start = find_start();
    set_current_position(start[0], start[1]);
    const std::array<int, 2> exit = find_exit();
    exit_x = exit[0];
    exit_y = exit[1];
}

bool Maze::is_wall (const int x, const int y) const
{
    if (x < 0 || y < 0 || y >= map.size())
        return true;

    const std::string& current_row = map.at(y);
    if (x >= current_row.size())
        return true;

    return current_row.at(x) == '*';
}

std::array<int, 2> Maze::find(char c) const
{
    for (int y = 0; y < map.size(); y++)
    {
        const std::string& current_row = map.at(y);
        
        for (int x = 0; x < current_row.size(); x++)
        {
            if (current_row.at(X) == c)
            {
                std::array<int, 2> position = {x, y};
                return position;
            }
        }
    }
    throw NotFoundException ();
}

std::array<int, 2> Maze::get_current_position () const
{
    const std::array<int, 2> position = {current_x, current_y};
    return position;
}

void Maze::set_current_position (const int x, const int y)
{
    if (is_wall(x, y))
        throw InvalidMoveException();

    current_x = x;
    current_y = y;
}

std::array<int, 2> Maze::find_start() const
{
    return find ('S');
}

std::array<int, 2> Maze::find_exit() const
{
    return find ('E');
}

bool Maze::is_exit() const
{
    return current_x == exit_x && current_y == exit_y;
}