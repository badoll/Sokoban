#ifndef GAME_MAP_H
#define GAME_MAP_H
#include <QFile>
#include <QString>
#include <QTextStream>
#include "map_elem.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
class game_map
{
public:
    game_map();
    ~game_map();
    void load(std::string filepath);
    void load();
    std::vector<basic_elem> get_wall() const {return wall;}
    basic_elem get_start_point() const {return start_point;}
    basic_elem get_end_point() const {return end_point;}
    int** get_mapb() const {return map_b;}
    std::vector<basic_elem> get_bestway() const {return bestway;}
    void find_bestway();
    bool in_bestway(basic_elem point);
private:
    std::vector<basic_elem> wall;
    basic_elem start_point;
    basic_elem end_point;
    int **map_b;
    std::vector<basic_elem> bestway;
};

typedef struct path {
    path() = default;
    path(basic_elem b, std::vector<basic_elem> p): point(b), paths(p) {}
    basic_elem point;
    std::vector<basic_elem> paths;
}path;

#endif // GAME_MAP_H
