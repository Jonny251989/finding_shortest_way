#pragma once

#include <QObject>
#include <QTimer>
#include <QString>
#include <vector>
#include <list>
#include <algorithm>
#include "widget.h"

struct Point;
class Algorithm: public QObject {
    Q_OBJECT

public:
    Algorithm(QObject *parent = nullptr);

    void set_start_points(Point*);
    void running_algorithm();
    void search_func();
    bool checking_of_conditions(const Point*, const int, const int);
    bool search_collisions_points(const int, const int);
    Point* check_not_processed_point();
    void fill_nearest_path(Point* point);
    std::vector<Point*> get_nearest_path();
    std::list<Point*> get_obstruction();
    std::pair<Point*,Point*>get_start_points();
    void checkBorder();
    void delete_points();

    ~Algorithm();

signals:
    void send_count_path(int);
    
public slots:
    void update_draw_nearest_path();

private:
    int x, y;
    size_t count;
    QTimer* timer_set_points;
    QTimer* timer;
    QTimer* timer_path;    
    
    Point* from_;
    Point* to_;
    
    std::vector<Point*> processed;
    std::vector<Point*> nearest_path;
    std::list<Point*> obstruction;
};