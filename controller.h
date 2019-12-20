#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "box.h"
#include "boxman.h"
#include "game_map.h"
#include "game_status.h"
#include "main_window.h"
#include <vector>
class controller: public QObject
{
    Q_OBJECT
public:
    controller();
    ~controller();
    void init_game(std::string);
    std::string get_mapfile() const {return mapfile;}
public slots:
    void handle_move(int dir);
    void restart();
    void set_hint();
private:
    std::string mapfile;
    main_window* mainview;
    box g_box;
    boxman g_boxman;
};

#endif // CONTROLLER_H
