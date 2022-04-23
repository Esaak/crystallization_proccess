#include "Cells.h"

Cells::Cells() : state(true) {};

/*########################################################################################*/
/*                              Getters and setters                                       */
/*########################################################################################*/

bool Cells::Get_state_color() const {
    return state_color;
}

void Cells::Set_state_color(bool state_c) {
    state_color = state_c;
}

void Cells::Set_coordinates(double x, double y) {
    coordinates.first = x * cells_distance;
    coordinates.second = y * cells_distance;
}

void Cells::Set_state(bool state) {
    this->state = state;
}

void Cells::Set_impurity(double impurity) {
    this->impurity = impurity;
}

void Cells::Set_solution(double solution) {
    this->solution = solution;
    this->impurity = max_density - this->solution;
}

void Cells::Set_next_step_solution(double next_step_solution) {
    this->next_step_solution = next_step_solution;
}

void Cells::Set_crys_rate_prob() {
    if (next_step_solution == max_density) {
        crys_rate = std::numeric_limits<double>::max();
        crys_prob = 1;
    } else {
        crys_rate = basic_rate * (next_step_solution * (max_density - equilibrium_concentration)) /
                    (equilibrium_concentration * (max_density - next_step_solution));
        //std::cout<<crys_rate<<"\n";
        crys_prob = 1 - exp(-crys_rate * dt * 1 / dx);
    }
};

void Cells::Set_dis_rate_prob() {
    dis_rate = basic_rate * (equilibrium_concentration * (max_density - next_step_solution)) /
               (next_step_solution * (max_density - equilibrium_concentration));
    if (crys_prob == 1) {
        dis_prob = 0;
    } else {
        dis_prob = 1 - exp(-dis_rate * dt * 1 / dx);
        //std::cout<<dis_prob<<"\n";
    }
};

void Cells::Set_crys_dis_rate_prob() {
    if (next_step_solution == max_density) {
        crys_rate = std::numeric_limits<double>::max();
        crys_prob = 1;
    } else {
        crys_rate = basic_rate * (next_step_solution * (max_density - equilibrium_concentration)) /
                    (equilibrium_concentration * (max_density - next_step_solution));
        //std::cout<<crys_rate<<"\n";
        crys_prob = 1 - exp(-crys_rate * dt * 1 / dx);
    }
    dis_rate = basic_rate * (equilibrium_concentration * (max_density - next_step_solution)) /
               (next_step_solution * (max_density - equilibrium_concentration));
    if (crys_prob == 1) {
        dis_prob = 0;
    } else {
        dis_prob = 1 - exp(-dis_rate * dt * 1 / dx);
    }

}

bool Cells::Get_state() const {
    return this->state;
}

std::pair<double, double> Cells::Get_coordinates() const {
    return this->coordinates;
}


double Cells::Get_impurity() const {
    return this->impurity;
}

double Cells::Get_next_step_solution() const {
    return this->next_step_solution;
};

double Cells::Get_solution() const {
    return this->solution;
}

double Cells::Get_crys_prob() const {
    return this->crys_prob;
}

double Cells::Get_crys_rate() const {
    return this->crys_rate;
}

double Cells::Get_dis_prob() const {
    return this->dis_prob;
}

double Cells::Get_dis_rate() const {
    return this->dis_rate;
}
