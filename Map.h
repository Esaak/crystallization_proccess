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
    std::vector<Cells> cell;
public:
    Map();

    Map(unsigned, unsigned, unsigned);

    Map(const Map &);

    Map &operator=(const Map &map);

    ~Map() = default;

    unsigned Get_Height() const { return Height; };

    unsigned Get_Width() const { return Width; };

    void Set_cell_coordinates(unsigned i, double x, double y) {
        cell[i].Set_coordinates(x, y);
    };

    void Set_cell_impurity(unsigned i, double impurity) {
        cell[i].Set_impurity(impurity);
    }

    void Set_cell_solution(unsigned i, double solution) {
        cell[i].Set_solution(solution);
        //cell[i].Set_impurity(max_density - solution);
    }
    void Set_cell_next_step_solution(unsigned i, double next_step_solution){
        cell[i].Set_next_step_solution(next_step_solution);
    }
    double Get_cell_next_step_solution(unsigned i){
        return cell[i].Get_next_step_solution();
    }
    std::pair<double, double> Get_cell_coordinates(unsigned i) const {
        return cell[i].Get_coordinates();
    }

    double Get_cell_impurity(unsigned i) const {
        return cell[i].Get_impurity();
    }

    double Get_cell_solution(unsigned i) const {
        return cell[i].Get_solution();
    }

    Cells &Get_cell_i(unsigned i) {
        return cell[i];
    }

    Cells Get_cell_i(unsigned i) const {
        return cell[i];
    }

    unsigned Get_number_of_Cells() {
        return number_of_Cells;
    }

    void Set_cell_origin();

    void Set_cell_coordinates_iterative();

//    void Set_max_density(int i, double max_density) {
//        cell[i].Set_max_density = max_density;
//    }

    void Set_equilibrium_concentration(double equilibrium_concentration) {
        this->equilibrium_concentration = equilibrium_concentration;
    }

    void Set_basic_rate(double basic_rate) {
        this->basic_rate = basic_rate;
    }

    void Set_diffusion_coef(double diffusion_coef) {
        this->diffusion_coef = diffusion_coef;
    }

    static double Get_max_density(double max_density) {
        return max_density;
    }

    static double Get_equilibrium_concentration(double equilibrium_concentration){
        return equilibrium_concentration;
    }

    static double Get_basic_rate(double basic_rate){
        return basic_rate;
    }

    static double Get_diffusion_coef(double diffusion_coef) {
        return diffusion_coef;
    }

    void Differential_equation_iteration1();
    void Differential_equation_iteration2();
    void Crystallization_dissolution_check();
    void Crystallization_process();
    void Is_cells_cristallization();
    void Set_cells_dis_rate_prob();
    void Set_cells_crys_rate_prob();
    void Set_cells_dis_crys_rate_prob();
};


#endif //FIRST_ATTEMPT_MAP_H
