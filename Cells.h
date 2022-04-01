//
// Created by п on 24.03.2022.
//
//Класс отвечающий за то что будет происходить с кружочками
//Точнее за то, какие значения они будут принимать, хранить данные о каждом кружочке
#ifndef FIRST_ATTEMPT_Cells_H
#define FIRST_ATTEMPT_Cells_H

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>

const double dt = 0.00001; // 10 в -5 секунд
const double dx = 0.01; // в сантиметрах, соответствует 100 мкм

class Cells {
protected:
    std::pair<double, double> coordinates;
    bool state; // state = 1 - if crystallized, otherwise state = 0
    double solution;
    double next_step_solution;
    double impurity;
    double crys_prob; // crystallization probability
    double dis_prob; // dissolution probability
    double crys_rate; // crystallization rate
    double dis_rate; // dissolution rate
    //double max_density;

public:
    static double max_density;
    static double equilibrium_concentration;
    static double basic_rate;
    static double diffusion_coef;
    Cells();

    //Cells(double, double, bool, double, double);

    void Set_coordinates(double x, double y) {
        coordinates.first = x;
        coordinates.second = y;
    }

    void Set_state(bool state) {
        this->state = state;
    }

    void Set_impurity(double impurity) {
        this->impurity = impurity;
    }

    void Set_solution(double solution) {
        this->solution = solution;
    }
    void Set_next_step_solution( double next_step_solution){
        this->next_step_solution = next_step_solution;
    }

    void Set_crys_rate_prob(){
        crys_rate = basic_rate * (solution * (max_density - equilibrium_concentration)) /
                            (equilibrium_concentration * (max_density - solution));
        crys_prob = 1 - exp(-crys_rate * dt / dx);
    };

    void Set_dis_rate_prob(){
        dis_rate = basic_rate * (equilibrium_concentration * (max_density - solution)) /
                         (solution * (max_density - equilibrium_concentration));
        dis_prob = 1 - exp(-dis_rate * dt / dx);
    };

    bool Get_state() const {
        return this->state;
    }

    std::pair<double, double> Get_coordinates() const {
        return this->coordinates;
    }


    double Get_impurity() const {
        return this->impurity;
    }
    double  Get_next_step_solution() const{
        return next_step_solution;
    };
    double Get_solution() const {
        return this->solution;
    }

    double Get_crys_prob() const {
        return this->crys_prob;
    }

    double Get_dis_prob() const {
        return this->dis_prob;
    }
    double Get_crys_rate() const{
        return crys_rate;
    }
    double Get_dis_rate() const{
        return dis_rate;
    }



};


#endif //FIRST_ATTEMPT_Cells_H
