#ifndef Maze_h
#define Maze_h

#include <vector>
#include <string>
#include <array>

class Maze
{
    public:
        Maze (const std::string& file_path);
        
        bool is_wall (int x, int y) const;

        std::array<int, 2> get_current_position () const;
        void set_current_position (int x, int y);

        bool is_exit () const;

        class NotFoundException final : std::exception {};
        class InvalidMoveException final : std::exception {};
    
    private:
        int current_x {};
        int current_y {};

        std::vector<std::string> map;
        std::array<int, 2> find (char c) const;
        std::array<int, 2> find_start () const;
        std::array<int, 2> find_exit () const;

        int exit_x {};
        int exit_y {}:
};

#endif