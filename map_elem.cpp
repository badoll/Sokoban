#include "map_elem.h"

void
map_elem::move(int dir)
{
    switch (dir) {
        case UP: {
            y--;
            break;
        }
        case DOWN: {
            y++;
            break;
        }
        case LEFT: {
            x--;
            break;
        }
        case RIGHT: {
            x++;
        }
    }
}

bool
map_elem::is_movable(int dir, const int **map) {
    switch (dir) {
        case UP:
            if (y-1 >= 0 && (map[x][y-1] == ACCESS || map[x][y-1] == DEST)) return true;
            break;
        case DOWN:
            if (y+1 < MAP_HEIGHT && (map[x][y+1] == ACCESS || map[x][y+1] == DEST)) return true;
            break;
        case LEFT:
            if (x-1 >= 0 && (map[x-1][y] == ACCESS || map[x-1][y] == DEST)) return true;
            break;
        case RIGHT:
            if (x+1 < MAP_WIDTH && (map[x+1][y] == ACCESS || map[x+1][y] == DEST)) return true;
            break;
    }
    return false;
}

