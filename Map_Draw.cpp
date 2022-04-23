#include "Map_Draw.h"

Map_Draw::Map_Draw(Map &map) {
    this->map = map;
}


// rendering
void Map_Draw::Display() {
    //setting initial concentration
    map.Set_cell_origin();
    auto start = std::chrono::system_clock::now();

    //Drawing only the last frame at the end
    for (int i = 0; i < 1500; i++) {
        //selecting the number of cores to which the program is parallelized

        map.Thread_Differential_equation_iteration_4();
        //map.Thread_Differential_equation_iteration_all();
        //map.Thread_Differential_equation_iteration_2();
        map.Crystallization_dissolution_check();
        std::cout << i << "\n"; // current iteration
    }


    //drawing the window
    unsigned int count = 0;
    sf::RenderWindow window(sf::VideoMode(this->map.Get_Width(), this->map.Get_Height()), "Particles");
    window.setFramerateLimit(30);
    window.setVerticalSyncEnabled(true);
    while (window.isOpen()) {
        // handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //selecting the number of cores to which the program is parallelized
        /*
        map.Thread_Differential_equation_iteration_4();
        //map.Thread_Differential_equation_iteration_all();
        //map.Thread_Differential_equation_iteration_2();
        map.Crystallization_dissolution_check();
        window.clear();
        if (count % 100 == 0){
            std::cout << count << "\n";
        }
         */

        //drawing every frame
        for (std::size_t i = 0; i < map.Get_Height() / Cells::cells_distance; i++) {
            for (std::size_t j = 0; j < map.Get_Width() / Cells::cells_distance; j++) {
                Cells_Draw circle(map.Get_cell_i(i, j));

                window.draw(circle.Get_circle(), 1, sf::Points);
            }
        }
        count++;
        window.display();
    }
}
