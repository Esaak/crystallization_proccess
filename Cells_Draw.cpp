
#include "Cells_Draw.h"
Cells_Draw::Cells_Draw(Cells &cell) {
    if(cell.Get_state_color()) {

        circle[0] = sf::Vertex(sf::Vector2f(cell.Get_coordinates().first, cell.Get_coordinates().second),
                               color_crystal);
    }
    else {
        const int cell_color = (static_cast<double>(cell.Get_solution()) / (2*Cells::Solution_concentration*Cells::max_density) * 255);
        sf::Color color_free1 = sf::Color(cell_color, 0, 0, 200);
        circle[0] = sf::Vertex(sf::Vector2f(cell.Get_coordinates().first, cell.Get_coordinates().second), color_free1);
    }
}