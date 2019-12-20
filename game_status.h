#ifndef GAME_STATUS_H
#define GAME_STATUS_H
#include "map_elem.h"
#include "box.h"
#include "boxman.h"
#include "game_map.h"
enum game_state {
    WIN,
    LOSE,
    GAMING
};

class game_status
{
public:
    game_status():state(GAMING) {}
    void set_state(int s) {state = s;}
    void set_pdir(int dir) {boxman_dir = dir;}
    void set_pushf(bool f) {push_flag = f;}
    void set_movef(bool f) {move_flag = f;}
    void set_hintf(bool f) {hint_flag = f;}
    int get_state() const {return state;}
    int get_pdir() const {return boxman_dir;}
    bool get_pushf() const {return push_flag;}
    bool get_movef() const {return move_flag;}
    bool get_hintf() const {return hint_flag;}
    void refresh() {push_flag = false; move_flag = false;}
    int get_leftstep() const {return left_step;}
    void set_leftstep(int step) {left_step = step;}
    void init();
private:
    int state;
    int boxman_dir;
    bool push_flag;
    bool move_flag;
    bool hint_flag;
    int left_step;
};

#endif // GAME_STATUS_H
