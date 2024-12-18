#include <RandomRobot.h>

void RandomRobot::move(Maze& maze) {
    const std::array<int, 2> current_position = maze.get_current_position();
    bool is_valid_move = false;

    while (!is_valid_move) {
        const int direction = rand() % 4;
        try {
            const int new_x = current_position[0] + (direction == 1) - (direction == 3);
            const int new_y = current_position[1] + (direction == 2) - (direction == 0);

            maze.set_current_position(new_x, new_y);
            is_valid_move = true;
        }catch (Maze::InvalidMoveException& e) {}
    }


}