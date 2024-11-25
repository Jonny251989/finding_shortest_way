#pragma once

#include <QWidget>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <memory>
#include "view.h"
#include "model.h"

extern const int SIZE_FIELD;
extern const int width;
extern const int height;
extern int hold;
extern const int w_rect;
extern const int h_rect;

struct Point{
    int x, y;
    Point* previous;
    bool processed;

    Point(int x_ = -1, int y_ = -1, Point* previous_ = nullptr, bool processed_ = false ): x(x_), y(y_), previous(previous_), processed(processed_){
    }

    Point& operator=(const Point*& point){
        *this = point;
        this->x = point ->x;
        this->y = point ->y;
        return *this;
    }
};
class My_view;
class Algorithm;
class Widget : public QWidget{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    void checkBorder();
    ~Widget();
private:
    std::shared_ptr<Algorithm> algorithm_;
    std::shared_ptr<My_view> view_;
    Point* from_ = nullptr;
    Point* to_ = nullptr;
    size_t x, y;
protected:
   virtual void keyPressEvent(QKeyEvent* event);

signals:
    void emit_point_start(int, int);
};