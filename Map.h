//This class is responsible for the map, and all the methods, which are applied to cells
#ifndef FIRST_ATTEMPT_MAP_H
#define FIRST_ATTEMPT_MAP_H

#include "Cells.h"

class Map : public Cells {
protected:
    unsigned Height;
    unsigned Width;
    unsigned number_of_Cells;
    std::vector<std::vector<Cells>> cell;
    std::vector<Cells *> cells_crystall;
    std::vector<std::thread *> cells_thread_even;
    std::vector<std::thread *> cells_thread_uneven;
public:
    Map();

    Map(unsigned, unsigned, unsigned);

    Map(const Map &);

    Map &operator=(const Map &map);

    ~Map() = default;

    unsigned Get_Height() const;

    unsigned Get_Width() const;

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

    void Thread_Differential_equation_iteration_4();

    void Thread_Differential_equation_iteration_all();

    void Thread_pass_even(std::size_t);

    void Thread_pass_even1(std::size_t);

    void Thread_pass_uneven(std::size_t);

    void Thread_pass_uneven1(std::size_t);

    static double Get_max_density(double max_density) {
        return max_density;
    }

    static double Get_equilibrium_concentration(double equilibrium_concentration) {
        return equilibrium_concentration;
    }

    static double Get_basic_rate(double basic_rate) {
        return basic_rate;
    }

    static double Get_diffusion_coef(double diffusion_coef) {
        return diffusion_coef;
    }

    void Set_cell_origin();

    void Thread_Differential_equation_iteration_2();

    void Differential_equation_iteration2();

    void Crystallization_dissolution_check();

    void Crystallization_process(int, int);

    void Rhombus(int);

    void Rhombus_clean(int);
};


#endif //FIRST_ATTEMPT_MAP_H
