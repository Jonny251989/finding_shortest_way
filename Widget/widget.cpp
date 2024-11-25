#include "widget.h"

const int SIZE_FIELD = 6;
const int width = 350;
const int height = 350;
int hold = 10;
const int w_rect = 50;
const int h_rect = 50;
const int TOP = 10;

Widget::Widget(QWidget *parent): QWidget(parent){
    this->setFocus();
    this->resize(800,800);

    x = 0, y = 0;
    algorithm_ = std::make_shared<Algorithm>(this);
    view_ = std::make_shared<My_view>(this, algorithm_);
    view_->draw_start_points(x, y);
    connect(this, &Widget::emit_point_start, view_.get(), &My_view::draw_start_points);
}

void Widget::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
        case Qt::Key_Left:
            --x;
            break;
        case Qt::Key_Right:
            ++x;
            break;
        case Qt::Key_Up:
            --y;
            break;
        case Qt::Key_Down:
            ++y;
            break;
        case Qt::Key_Space:{
            if(this->from_ == nullptr){
                this->from_ = new Point(x, y);
                algorithm_->set_start_points(from_);
            }
            else{
                to_ = new Point(x, y);
                algorithm_-> set_start_points(to_);
                algorithm_->running_algorithm();
            }
            break;
        }
    }
    this->checkBorder();
    this->emit_point_start(x, y);
}

void Widget::checkBorder(){
    if (x > SIZE_FIELD - 1)
        x = 0;
    else if (x < 0)
        x = SIZE_FIELD - 1;
    else if (y > SIZE_FIELD - 1)
        y = 0;
    else if (y < 0)
        y = SIZE_FIELD - 1;
}

Widget::~Widget(){ }