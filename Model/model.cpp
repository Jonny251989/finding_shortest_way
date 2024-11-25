#include "model.h"


Algorithm::Algorithm(QObject* parent):QObject(parent){

    x = 0, y = 0, count = 0;
    obstruction.push_back(new Point(3,0));
    obstruction.push_back(new Point(3,1));
    obstruction.push_back(new Point(3,2));
}

void Algorithm::set_start_points(Point*point){
    if(!from_) from_= point;
    else to_ = point;
}

 void Algorithm::running_algorithm(){
    this->search_func();
    Point *end = processed.back();
    this->fill_nearest_path(end);
    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(update_draw_nearest_path()));
    timer->start(100);
 }

void Algorithm::update_draw_nearest_path(){
    if(count < nearest_path.size()){
        emit send_count_path(count);
        this->count = count + 1;
    }
    else{
        timer->stop();
        delete timer;
        this->count = 0;
    }
}

void Algorithm::fill_nearest_path(Point* point){

    if(point!= nullptr){
        this->fill_nearest_path(point->previous);
        nearest_path.push_back(point);
    }
}

 void Algorithm::search_func(){
    Point* temp_point = from_;
    temp_point->processed = true;
    processed.push_back(temp_point);

    while(true){

        for(int j_start = std::max(temp_point->y - 1, 0); j_start <= std::min(temp_point->y + 1, SIZE_FIELD - 1); ++j_start){ // ось Y
            for(int i_start = std::max(temp_point->x - 1, 0); i_start <= std::min(temp_point->x + 1, SIZE_FIELD - 1); ++i_start){ // ось X
                if(checking_of_conditions(temp_point, i_start, j_start)){
                    if( search_collisions_points( i_start, j_start) ){
                        Point* new_point = new Point(i_start, j_start,  temp_point, false);
                        if(new_point->x == to_->x && new_point->y == to_->y){
                            processed.push_back(new_point);
                            return;
                        }
                        else
                            processed.push_back(new_point); 
                    }
                }
            }
        }
        temp_point = check_not_processed_point();
        temp_point->processed = true;
    }
}

Point* Algorithm::check_not_processed_point(){
    auto point = std::find_if(processed.begin(), processed.end(), [=](Point* one){
            return one->processed == false;});

    if(point != processed.end()) 
        return *point;
    else
        return nullptr;
}

bool Algorithm::checking_of_conditions(const Point* temp_point, const int i_start_, const int j_start_){
    if( ((std::abs(i_start_ - temp_point->x) == 1) && (std::abs(j_start_ - temp_point->y) == 0)) ||
        ((std::abs(j_start_ - temp_point->y) == 1) && (std::abs(i_start_ - temp_point->x) == 0)) )
        return true;
    return false;
}

bool Algorithm::search_collisions_points(const int i_start_, const int j_start_){

    auto point = std::find_if(processed.begin(), processed.end(), [=](Point* one){
            return one->x ==i_start_ && one->y == j_start_;});

    if(point != processed.end()) 
        return false;

    auto point_obst = std::find_if(obstruction.begin(), obstruction.end(), [=](Point* one){
    return one->x ==i_start_ && one->y == j_start_;});

   if(point_obst != obstruction.end()) 
        return false;

    return true;
}

void Algorithm::delete_points(){
    for(Point* point: processed){
        delete point;
    }
    for(Point* point: obstruction){
        delete point;
    }
}

std::vector<Point*> Algorithm::get_nearest_path(){
   return nearest_path;
}

std::list<Point*> Algorithm::get_obstruction(){
    return obstruction;
}


std::pair<Point*,Point*> Algorithm::get_start_points(){
    return std::make_pair(from_, to_);
}

void Algorithm::checkBorder(){
    if (x > SIZE_FIELD - 1)
        x = 0;

    else if (x < 0)
        x = SIZE_FIELD - 1;

    else if (y > SIZE_FIELD - 1)
        y = 0;

    else if (y < 0)
        y = SIZE_FIELD - 1;
}

Algorithm::~Algorithm(){

}


