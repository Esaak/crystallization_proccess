//
// Created by п on 24.03.2022.
//
//Это класс отвечающий за карту и что происходит с кружочкам,
// думаю это главный класс, в котором  будет вся математика( я так вижу)
#ifndef FIRST_ATTEMPT_MAP_H
#define FIRST_ATTEMPT_MAP_H

#include "Cells.h"

//template<unsigned T>
class Map : public Cells {
protected:
    unsigned Height;
    unsigned Width;
    unsigned number_of_Cells;
    std::vector<std::vector<Cells>> cell;
    std::vector<Cells*>cells_crystall;
public:
    Map();
    Map(unsigned, unsigned, unsigned);
    Map(const Map &);
    Map &operator=(const Map &map);
    ~Map() = default;
    unsigned Get_Height() const;
    unsigned Get_Width() const ;
    void Set_cell_coordinates(unsigned i, unsigned j);
    void Set_cell_impurity(unsigned i, unsigned j, double impurity);
    void Set_cell_solution(unsigned i, unsigned j, double solution);
    void Set_cell_next_step_solution(unsigned i, unsigned j, double next_step_solution);
    double Get_cell_next_step_solution(unsigned i, unsigned j);
    std::pair<double, double> Get_cell_coordinates(unsigned i, unsigned j) const;
    double Get_cell_impurity(unsigned i, unsigned j) const;
    double Get_cell_solution(unsigned i, unsigned j) const;
    Cells &Get_cell_i(unsigned i, unsigned j);
    Cells Get_cell_i(unsigned i, unsigned j) const;
    unsigned Get_number_of_Cells();

    static double  Get_max_density(double max_density) {
        return max_density;
    }

    static double  Get_equilibrium_concentration(double equilibrium_concentration){
        return equilibrium_concentration;
    }

    static double Get_basic_rate(double basic_rate){
        return basic_rate;
    }

    static double  Get_diffusion_coef(double diffusion_coef) {
        return diffusion_coef;
    }

    void Set_cell_origin();
    void Differential_equation_iteration();
    void Crystallization_dissolution_check();
    void Crystallization_process(int, int);
    void Rhompus(int);
    void Rhompus_clean(int);
};


#endif //FIRST_ATTEMPT_MAP_H
