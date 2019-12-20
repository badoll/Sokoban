#include "controller.h"
bool is_movable(map_elem* b, int dir, int **map);

controller::controller():
    mainview(new main_window())
{
    QObject::connect(mainview, &main_window::keypress, this, &controller::handle_move);
    QObject::connect(mainview->get_restartbtn(), &QPushButton::clicked, this, &controller::restart);
    QObject::connect(mainview->get_hintbtn(), &QPushButton::clicked, this, &controller::set_hint);
}

controller::~controller()
{
    delete mainview;
    mainview = nullptr;
}

void
controller::init_game(std::string filepath)
{
    mapfile = filepath;
    mainview->init_map(filepath);
    mainview->chg_leftstep();
    const int **gm_map = const_cast<const int**>(mainview->get_map()->get_mapb());
    for (int i = 0; i < MAP_WIDTH; ++i) {
        for (int j = 0; j < MAP_HEIGHT; ++j) {
            if (gm_map[i][j] == BOX) {
                g_box = box(i,j);
            } else if (gm_map[i][j] == BOXMAN) {
                g_boxman = boxman(i,j);
            }
        }
    }
    mainview->show();
}

void
controller::handle_move(int dir)
{
    if (mainview->get_gstatus()->get_state() != GAMING) return;
    mainview->get_gstatus()->set_pdir(dir);
    const int **gm_map = const_cast<const int**>(mainview->get_map()->get_mapb());
    if (g_boxman.able_to_push(g_box,dir,gm_map)) {
        g_boxman.move(dir);
        g_box.move(dir);
        mainview->get_gstatus()->set_movef(true);
        mainview->get_gstatus()->set_pushf(true);
        int leftstep = mainview->get_gstatus()->get_leftstep();
        mainview->get_gstatus()->set_leftstep(leftstep - 1);
        mainview->chg_leftstep();
    } else if (g_boxman.is_movable(dir,gm_map)) {
        g_boxman.move(dir);
        mainview->get_gstatus()->set_movef(true);
    } else { //boxman can't move

    }
    basic_elem e = mainview->get_map()->get_end_point();
    if (e.x == g_box.get_x() && e.y == g_box.get_y()) {
        mainview->get_gstatus()->set_state(WIN);
    } else if (mainview->get_gstatus()->get_leftstep() == 0) {
        mainview->get_gstatus()->set_state(LOSE);
    }
    mainview->update_amove(g_boxman,g_box);
}

void
controller::restart()
{
    init_game(mapfile);
}

void
controller::set_hint()
{
    if (!mainview->get_gstatus()->get_hintf()) {
        mainview->get_gstatus()->set_hintf(true);
        mainview->get_hintbtn()->setText(QString("关闭提示"));
    } else {
        mainview->get_gstatus()->set_hintf(false);
        mainview->get_hintbtn()->setText(QString("提示"));
    }
    mainview->update_map();
}
