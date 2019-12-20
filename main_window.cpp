#include "main_window.h"
#include "ui_main_window.h"

main_window::main_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::main_window),
    map(new game_map()),
    g_status(new game_status())
{
    ui->setupUi(this);
    setFocusPolicy(Qt::StrongFocus);
}

main_window::~main_window()
{
    delete ui;
    ui = nullptr;
    delete map;
    map = nullptr;
    delete g_status;
    g_status = nullptr;
}

void
main_window::draw(int i, int j, int w, int h, QPainter& p, QImage img)
{
    QRect rect(i, j, w, h);
    p.drawImage(rect,img);
}
void
main_window::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    if (g_status->get_state() == GAMING) {
        auto unit_width = ui->game_window->width()/MAP_WIDTH;
        auto unit_height = ui->game_window->height()/MAP_HEIGHT;
        const int **gm_map = const_cast<const int**>(map->get_mapb());
        QImage box_i(":/picres/img/box.png");
        box_i.scaled(unit_width,unit_height);
        QImage boxman_i(":/picres/img/boxman.png");
        boxman_i.scaled(unit_width,unit_height);
        QImage wall_i(":/picres/img/wall.png");
        wall_i.scaled(unit_width,unit_height);
        QImage access_i(":/picres/img/access.png");
        access_i.scaled(unit_width,unit_height);
        for (int i = 0; i < MAP_WIDTH; ++i) {
            for (int j = 0; j < MAP_HEIGHT; ++j) {
                if (gm_map[i][j] == ACCESS) {
                    if (g_status->get_hintf() && map->in_bestway(basic_elem(i,j))) {
                        //hint
                        QImage hint_i(":/picres/img/hint.png");
                        hint_i.scaled(unit_width,unit_height);
                        draw(i*unit_width,j*unit_height,unit_width,unit_height,painter,hint_i);
                    } else {
                        draw(i*unit_width,j*unit_height,unit_width,unit_height,painter,access_i);
                    }
                } else if (gm_map[i][j] == WALL) {
                    draw(i*unit_width,j*unit_height,unit_width,unit_height,painter,wall_i);
                } else if (gm_map[i][j] == BOX) {
                    draw(i*unit_width,j*unit_height,unit_width,unit_height,painter,box_i);
                } else if (gm_map[i][j] == BOXMAN) {
                    draw(i*unit_width,j*unit_height,unit_width,unit_height,painter,boxman_i);
                }
            }
        }
        int sx = map->get_end_point().x;
        int sy = map->get_end_point().y;
        if (gm_map[sx][sy] == DEST || gm_map[sx][sy] == ACCESS) {
            QImage endp_i(":/picres/img/endp.png");
            endp_i.scaled(unit_width,unit_height);
            draw(sx*unit_width,sy*unit_height,unit_width,unit_height,painter,endp_i);
        }
    } else if (g_status->get_state() == WIN) {
        QImage win_i(":/picres/img/win.jpg");
        auto w = ui->game_window->width();
        auto h = ui->game_window->height();
        win_i.scaled(w,h);
        draw(0,0,w,h,painter,win_i);
    } else if (g_status->get_state() == LOSE) {
        QImage lose_i(":/picres/img/lose.jpeg");
        auto w = ui->game_window->width();
        auto h = ui->game_window->height();
        lose_i.scaled(w,h);
        draw(0,0,w,h,painter,lose_i);
    }
}

void
main_window::keyPressEvent(QKeyEvent* e)
{
    switch (e->key()) {
        case Qt::Key_Up: emit keypress(UP); break;
        case Qt::Key_Down: emit keypress(DOWN); break;
        case Qt::Key_Left: emit keypress(LEFT); break;
        case Qt::Key_Right: emit keypress(RIGHT); break;
    }
}

void
main_window::init_map(std::string filepath)
{
    map->load(filepath);
    g_status->init();
    g_status->set_leftstep(static_cast<int>(map->get_bestway().size()));
    int **gm_map = map->get_mapb();
    basic_elem s = map->get_start_point();
    int d1[] = {-1,1,0,0};
    int d2[] = {0,0,1,-1};
    for (int i = 0; i < 4; ++i) {
        if (s.x + d1[i] < 0 || s.x + d1[i] >= MAP_WIDTH
            || s.y + d2[i] < 0 || s.y + d2[i] >= MAP_HEIGHT) break;
        if (gm_map[s.x + d1[i]][s.y+d2[i]] == ACCESS) {
            gm_map[s.x][s.y] = BOX;
            gm_map[s.x + d1[i]][s.y+d2[i]] = BOXMAN;
            break;
        }
    }
    update();
}

void
main_window::update_amove(boxman bm, box b)
{
    int tx = 0, ty = 0;
    int move_dir = g_status->get_pdir();
    switch (move_dir) {
        case UP:
            tx = 0;
            ty = -1;
            break;
        case DOWN:
            tx = 0;
            ty = 1;
            break;
        case LEFT:
            tx = -1;
            ty = 0;
            break;
        case RIGHT:
            tx = 1;
            ty = 0;
            break;
    }
    int **gm_map = map->get_mapb();
    if (g_status->get_pushf()) {
        gm_map[bm.get_x()-tx][bm.get_y()-ty] = ACCESS;
        gm_map[bm.get_x()][bm.get_y()] = BOXMAN;
        gm_map[b.get_x()][b.get_y()] = BOX;

    } else if (g_status->get_movef()) {
        gm_map[bm.get_x()-tx][bm.get_y()-ty] = ACCESS;
        gm_map[bm.get_x()][bm.get_y()] = BOXMAN;
    } else { //not move

    }
    g_status->set_movef(false);
    g_status->set_pushf(false);
    update();
}

QPushButton*
main_window::get_restartbtn()
{
    return ui->restart_button;
}

QPushButton*
main_window::get_hintbtn()
{
    return ui->hint_Button;
}

void
main_window::chg_leftstep()
{
    ui->step_label->setText(QString::number(g_status->get_leftstep()));
}

void
main_window::update_map()
{
    update();
}
