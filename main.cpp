
#include "Map_Draw.h"
int main() {
    unsigned Height=600;
    unsigned Width = 800;
    unsigned number_of_points = 4800;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 100);
    Map map(Height, Width, number_of_points);
    Map_Draw a(map);
    a.Display();
    return 0;
}
