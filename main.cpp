
#include "Map_Draw.h"
//setting the max crystallized substance density
double Cells::max_density = 2;
//setting the equilibrium concentration
double Cells::equilibrium_concentration = 1;
//setting the equilibrium speed rate
double Cells::basic_rate = 0.1;
//setting diffusion coefficient
double Cells::diffusion_coef = 1;
//setting distance between cells
unsigned Cells::cells_distance =2;
//setting the time step in differential equation
const double Cells::dt = 0.00001;
//setting the distance step in differential equation
const double Cells:: dx = 0.01;
//setting the number of cells
template <typename T>
int Max_number (T Height, T Width,int cells_distance){
    return (Height*Width/cells_distance)/cells_distance;
}
int main() {
    //setting size of map
    size_t Height = 1000;
    size_t Width = 1000;
    //setting number of cells
    unsigned number_of_points = Max_number(Height, Width,Cells::cells_distance);
    //create map
    Map map(Height, Width, number_of_points);
    //create crystallization process
    Map_Draw a(map);
    //start and display crystallization process
    a.Display();
    return 0;
}
