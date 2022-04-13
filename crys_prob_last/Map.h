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
    std::vector<Cells*>cells_cristall;
public:
    Map();

    Map(unsigned, unsigned, unsigned);

    Map(const Map &);

    Map &operator=(const Map &map);

    ~Map() = default;

    unsigned Get_Height() const { return Height; };

    unsigned Get_Width() const { return Width; };

    void Set_cell_coordinates(unsigned i, unsigned j) {
        cell[i][j].Set_coordinates(i * 2, j * 2);
    };

    void Set_cell_impurity(unsigned i, unsigned j, double impurity) {
        cell[i][j].Set_impurity(impurity);
    }

    void Set_cell_solution(unsigned i, unsigned j, double solution) {
        cell[i][j].Set_solution(solution);
        //cell[i].Set_impurity(max_density - solution);
    }
    void Set_cell_next_step_solution(unsigned i, unsigned j, double next_step_solution){
        cell[i][j].Set_next_step_solution(next_step_solution);
    }
    double Get_cell_next_step_solution(unsigned i, unsigned j){
        return cell[i][j].Get_next_step_solution();
    }
    std::pair<double, double> Get_cell_coordinates(unsigned i, unsigned j) const {
        return cell[i][j].Get_coordinates();
    }

    double Get_cell_impurity(unsigned i, unsigned j) const {
        return cell[i][j].Get_impurity();
    }

    double Get_cell_solution(unsigned i, unsigned j) const {
        return cell[i][j].Get_solution();
    }

    Cells &Get_cell_i(unsigned i, unsigned j) {
        return cell[i][j];
    }

    Cells Get_cell_i(unsigned i, unsigned j) const {
        return cell[i][j];
    }

    unsigned Get_number_of_Cells() {
        return number_of_Cells;
    }

    void Set_cell_origin();

    void Set_cell_coordinates_iterative();

//    void Set_max_density(int i, double max_density) {
//        cell[i].Set_max_density = max_density;
//    }


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
    void Differential_equation_iteration3();
    void Crystallization_dissolution_check();
    void Crystallization_dissolution_check1();
    void Crystallization_dissolution_check3();
    void Crystallization_process(int, int);
};


#endif //FIRST_ATTEMPT_MAP_H
