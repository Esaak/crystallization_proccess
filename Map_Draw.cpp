//
// Created by п on 24.03.2022.
//

#include "Map_Draw.h"

Map_Draw::Map_Draw(Map &map) {
    this->map = map;
}

void Map_Draw::Display() {

  /*  int count =0;
    map.Set_cell_origin();
    while(count <= 100000)
    {
        //map.Rhompus_clean(count);
        map.Differential_equation_iteration();
        map.Crystallization_dissolution_check();
        std::cout << count << std::endl;
        count++;
    }
    sf::RenderWindow window(sf::VideoMode(this->map.Get_Width(), this->map.Get_Height()), "Particles");
    window.setFramerateLimit(30);
    window.setVerticalSyncEnabled(true);*/
    //set start values
    sf::RenderWindow window(sf::VideoMode(this->map.Get_Width(), this->map.Get_Height()), "Particles");
    window.setFramerateLimit(30);
    window.setVerticalSyncEnabled(true);
    map.Set_cell_origin();
    int count=0;
    auto start = std::chrono::system_clock::now();
    while (window.isOpen()) {
        // handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        //map.Rhompus_clean(count);
        //std::cout
        map.Thread_Differential_equation_iteration();
        //map.Thread_Differential_equation_iteration1();
        //map.Differential_equation_iteration();
        map.Crystallization_dissolution_check();

        count++;
        if(count%100==0){
            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> diff = end - start;
            std::cout<<diff.count()<<"\n";
        }
        //std::thread th((map.Rhompus),count);
        //map.Rhompus(count);
        //std::cout<<count<<"\n";
        //draw moving particles
        for (std::size_t i = 0; i < map.Get_Height() / Cells::cells_distance; i++) {
            for (std::size_t j = 0; j < map.Get_Width() / Cells::cells_distance; j++) {
                Cells_Draw circle(map.Get_cell_i(i, j));

                window.draw(circle.Get_circle(), 1, sf::Points);
            }

        }
        window.display();
    }
    /*while (window.isOpen()) {
        // handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        for (std::size_t i = 0; i < map.Get_Height() / Cells::cells_distance; i++) {
            for (std::size_t j = 0; j < map.Get_Width() / Cells::cells_distance; j++) {
                Cells_Draw circle(map.Get_cell_i(i, j));

                window.draw(circle.Get_circle(), 1, sf::Points);
            }

        }
        window.display();
    }

*/
}
