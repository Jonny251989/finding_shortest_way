#pragma once

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QObject>
#include <memory>
#include "model.h"
#include "widget.h"

class Algorithm;
struct Point;
class My_view : public QGraphicsView{
    Q_OBJECT
public:
    My_view( QWidget *parent = nullptr, std::shared_ptr<Algorithm> algorithm = nullptr );
    void draw_field();
    void draw_nearest_path(int);
    void draw_path(int);
    void set_starts_points(int,int);
    void draw_start_points(size_t, size_t);
    void set_all_collors();
    ~My_view();
signals:
    void stop();
private:
    size_t x, y;
    std::shared_ptr<Algorithm> wave_;
    Point* from = nullptr;
    Point* to = nullptr;
    std::list<QGraphicsItem*> m_moved_items;
    QGraphicsScene* scene;
    QColor temporary_color_from;
    QColor temporary_color_to;
    QColor color_from;
    QColor color_to;
    QColor highlight_color;
    QColor main_color;
    QColor path_color;
    int width, heigth;
};