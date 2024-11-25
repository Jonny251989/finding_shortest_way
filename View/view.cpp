#include "view.h"
#include "model.h"
#include <QList>
#include <QGraphicsItem>

My_view::My_view(QWidget *parent, std::shared_ptr<Algorithm> algorithm): QGraphicsView(parent), wave_(algorithm){
    width = 600, heigth = 600;
    x = 0, y = 0;
    setFocusPolicy(Qt::NoFocus);
    this->setFixedHeight(heigth);
    this->setFixedWidth(width);
    this->setGeometry(0,0, 350, 350);
    this->setMinimumSize(350, 350);
    scene = new QGraphicsScene(this);
    this->setScene(scene);
    scene->setSceneRect(0,0, 360, 360); // Устанавливаем область графической сцены
    this->set_all_collors();
    this->setAlignment(Qt::AlignCenter);                        // Делаем привязку содержимого к центру
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);    // Растягиваем содержимое по виджету
    this->draw_field();

    connect(wave_.get(), &Algorithm::send_count_path, this, &My_view::draw_nearest_path);
}

void My_view::set_all_collors(){
    temporary_color_from = QColor(Qt::red);
    temporary_color_to = QColor(Qt::green);
    color_from = QColor(Qt::red);
    color_to = QColor(Qt::darkGreen);
    highlight_color = QColor(Qt::darkBlue);
    main_color = QColor(Qt::blue);
    path_color = QColor(Qt::yellow);
}

void My_view::draw_start_points(size_t x, size_t y){
    std::pair<Point*, Point*> points = wave_->get_start_points();
    auto item = new QGraphicsRectItem;

    if(points.first == nullptr && points.second == nullptr){
        item->setBrush(QBrush(temporary_color_from));
        if(!m_moved_items.empty()){
            QGraphicsRectItem* last_item = dynamic_cast<QGraphicsRectItem*>(m_moved_items.back());
            delete last_item;
        }
    }else if( points.first != nullptr && points.second == nullptr){
        QGraphicsRectItem* last_item_two = dynamic_cast<QGraphicsRectItem*>(m_moved_items.back());
        delete last_item_two;
        this->set_starts_points(x, y);
        item->setBrush(QBrush(temporary_color_to));
    }else
        this->set_starts_points(x, y);

    item->setRect(x * w_rect, y * h_rect, w_rect, h_rect);
    scene->addItem(item);
    m_moved_items.push_back(item);
}

void My_view::set_starts_points(int x, int y){
    std::pair<Point*, Point*> points = wave_->get_start_points();

    if( points.first != nullptr && points.second == nullptr){
        from = wave_->get_start_points().first;
        auto item_first = new QGraphicsRectItem(from->x * w_rect, from->y * h_rect, w_rect, h_rect);
        item_first->setBrush(QBrush(color_from));
        scene->addItem(item_first);
        m_moved_items.push_back(item_first);
    }else{
        to = wave_->get_start_points().second;
        auto item_finish = new QGraphicsRectItem(x * w_rect, y * h_rect, w_rect, h_rect);
        item_finish->setBrush(QBrush(color_to));
        scene->addItem(item_finish);
        m_moved_items.push_back(item_finish);
    }
}

void My_view::draw_nearest_path(int count){
    std::vector<Point*> nearest_path = wave_->get_nearest_path();
    auto item = new QGraphicsRectItem;

    if(((nearest_path[count]->x == from->x) && nearest_path[count]->y == from->y))
        item->setBrush(QBrush(color_from));

    else if(((nearest_path[count]->x == to->x)&& nearest_path[count]->y == to->y))
        item->setBrush(QBrush(color_to));
    else
        item->setBrush(QBrush(path_color));
    

    item->setRect(nearest_path[count]->x*w_rect, nearest_path[count]->y*h_rect, w_rect, h_rect);
    scene->addItem(item);
    m_moved_items.push_back(item);
}

void My_view::draw_field(){
    QPen pen_free_item(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    auto obstruction = wave_->get_obstruction();

    for(int rows = 0; rows < SIZE_FIELD; ++rows){
        for(int columns = 0; columns < SIZE_FIELD; ++columns){
            auto item = new QGraphicsRectItem(
                columns * w_rect, rows * h_rect,
                w_rect, h_rect);
            item->setPen(pen_free_item);
            item->setZValue(0);
            scene->addItem(item);
        }
    }
    for(Point* one: obstruction){
        auto item_obstr = new QGraphicsRectItem(one->x * w_rect, one->y * h_rect, w_rect, h_rect);
        item_obstr->setBrush(QBrush(QColor(Qt::darkMagenta)));
        scene->addItem(item_obstr);
    }
}

My_view::~My_view(){
    
}

