#include "game_map.h"

game_map::game_map()
{
    map_b = new int*[MAP_WIDTH];
    for (int i = 0; i < MAP_WIDTH; ++i)
        map_b[i] = new int[MAP_HEIGHT];
    for (int i = 0; i < MAP_WIDTH; ++i)
        for (int j = 0; j < MAP_HEIGHT; ++j)
            map_b[i][j] = ACCESS;
}

game_map::~game_map()
{
    for (int i = 0; i < MAP_WIDTH; ++i) delete[] map_b[i];
    delete [] map_b;
    map_b = nullptr;
}

void
game_map::load(std::string filepath)
{
    QFile mapfile(QString::fromStdString(filepath));
    if (!mapfile.open(QIODevice::ReadOnly)) {
        load(); //default map
    }
    else {
        QTextStream text(&mapfile);
        QString line;
        int y = MAP_HEIGHT - 1;
        while (true) {
            line = text.readLine();
            std::istringstream s(line.toStdString());
            char m;
            int x = 0;
            while (s >> m) {
                if (m == '0') map_b[x][y] = ACCESS;
                else if (m == 'x'){
                    wall.push_back({x,y});
                    map_b[x][y] = WALL;
                }
                else if (m == '1'){
                    start_point = {x,y};
                    map_b[x][y] = START;
                }
                else if (m == '2') {
                    end_point = {x,y};
                    map_b[x][y] = DEST;
                }
                if (++x == MAP_WIDTH) break;
            }
            if (--y < 0) break;
        }
    }
    find_bestway();
}

void
game_map::load()
{
    std::vector<std::string> map = {
        "xxxxxxxxxxxxxxxxxxxx",
        "x000000000000000000x",
        "x0xx00000000xxxxx00x",
        "x000000000000000000x",
        "x0000000xxxxx000x00x",
        "x00xx00000000000000x",
        "x000000xxxxxxx0x000x",
        "x0x000000000000x000x",
        "x00x0x0000xxx00x200x",
        "x00000000x000000000x",
        "x000000000000000000x",
        "x0xxxxxxxxx00000xx0x",
        "x0000000000xxxx0000x",
        "x000000000000000000x",
        "x0000000000xxxx0000x",
        "x00xxxxxxxx00000000x",
        "x010000000000000000x",
        "x000000000000000000x",
        "x000000000000000000x",
        "xxxxxxxxxxxxxxxxxxxx",
    };
//    int x = 0, y = MAP_HEIGHT - 1;
//    for (const auto& m : map) {
//        for (const auto& s : m) {
//            if (s == '0') map_b[x][y] = ACCESS;
//            else if (s == 'x'){
//                std::cout << "1" << std::endl;
//                wall.push_back({x,y});
//                map_b[x][y] = WALL;
//            }
//            else if (s == '1'){
//                std::cout << "2" << std::endl;
//                start_point = {x,y};
//                map_b[x][y] = START;
//            }
//            else if (s == '2') {
//                std::cout << "3" << std::endl;
//                end_point = {x,y};
//                map_b[x][y] = DEST;
//            }
//            if (++x == MAP_WIDTH) break;
//        }
//        if (--y < 0) break;
//    }
    for (int i = 0; i < MAP_WIDTH; ++i) {
        for (int j = 0; j < MAP_HEIGHT; ++j) {
            int y = MAP_HEIGHT - 1 - j;
            if (map[i][j] == '0') map_b[i][y] = ACCESS;
            else if (map[i][j] == 'x'){
                wall.push_back({i,y});
                map_b[i][y] = WALL;
            }
            else if (map[i][j] == '1'){
                start_point = {i,y};
                map_b[i][y] = ACCESS;
            }
            else if (map[i][j] == '2') {
                end_point = {i,y};
                map_b[i][y] = DEST;
            }
        }
    }
}

void go(std::queue<path>& Q, int (*visit)[MAP_HEIGHT], path cur)
{
    Q.push(cur);
    visit[cur.point.x][cur.point.y] = 1;
}

bool is_block(int (*visit)[MAP_HEIGHT], basic_elem p, int** map)
{
    if (p.x < MAP_WIDTH && p.x  >= 0 && p.y< MAP_HEIGHT && p.y>= 0 &&
        visit[p.x][p.y] == 0 && map[p.x][p.y] != WALL) {
        return false;
    }
    return true;
}

void
game_map::find_bestway()
{
    int d1[] = {1,0,-1,0};
    int d2[] = {0,1,0,-1};
    int visit[MAP_WIDTH][MAP_HEIGHT];
    for (int i = 0; i < MAP_WIDTH; ++i)
        for (int j = 0; j < MAP_HEIGHT; ++j)
            visit[i][j] = 0;
    std::queue<path> Q;
    go(Q,visit,path(start_point,{start_point}));
    while (!Q.empty()) {
        path p = Q.front();
        Q.pop();
        basic_elem point = p.point;
        if (point.x == end_point.x && point.y == end_point.y) {
            bestway = p.paths;
            bestway.erase(bestway.begin());//去掉起点
            break;
        }
        for (int i = 0; i < 4; ++i) {
            basic_elem t(point.x+d1[i],point.y+d2[i]);
            std::vector<basic_elem> paths = p.paths;
            paths.push_back(t);
            if (!is_block(visit,t,map_b)) {
                path cur(t,paths);
                go(Q,visit,cur);
            }
        }
    }
}

bool
game_map::in_bestway(basic_elem point)
{
    for (auto p : bestway) {
        if (point == p) {
            return true;
        }
    }
    return false;
}
