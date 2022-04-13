
//класс отвечает за то, как будет отрисовываться вся картинка проекта
//в Display происходит все действо

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include "Cells_Draw.h"

#ifndef FIRST_ATTEMPT_MAP_DRAW_H
#define FIRST_ATTEMPT_MAP_DRAW_H


class Map_Draw {
private:
    Map map;
public:
    Map_Draw(Map&);
    ~Map_Draw() = default;
    void Display();
};


#endif //FIRST_ATTEMPT_MAP_DRAW_H
