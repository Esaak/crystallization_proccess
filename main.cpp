
#include "Map_Draw.h"
//setting the max crystallized substance density g/cm^3
//double Cells::max_density = 3.6;
double Cells::max_density = 2.165;
//setting the equilibrium concentration
//double Cells::equilibrium_concentration = 0.1;
double Cells::equilibrium_concentration = 0.7;
//setting the equilibrium speed rate
//double Cells::basic_rate = 1;
double Cells::basic_rate = 0.1;
//setting diffusion coefficient cm^2/c
//double Cells::diffusion_coef = 0.0000045;
double Cells::diffusion_coef = 0.0001;
//setting distance between cells
unsigned Cells::cells_distance =2;
//setting the time step in differential equation
const double Cells::dt = 0.0001;
//setting the distance step in differential equation
const double Cells:: dx = 0.001;
//setting the number of cells
const double Cells:: Solution_concentration = 0.2;
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
