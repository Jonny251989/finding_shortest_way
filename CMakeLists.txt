cmake_minimum_required(VERSION 3.15)
project (shortest_way CXX)

set(target shortest_way)
set(CMAKE_AUTOMOC ON) # Автоматически запускает moc
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON) # Для ресурсов Qt
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_package(Qt6 REQUIRED COMPONENTS Core Widgets )

add_subdirectory(Widget)
add_subdirectory(View)
add_subdirectory(Model)

add_executable(${target} ${SOURCES} main.cpp)
    
target_link_libraries (${target} widget Qt6::Widgets)
