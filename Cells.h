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


class Cells {
protected:
    std::pair<double, double> coordinates;
    bool state; // state = 1 - if crystallized, otherwise state = 0
    double solution;

    double next_step_solution; // solution on next step
    double impurity;
    bool state_color; // state_color = 1 - if crystallized and we reached it, otherwise state_color = 0
    double crys_prob; // crystallization probability
    double dis_prob; // dissolution probability
    double crys_rate; // crystallization rate
    double dis_rate; // dissolution rate
    //double max_density;

public:
    static const double dt; // 10 in -5 seconds
    static const double dx; // in centimeters, = 100 micrometers
    static unsigned cells_distance;
    static double max_density;
    static double equilibrium_concentration;
    static double basic_rate;
    static double diffusion_coef;
    Cells();
    void Set_state_color(bool state_c);
    void Set_coordinates(double x, double y) ;
    void Set_state(bool state);
    void Set_impurity(double impurity);
    void Set_solution(double solution);
    void Set_next_step_solution( double next_step_solution);
    void Set_crys_rate_prob();
    void Set_dis_rate_prob();
    bool Get_state() const ;
    std::pair<double, double> Get_coordinates() const ;
    double Get_impurity() const ;
    double  Get_next_step_solution() const;
    double Get_solution() const ;
    double Get_crys_prob() const ;
    double Get_crys_rate() const ;
    double Get_dis_prob() const ;
    double Get_dis_rate() const ;
    bool Get_state_color() const;
};


#endif //FIRST_ATTEMPT_Cells_H
