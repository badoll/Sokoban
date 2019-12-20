#include "game_status.h"
void
game_status::init()
{
    state = GAMING;
    push_flag = false;
    move_flag = false;
    hint_flag = false;
}
