#ifndef MAP_ELEM_H
#define MAP_ELEM_H
#include <iostream>
#include <string>
const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 20;
enum elem
{
    ACCESS,
    WALL,
    START,
    DEST,
    BOX,
    BOXMAN
};

enum direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

typedef struct basic_elem{
    basic_elem() = default;
    basic_elem(int xx,int yy):x(xx),y(yy) {}
    bool operator==(const basic_elem& b) {
        if (x == b.x && y == b.y) return true;
        return false;
    }
    int x;
    int y;
}basic_elem;


class map_elem {
public:
    map_elem() = default;
    map_elem(int xx, int yy): x(xx), y(yy) {}
    int get_x() const {return x;}
    int get_y() const {return y;}
    void set_x(int xx) {x = xx;}
    void set_y(int yy) {y = yy;}
    void move(int dir);
    bool is_movable(int dir, const int **map);
private:
    int x;
    int y;
};

#endif // MAP_ELEM_H
