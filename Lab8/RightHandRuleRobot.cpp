
#include <RightHandRuleRobot.h>

void RightHandRuleRobot::move(Maze& maze) {
    const std::array<int, 2> current_position = maze.get_current_position();
    bool is_valid_move = false;

    while (!is_valid_move) {
        const int direction = current_direction;
        try {
            const int new_x = current_position[0] + (direction == 1) - (direction == 3);
            const int new_y = current_position[1] + (direction == 2) - (direction == 0);

            maze.set_current_position(new_x, new_y);
            is_valid_move = true;
        } catch (Maze::InvalidMoveException& e) {
            current_direction = (4 + (current_direction - 1)) % 4;
            found_wall = true;
        }
    }

    if (found_wall) {
        const int right_x = current_position[0] + (current_direction == 1) - (current_direction == 3);
        const int right_y = current_position[1] + (current_direction == 2) - (current_direction == 0);
        if (!maze.is_wall(right_x, right_y)) {
            current_direction = (current_direction + 1) % 4;
        }
    }

}
