#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include <QMainWindow>
#include <QPushButton>
#include <QPainter>
#include <QKeyEvent>
#include <QImage>
#include <QRect>
#include <QRgb>
#include <QColor>
#include "game_map.h"
#include "box.h"
#include "boxman.h"
#include "game_status.h"
namespace Ui {
class main_window;
}

class main_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit main_window(QWidget *parent = nullptr);
    ~main_window();
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent*);
    void init_map(std::string filepath);
    void update_amove(boxman bm, box b);
    void draw(int i, int j, int w, int h,QPainter& p, QImage img);
    game_map* get_map() const {return map;}
    void set_map(game_map m);
    game_status* get_gstatus() const {return g_status;}
    QPushButton* get_restartbtn();
    QPushButton* get_hintbtn();
    void chg_leftstep();
    void update_map();
signals:
    void keypress(int dir);

private:
    Ui::main_window *ui;
    game_map* map;
    game_status* g_status;
};

#endif // MAIN_WINDOW_H
