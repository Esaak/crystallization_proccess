
#include "Map_Draw.h"

double Cells::max_density = 2;
double Cells::equilibrium_concentration = 1;
double Cells::basic_rate = 0.1;
double Cells::diffusion_coef = 1;
template <typename T>
int Max_number (T Height, T Width, int step){
    return (Height*Width/step)/step;
}
int main() {
    unsigned Height = 1000;
    unsigned Width = 1000;
    unsigned number_of_points = Height * Width / 4;

    //Cells::max_density = 2; // г/см3
    //Map::max_density = 2;
//    Map::equilibrium_concentration = 1; // г/см3
//    Map::basic_rate = 0.1; // см/с
//    Map::diffusion_coef = 1; // см2/с
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 100);
    //double max_density = 2; // г/см3

    Map map(Height, Width, number_of_points);
    //map.Set_max_density(max_density);
    Map_Draw a(map);
    a.Display();
    return 0;
}
