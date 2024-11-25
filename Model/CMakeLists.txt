set(target model)

add_library(${target} STATIC model.cpp)

target_include_directories(${target} PUBLIC .)

target_link_libraries (${target} widget Qt6::Widgets)