
#include "Cells_Draw.h"
Cells_Draw::Cells_Draw(Cells &cell) {
    if(cell.Get_state())
        circle[0] = sf::Vertex(sf::Vector2f(  cell.Get_coordinates().first, cell.Get_coordinates().second), color_crystal);


    else
        circle[0] = sf::Vertex(sf::Vector2f(  cell.Get_coordinates().first, cell.Get_coordinates().second), color_free);
}