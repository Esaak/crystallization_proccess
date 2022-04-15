//Класс который отвечает за  отрисовку кружочков, в зависимости от параметров кружочков

#ifndef FIRST_ATTEMPT_POINTS_DRAW_H
#define FIRST_ATTEMPT_POINTS_DRAW_H

#include <SFML/Graphics.hpp>
#include "Map.h"

class Cells_Draw {
protected:
    sf::Color color_free = sf::Color(255, 0, 0, 200);
    sf::Color color_crystal = sf::Color(0, 255, 0, 255);
    sf::Vertex circle[];
public:

    Cells_Draw(Cells &cell);

    sf::Vertex *Get_circle() {
        return circle;
    };

};


#endif //FIRST_ATTEMPT_POINTS_DRAW_H
