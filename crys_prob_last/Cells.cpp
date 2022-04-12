//
// Created by п on 24.03.2022.
//

#include "Cells.h"

Cells::Cells() : state(true) {};

/*
Cells::Cells(double x, double y, bool state, double solution, double impurity) :
        coordinates(x, y), state(state), solution(solution), impurity(impurity) {
    crys_rate = basic_rate * (solution * (max_density - equilibrium_concentration)) /
                (equilibrium_concentration * (max_density - solution));

    dis_rate = basic_rate * (equilibrium_concentration * (max_density - solution)) /
               (solution * (max_density - equilibrium_concentration));

    crys_prob = 1 - exp(-crys_rate * dt / dx);
    dis_prob = 1 - exp(-dis_rate * dt / dx);
}*/