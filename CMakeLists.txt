cmake_minimum_required(VERSION 3.17)
project(first_attempt)

set(CMAKE_CXX_STANDARD 20)

add_executable(first_attempt
        main.cpp Map_Draw.cpp Map_Draw.h Map.cpp Map.h
        Cells_Draw.cpp
        Cells.h
        Cells.cpp
        Cells_Draw.h
        )
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR D:/informatika/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(D:/informatika/SFML/include)
target_link_libraries(first_attempt sfml-system sfml-window sfml-graphics sfml-audio)