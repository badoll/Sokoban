#include "boxman.h"
bool
boxman::able_to_push(box b, int dir, const int** map)
{
    switch (dir) {
        case UP:
            if (get_x() == b.get_x() && get_y() - 1 == b.get_y() && b.is_movable(dir,map)) return true;
            break;
        case DOWN:
            if (get_x() == b.get_x() && get_y() + 1 == b.get_y() && b.is_movable(dir,map)) return true;
            break;
        case LEFT:
            if (get_x() - 1 == b.get_x() && get_y() == b.get_y() && b.is_movable(dir,map)) return true;
            break;
        case RIGHT:
            if (get_x() + 1 == b.get_x() && get_y() == b.get_y() && b.is_movable(dir,map)) return true;
            break;
    }
    return false;
}
