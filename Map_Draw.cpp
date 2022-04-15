//
// Created by п on 24.03.2022.
//

#include "Map_Draw.h"

Map_Draw::Map_Draw(Map &map) {
    this->map = map;
}

void Map_Draw::Display() {
    sf::RenderWindow window(sf::VideoMode(this->map.Get_Width(), this->map.Get_Height()), "Particles");
    window.setFramerateLimit(30);
    window.setVerticalSyncEnabled(true);
    //set start values
    map.Set_cell_origin();
    while (window.isOpen()) {
        // handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        map.Differential_equation_iteration();
        map.Crystallization_dissolution_check();
        //draw moving particles
        for (std::size_t i = 0; i < map.Get_Height() / 2; i++) {
            for (std::size_t j = 0; j < map.Get_Width() / 2; j++) {
                Cells_Draw circle(map.Get_cell_i(i, j));

                window.draw(circle.Get_circle(), 1, sf::Points);
            }

        }
        window.display();
    }

}
