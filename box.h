#ifndef BOX_H
#define BOX_H
#include "map_elem.h"

class box: public map_elem
{
public:
    box() = default;
    box(int xx, int yy): map_elem(xx,yy) {}
};

#endif // BOX_H
