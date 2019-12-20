#ifndef BOXMAN_H
#define BOXMAN_H

#include "map_elem.h"
#include "box.h"
class boxman: public map_elem
{
public:
    boxman() = default;
    boxman(int xx, int yy): map_elem(xx,yy) {}
    bool able_to_push(box b, int dir, const int **map);
};

#endif // BOXMAN_H
