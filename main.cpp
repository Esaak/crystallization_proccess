#include "Map_Draw.h"

//setting the max crystallized substance density g/cm^3
double Cells::max_density = 2.165;
//setting the equilibrium concentration
double Cells::equilibrium_concentration = 0.5;
//setting the equilibrium speed rate
double Cells::basic_rate = 0.1;
//setting diffusion coefficient cm^2/c
double Cells::diffusion_coef = 0.001;
//setting distance between cells (scale)
unsigned Cells::cells_distance = 1;
//setting the time step in differential equation
const double Cells::dt = 0.000001;
//setting the distance step in differential equation
const double Cells::dx = 0.0001;
//setting concentration of the substance in solution
const double Cells::Solution_concentration = 0.2;

/*                              basic parameters
double Cells::max_density = 2.165;
double Cells::equilibrium_concentration = 0.5;
double Cells::basic_rate = 0.1;
double Cells::diffusion_coef = 0.001;
unsigned Cells::cells_distance = 1;
const double Cells::dt = 0.000001;
const double Cells::dx = 0.0001;
const double Cells::Solution_concentration = 0.2;
 */

template<typename T>
int Max_number(T Height, T Width, unsigned int cells_distance) {
    return (Height * Width / cells_distance) / cells_distance;
}

int main() {
    //setting window size
    size_t Height = 1000;
    size_t Width = 1000;
    //setting cells number
    unsigned number_of_points = Max_number(Height, Width, Cells::cells_distance);
    //creating a map
    Map map(Height, Width, number_of_points);
    //launching crystallization process
    Map_Draw a(map);
    //starting and displaying crystallization process
    a.Display();
    return 0;
}
