//
// Created by п on 24.03.2022.
//

#include "Map.h"
#include <iomanip>
/*########################################################################################*/
/*#################################Constuctors and operators##############################*/
/*########################################################################################*/
//default constructor
Map::Map() : Height(600), Width(800), number_of_Cells(1000) {
    cell.resize(Height / cells_distance);
    for (auto &it: cell) {
        it.resize(Width / cells_distance);
    }
}

//constructor
Map::Map(unsigned int H, unsigned int W, unsigned int N) : Height(H), Width(W), number_of_Cells(N) {
    cell.resize(Height / cells_distance);
    for (auto &it: cell) {
        it.resize(Width / cells_distance);
    }
}

//copy constructor
Map::Map(const Map &map) : Height(map.Height), Width(map.Width), number_of_Cells(map.number_of_Cells) {
    cell.resize(map.Height / map.cells_distance);
    for (auto &it: cell) {
        it.resize(map.Width / map.cells_distance);
    }
    for (int i = 0; i < map.Height / map.cells_distance; i++) {
        for (int j = 0; j < map.Width / map.cells_distance; j++)
            cell[i][j] = map.cell[i][j];
    }
}

//operator = overload
Map &Map::operator=(const Map &map) {
    if (this == &map) {
        return *this;
    }
    Height = map.Height;
    Width = map.Width;
    number_of_Cells = map.number_of_Cells;
    cell.resize(map.Height);
    for (auto &it: cell) {
        it.resize(map.Width);
    }
    for (int i = 0; i < map.Height / map.cells_distance; i++) {
        for (int j = 0; j < map.Width / map.cells_distance; j++) cell[i][j] = map.cell[i][j];
    }
    return *this;
}

/*########################################################################################*/
/*#################################Getters and Setters####################################*/
/*########################################################################################*/

unsigned Map::Get_Height() const {
    return Height;
};

unsigned Map::Get_Width() const {
    return Width;
};

void Map::Set_cell_coordinates(unsigned i, unsigned j) {
    cell[i][j].Set_coordinates(i * cells_distance, j * cells_distance);
};

void Map::Set_cell_impurity(unsigned i, unsigned j, double impurity) {
    cell[i][j].Set_impurity(impurity);
}

void Map::Set_cell_solution(unsigned i, unsigned j, double solution) {
    cell[i][j].Set_solution(solution);
    cell[i][j].Set_impurity(max_density - solution);
}

void Map::Set_cell_next_step_solution(unsigned i, unsigned j, double next_step_solution) {
    cell[i][j].Set_next_step_solution(next_step_solution);
}

double Map::Get_cell_next_step_solution(unsigned i, unsigned j) {
    return cell[i][j].Get_next_step_solution();
}

std::pair<double, double> Map::Get_cell_coordinates(unsigned i, unsigned j) const {
    return cell[i][j].Get_coordinates();
}

double Map::Get_cell_impurity(unsigned i, unsigned j) const {
    return cell[i][j].Get_impurity();
}

double Map::Get_cell_solution(unsigned i, unsigned j) const {
    return cell[i][j].Get_solution();
}

Cells &Map::Get_cell_i(unsigned i, unsigned j) {
    return cell[i][j];
}

Cells Map::Get_cell_i(unsigned i, unsigned j) const {
    return cell[i][j];
}

unsigned Map::Get_number_of_Cells() {
    return number_of_Cells;
}

/*########################################################################################*/
/*########################################Math############################################*/
/*########################################################################################*/

// setting initial values
void Map::Set_cell_origin() {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    std::random_device rd;
    std::mt19937 gen(seed);
    std::normal_distribution<double> distrib{Solution_concentration * max_density, sqrt(Solution_concentration * max_density)};
    for (unsigned i = 0; i < Height / cells_distance; i++) {
        for (unsigned j = 0; j < Width / cells_distance; j++) {
            cell[i][j].Set_coordinates(i, j);
            double rand_temp = distrib(gen);
            if (rand_temp < 0) rand_temp = 0;
            if (rand_temp > 2 * Solution_concentration * max_density) rand_temp = 2 * Solution_concentration * max_density;
            if (i == 0 || i == Height / cells_distance - 1 || j == 0 || j == Width / cells_distance - 1)
                rand_temp = 0;
            cell[i][j].Set_solution(rand_temp);
            cell[i][j].Set_next_step_solution(rand_temp);
            cell[i][j].Set_state(false);
            cell[i][j].Set_state_color(false);
            cell[i][j].Set_blue_color(false);
        }
    }
    cells_thread_even.reserve(Width / 2);
    cells_thread_uneven.reserve(Width / 2);
    cell[Height / (2 * cells_distance)][Width / (2 * cells_distance)].Set_state(true);
    cell[Height / (2 * cells_distance)][Width / (2 * cells_distance)].Set_state_color(true);
    cells_crystall.push_back(&cell[Height / (2 * cells_distance)][Width / (2 * cells_distance)]);
    cell[Height / (2 * cells_distance)][Width / (2 * cells_distance)].Set_solution(max_density);
    cell[Height / (2 * cells_distance)][Width / (2 * cells_distance)].Set_next_step_solution(max_density);
}




void Map::Thread_pass_uneven(std::size_t j) {
    j=j/cells_distance- j%cells_distance;
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    double total_solution = 0.0;
    for (std::size_t i = 1; i < Height / cells_distance - 1; i++) {
        if (!cell[i][j].Get_state_color()) {
            std::uniform_real_distribution<double> distrib(0, 1);
            cell[i][j].Set_crys_dis_rate_prob();
            double prob = distrib(gen);
            if (prob < cell[i][j].Get_dis_prob()) cell[i][j].Set_state(false);
            if (prob >= cell[i][j].Get_dis_prob() &&
                prob <= cell[i][j].Get_dis_prob() + cell[i][j].Get_dis_prob()) {
                cell[i][j].Set_state(true);
            }

            Set_cell_solution(i, j, Get_cell_next_step_solution(i, j));
            total_solution = Get_cell_solution(i, j) * (1 - 4 * diffusion_coef * dt / (dx * dx));
            total_solution += cell[i - 1][j].Get_state_color() ? 0 : Get_cell_solution(i - 1, j) *
                                                                     diffusion_coef *
                                                                     dt /
                                                                     (dx * dx);
            total_solution += cell[i + 1][j].Get_state_color() ? 0 : Get_cell_solution(i + 1, j) *
                                                                     diffusion_coef * dt / (dx * dx);
            total_solution += cell[i][j - 1].Get_state_color() ? 0 : Get_cell_solution(i, j - 1) *
                                                                     diffusion_coef *
                                                                     dt /
                                                                     (dx * dx);
            total_solution += cell[i][j + 1].Get_state_color() ? 0 : Get_cell_solution(i, j + 1) *
                                                                     diffusion_coef * dt / (dx * dx);
            Set_cell_next_step_solution(i, j, total_solution);
        }
    }
}


//solution of differential equation
void Map::Thread_pass_even(std::size_t j){
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    double total_solution =0;
    std::size_t p=0;
    if(j==1){
        p=248/cells_distance;
    }
    else{
        p=249/cells_distance+249%cells_distance;
    }
    for(std::size_t m=1; m<Height/cells_distance-1; m++) {
        for (std::size_t n = j; n < (j + p); n++) {
            if (!cell[m][n].Get_state_color()) {
                std::uniform_real_distribution<double> distrib(0, 1);

                cell[m][n].Set_crys_dis_rate_prob();
                //std::cout<<cell[i][j].Get_crys_prob()<<"\n";
                double prob = distrib(gen);
                if (prob < cell[m][n].Get_dis_prob()) cell[m][n].Set_state(false);
                if (prob >= cell[m][n].Get_dis_prob() &&
                    prob <= cell[m][n].Get_dis_prob() + cell[m][n].Get_dis_prob()) {
                    cell[m][n].Set_state(true);
                }


                Set_cell_solution(m, n, Get_cell_next_step_solution(m, n));
                total_solution = Get_cell_solution(m, n) * (1 - 4 * diffusion_coef * dt / (dx * dx));
                total_solution += cell[m - 1][n].Get_state_color() ? 0 : Get_cell_solution(m - 1, n) *
                                                                         diffusion_coef *
                                                                         dt /
                                                                         (dx * dx);
                total_solution += cell[m + 1][n].Get_state_color() ? 0 : Get_cell_next_step_solution(m + 1, n) *
                                                                         diffusion_coef * dt / (dx * dx);
                total_solution += cell[m][n - 1].Get_state_color() ? 0 :n==j? Get_cell_next_step_solution(m,n-1)*diffusion_coef *
                                                                                                                dt /
                                                                                                                (dx * dx):Get_cell_solution(m, n - 1) *
                                                                         diffusion_coef *
                                                                         dt /
                                                                         (dx * dx);
                total_solution += cell[m][n + 1].Get_state_color() ? 0 : Get_cell_next_step_solution(m, n + 1) *
                                                                         diffusion_coef * dt / (dx * dx);
                Set_cell_next_step_solution(m, n, total_solution);
            }
        }
    }
}
void Map::Thread_Differential_equation_iteration() {
    std::thread th1(&Map::Thread_pass_even, this, 1);
    std::thread th2(&Map::Thread_pass_even, this, 250/cells_distance);
    std::thread th3(&Map::Thread_pass_even, this, 500/cells_distance);
    std::thread th4(&Map::Thread_pass_even, this, 750/cells_distance);
    th1.join();
    th2.join();
    th3.join();
    th4.join();
    std::thread th5(&Map::Thread_pass_uneven, this,249);
    std::thread th6(&Map::Thread_pass_uneven, this, 499);
    std::thread th7 (&Map::Thread_pass_uneven, this, 749);
    th5.join();
    th6.join();
    th7.join();
}



void Map::Thread_pass_even1(std::size_t j) {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    double total_solution = 0.0;
    for (std::size_t i = 1; i < Height / cells_distance - 1; i++) {
        if (!cell[i][j].Get_state_color()) {
            std::uniform_real_distribution<double> distrib(0, 1);

            cell[i][j].Set_crys_dis_rate_prob();
            //std::cout<<cell[i][j].Get_crys_prob()<<"\n";
            double prob = distrib(gen);
            if (prob < cell[i][j].Get_dis_prob()) cell[i][j].Set_state(false);
            if (prob >= cell[i][j].Get_dis_prob() &&
                prob <= cell[i][j].Get_dis_prob() + cell[i][j].Get_dis_prob()) {
                cell[i][j].Set_state(true);
            }

            Set_cell_solution(i, j, Get_cell_next_step_solution(i, j));
            total_solution = Get_cell_solution(i, j) * (1 - 4 * diffusion_coef * dt / (dx * dx));
            total_solution += cell[i - 1][j].Get_state_color() ? 0 : Get_cell_next_step_solution(i - 1, j) *
                                                                     diffusion_coef *
                                                                     dt /
                                                                     (dx * dx);
            total_solution += cell[i + 1][j].Get_state_color() ? 0 : Get_cell_next_step_solution(i + 1, j) *
                                                                     diffusion_coef * dt / (dx * dx);
            total_solution += cell[i][j - 1].Get_state_color() ? 0 : Get_cell_next_step_solution(i, j - 1) *
                                                                     diffusion_coef *
                                                                     dt /
                                                                     (dx * dx);
            total_solution += cell[i][j + 1].Get_state_color() ? 0 : Get_cell_next_step_solution(i, j + 1) *
                                                                     diffusion_coef * dt / (dx * dx);
            Set_cell_next_step_solution(i, j, total_solution);
        }
    }
}

void Map::Thread_pass_uneven1(std::size_t j) {
    j = (j-1)*cells_distance;
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    double total_solution = 0.0;
    for (std::size_t i = 1; i < Height / cells_distance - 1; i++) {
        if (!cell[i][j].Get_state_color()) {
            std::uniform_real_distribution<double> distrib(0, 1);

            cell[i][j].Set_crys_dis_rate_prob();
            //std::cout<<cell[i][j].Get_crys_prob()<<"\n";
            double prob = distrib(gen);
            if (prob < cell[i][j].Get_dis_prob()) cell[i][j].Set_state(false);
            if (prob >= cell[i][j].Get_dis_prob() &&
                prob <= cell[i][j].Get_dis_prob() + cell[i][j].Get_dis_prob()) {
                cell[i][j].Set_state(true);
            }

            Set_cell_solution(i, j, Get_cell_next_step_solution(i, j));
            total_solution = Get_cell_solution(i, j) * (1 - 4 * diffusion_coef * dt / (dx * dx));
            total_solution += cell[i - 1][j].Get_state_color() ? 0 : Get_cell_solution(i - 1, j) *
                                                                     diffusion_coef *
                                                                     dt /
                                                                     (dx * dx);
            total_solution += cell[i + 1][j].Get_state_color() ? 0 : Get_cell_solution(i + 1, j) *
                                                                     diffusion_coef * dt / (dx * dx);
            total_solution += cell[i][j - 1].Get_state_color() ? 0 : Get_cell_solution(i, j - 1) *
                                                                     diffusion_coef *
                                                                     dt /
                                                                     (dx * dx);
            total_solution += cell[i][j + 1].Get_state_color() ? 0 : Get_cell_solution(i, j + 1) *
                                                                     diffusion_coef * dt / (dx * dx);
            Set_cell_next_step_solution(i, j, total_solution);
        }
    }
}

void Map::Thread_Differential_equation_iteration1() {
    for (int j = 2; j < Width/cells_distance; j += 2) {
//        std::cout<<j<<" ";
        auto b_tedt = new std::thread(&Map::Thread_pass_even1, this, j);
        cells_thread_even[j/2-1] = b_tedt;
    }
//    std::cout<<"\n";
    for (auto &it:cells_thread_even) {
        it->join();
        delete it;
    }
    for(int j=1;j<Width/cells_distance-1; j+=2){
        //std::cout<<j<<" ";
        auto b_tedt = new std::thread(&Map::Thread_pass_uneven1, this, j);
        cells_thread_uneven[j/2+1]= b_tedt;
    }
    for(auto& it:cells_thread_uneven){
        it->join();
        delete it;
    }
}



void Map::Differential_equation_iteration() {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    double summ = 0;

    summ = 0;

    std::thread th1([&]() {
        std::pair<double, double> coordinates_temp;
        double total_solution = 0.0;
        for (int i = 1; i < Height / cells_distance - 1; i++) {
            //std::cout << 1;
            for (int j = 1; j < Width / (2 * cells_distance) - 1; j++) {
                if (!cell[i][j].Get_state_color()) {
                    std::uniform_real_distribution<double> distrib(0, 1);

                    cell[i][j].Set_crys_dis_rate_prob();
                    double prob = distrib(gen);
                    if (prob < cell[i][j].Get_dis_prob()) cell[i][j].Set_state(false);
                    if (prob >= cell[i][j].Get_dis_prob() &&
                        prob <= cell[i][j].Get_dis_prob() + cell[i][j].Get_dis_prob()) {
                        cell[i][j].Set_state(true);
                    }


                    total_solution = 0.0;
                    coordinates_temp.first = i;
                    coordinates_temp.second = j;
                    Set_cell_solution(i, j, Get_cell_next_step_solution(i, j));
                    total_solution = Get_cell_solution(i, j) * (1 - 4 * diffusion_coef * dt / (dx * dx));
                    // block with if in the absence of boundary conditions
                    /*if (i - 1 >= 0) {
                        total_solution += Get_cell_solution(i - 1, j) * diffusion_coef * dt / (dx * dx);
                    }
                    if (i + 1 < Height / 2) {
                        total_solution += Get_cell_solution(i + 1, j) * diffusion_coef * dt / (dx * dx);
                    }

                    if (j - 1 >= 0) {
                        total_solution += Get_cell_solution(i, j - 1) * diffusion_coef * dt / (dx * dx);
                    }
                    if (j + 1 < Width / 2) {
                        total_solution += Get_cell_solution(i, j + 1) * diffusion_coef * dt / (dx * dx);
                    }*/
                    total_solution += cell[i - 1][j].Get_state_color() ? 0 : Get_cell_solution(i - 1, j) *
                                                                             diffusion_coef *
                                                                             dt /
                                                                             (dx * dx);
                    total_solution += cell[i + 1][j].Get_state_color() ? 0 : Get_cell_next_step_solution(i + 1, j) *
                                                                             diffusion_coef * dt / (dx * dx);
                    total_solution += cell[i][j - 1].Get_state_color() ? 0 : Get_cell_solution(i, j - 1) *
                                                                             diffusion_coef *
                                                                             dt /
                                                                             (dx * dx);
                    total_solution += cell[i][j + 1].Get_state_color() ? 0 : Get_cell_next_step_solution(i, j + 1) *
                                                                             diffusion_coef * dt / (dx * dx);
                    Set_cell_next_step_solution(i, j, total_solution);
                }
            }
        }

    });
    std::thread th2([&]() {
        std::pair<double, double> coordinates_temp;
        double total_solution = 0.0;
        for (int i = 1; i < Height / cells_distance - 1; i++) {
            for (int j = Width / (2 * cells_distance); j < Width / cells_distance - 1; j++) {
                if (!cell[i][j].Get_state_color()) {

                    std::uniform_real_distribution<double> distrib(0, 1);

                    cell[i][j].Set_crys_dis_rate_prob();
                    double prob = distrib(gen);
                    if (prob < cell[i][j].Get_dis_prob()) cell[i][j].Set_state(false);
                    if (prob >= cell[i][j].Get_dis_prob() &&
                        prob <= cell[i][j].Get_dis_prob() + cell[i][j].Get_dis_prob()) {
                        cell[i][j].Set_state(true);
                    }

                    total_solution = 0.0;
                    coordinates_temp.first = i;
                    coordinates_temp.second = j;
                    Set_cell_solution(i, j, Get_cell_next_step_solution(i, j));
                    total_solution = Get_cell_solution(i, j) * (1 - 4 * diffusion_coef * dt / (dx * dx));
                    // block with if in the absence of boundary conditions
                    /*if (i - 1 >= 0) {
                        total_solution += Get_cell_solution(i - 1, j) * diffusion_coef * dt / (dx * dx);
                    }
                    if (i + 1 < Height / 2) {
                        total_solution += Get_cell_solution(i + 1, j) * diffusion_coef * dt / (dx * dx);
                    }

                    if (j - 1 >= 0) {
                        total_solution += Get_cell_solution(i, j - 1) * diffusion_coef * dt / (dx * dx);
                    }
                    if (j + 1 < Width / 2) {
                        total_solution += Get_cell_solution(i, j + 1) * diffusion_coef * dt / (dx * dx);
                    }*/
                    total_solution += cell[i - 1][j].Get_state_color() ? 0 : Get_cell_solution(i - 1, j) *
                                                                             diffusion_coef *
                                                                             dt /
                                                                             (dx * dx);
                    total_solution += cell[i + 1][j].Get_state_color() ? 0 : Get_cell_next_step_solution(i + 1, j) *
                                                                             diffusion_coef * dt / (dx * dx);
                    total_solution += cell[i][j - 1].Get_state_color() ? 0 : j == Width / (2 * cells_distance) ?
                                                                             Get_cell_next_step_solution(i, j - 1) *
                                                                             diffusion_coef *
                                                                             dt /
                                                                             (dx * dx) : Get_cell_solution(i, j - 1) *
                                                                                         diffusion_coef *
                                                                                         dt /
                                                                                         (dx * dx);
                    total_solution += cell[i][j + 1].Get_state_color() ? 0 : Get_cell_next_step_solution(i, j + 1) *
                                                                             diffusion_coef * dt / (dx * dx);
                    Set_cell_next_step_solution(i, j, total_solution);
                }
            }
        }
    });
    th1.join();
    th2.join();
    double total_solution = 0;
    for (int m = 1; m < Height / cells_distance - 1; m++) {
        if (!cell[m][Width / (2 * cells_distance) - 1].Get_state_color()) {
            Set_cell_solution(m, Width / (2 * cells_distance) - 1,
                              Get_cell_next_step_solution(m, Width / (2 * cells_distance) - 1));

            total_solution =
                    Get_cell_solution(m, Width / (2 * cells_distance) - 1) * (1 - 4 * diffusion_coef * dt / (dx * dx));
            total_solution += cell[m - 1][Width / (2 * cells_distance) - 1].Get_state_color() ? 0 :
                              Get_cell_solution(m - 1, Width / (2 * cells_distance) - 1) * diffusion_coef *
                              dt /
                              (dx * dx);
            total_solution += cell[m + 1][Width / (2 * cells_distance) - 1].Get_state_color() ? 0 :
                              Get_cell_solution(m + 1, Width / (2 * cells_distance) - 1) *
                              diffusion_coef * dt / (dx * dx);

            total_solution += cell[m][Width / (2 * cells_distance) - 1 - 1].Get_state_color() ? 0 :
                              Get_cell_solution(m, Width / (2 * cells_distance) - 1 - 1) * diffusion_coef *
                              dt /
                              (dx * dx);
            total_solution += cell[m][Width / (2 * cells_distance) - 1 + 1].Get_state_color() ? 0 :
                              Get_cell_solution(m, Width / (2 * cells_distance) - 1 + 1) *
                              diffusion_coef * dt / (dx * dx);
            Set_cell_next_step_solution(m, Width / (2 * cells_distance) - 1, total_solution);
        }

    }
}

// process of crystallization and dissolution
void Map::Crystallization_process(int i, int j) {
    //pass circle radius, increases by one
    int k = 1;
    //the amount of substance needed for crystallization
    double needed_solution = max_density - cell[i][j].Get_next_step_solution();
    //the amount of substance in this circle
    double summary_group_solution;
    int x, y;
    //proportionality coefficient
    double ratio = 0.0;
    while (needed_solution > 0) {

        summary_group_solution = 0;
        //calculation the amount of substance in cells of  this circle
        if (j - k > 0) {
            if (!cell[i][j - k].Get_state() && !cell[i][j - k].Get_state_color()) {
                summary_group_solution += cell[i][j - k].Get_next_step_solution();
            }
        }
        if (j + k <= Width / 2 - 1) {
            if (!cell[i][j + k].Get_state() && !cell[i][j + k].Get_state_color()) {
                summary_group_solution += cell[i][j + k].Get_next_step_solution();
            }
        }
        for (y = j - k + 1; y < j + k; y++) {
            x = i + k - abs(j - y);
            if (x >= 0 && x < Height / cells_distance && y >= 0 && y < Width / cells_distance) {
                if (!cell[x][y].Get_state() && !cell[x][y].Get_state_color()) {
                    summary_group_solution += cell[x][y].Get_next_step_solution();
                }
            }
            x = i - k + abs(j - y);
            if (x >= 0 && x < Height / cells_distance && y >= 0 && y < Width / cells_distance) {
                if (!cell[x][y].Get_state() && !cell[x][y].Get_state_color()) {
                    summary_group_solution += cell[x][y].Get_next_step_solution();
                }
            }
        }
        // check if there is enough substance for crystallization
        if (summary_group_solution >= needed_solution) {
            ratio = needed_solution / summary_group_solution;
            cell[i][j].Set_next_step_solution(max_density);
            cell[i][j].Set_impurity(0.0);
        } else {
            ratio = 1;
            cell[i][j].Set_next_step_solution(cell[i][j].Get_next_step_solution() + summary_group_solution);
            cell[i][j].Set_impurity(max_density - cell[i][j].Get_next_step_solution());
        }
        // if there is enough substance in this circle, we subtract proportionally the amount,
        //else we subtract all the amount in this circle
        //the amount of substance in the cell
        double current_solution;
        if (j - k > 0) {
            if (!cell[i][j - k].Get_state() && !cell[i][j - k].Get_state_color()) {
                current_solution = cell[i][j - k].Get_next_step_solution();
                cell[i][j - k].Set_next_step_solution(current_solution * (1 - ratio));
            }
        }
        if (j + k <= Width / cells_distance - 1) {
            if (!cell[i][j + k].Get_state() && !cell[i][j + k].Get_state_color()) {
                current_solution = cell[i][j + k].Get_next_step_solution();
                cell[i][j + k].Set_next_step_solution(current_solution * (1 - ratio));
            }
        }
        for (y = j - k + 1; y < j + k; y++) {
            x = i + k - abs(j - y);
            if (x > 0 && x < Height / cells_distance && y > 0 && y < Width / cells_distance) {
                if (!cell[x][y].Get_state() && !cell[x][y].Get_state_color()) {
                    current_solution = cell[x][y].Get_next_step_solution();
                    cell[x][y].Set_next_step_solution(current_solution * (1 - ratio));
                }
            }
            x = i - k + abs(j - y);
            if (x > 0 && x < Height / cells_distance && y > 0 && y < Width / cells_distance) {
                if (!cell[x][y].Get_state() && !cell[x][y].Get_state_color()) {
                    current_solution = cell[x][y].Get_next_step_solution();
                    cell[x][y].Set_next_step_solution(current_solution * (1 - ratio));
                }
            }
        }


        needed_solution -= summary_group_solution;
        k++;
    }
}

//crystal one lab build
void Map::Crystallization_dissolution_check() {
    int x, y;
    //vector pointers on crystallized cells on this lab
    std::vector<Cells *> b;
    //check, are crystallized cells near cells, which crystallized in past lab
    for (auto &it: cells_crystall) {
        y = it->Get_coordinates().second / cells_distance - 1;
        x = it->Get_coordinates().first / cells_distance;
        if (x > 0 && x < Height / cells_distance && y > 0 && y < Width / cells_distance && cell[x][y].Get_state() &&
            !cell[x][y].Get_state_color()) {
            cell[x][y].Set_state_color(true);
            b.push_back(&cell[x][y]);
            Crystallization_process(x, y);
        }
        y = it->Get_coordinates().second / cells_distance + 1;
        x = it->Get_coordinates().first / cells_distance;
        if (x > 0 && x < Height / cells_distance && y > 0 && y < Width / cells_distance && cell[x][y].Get_state() &&
            !cell[x][y].Get_state_color()) {
            cell[x][y].Set_state_color(true);
            b.push_back(&cell[x][y]);
            Crystallization_process(x, y);
        }
        y = it->Get_coordinates().second / cells_distance;
        x = it->Get_coordinates().first / cells_distance + 1;
        if (x > 0 && x < Height / cells_distance && y > 0 && y < Width / cells_distance && cell[x][y].Get_state() &&
            !cell[x][y].Get_state_color()) {
            cell[x][y].Set_state_color(true);
            b.push_back(&cell[x][y]);
            Crystallization_process(x, y);
        }
        y = it->Get_coordinates().second / cells_distance;
        x = it->Get_coordinates().first / cells_distance - 1;
        if (x > 0 && x < Height / cells_distance && y > 0 && y < Width / cells_distance && cell[x][y].Get_state() &&
            !cell[x][y].Get_state_color()) {
            cell[x][y].Set_state_color(true);
            b.push_back(&cell[x][y]);
            Crystallization_process(x, y);
        }
    }
    //push a cells which crystallized in this lab in the vector pointer crystallization
    for (auto &q:b) {
        cells_crystall.push_back(q);
    }
    b.clear();
}

void Map::Rhompus(int count) {
    int i = Height / (2 * cells_distance);
    int j = Width / (2 * cells_distance);
    //int count=0;
    double delta_r = sqrt(4 * diffusion_coef * dt * count) / dx;
    //std::cout<<delta_r<<'\n';
    delta_r = round(delta_r);
    if (j - delta_r > 0) {
        cell[i][j - static_cast<int>(delta_r)].Set_blue_color(true);
    }
    if (j + delta_r < Width / cells_distance) {
        cell[i][j + static_cast<int>(delta_r)].Set_blue_color(true);
    }
    for (int y = j - static_cast<int>(delta_r) + 1; y < j + static_cast<int>(delta_r); y++) {
        int x = i + static_cast<int>(delta_r) - abs(j - y);
        if (x > 0 && x < Height / cells_distance && y > 0 && y < Width / cells_distance) {
            cell[x][y].Set_blue_color(true);
        }
        x = i - static_cast<int>(delta_r) + abs(j - y);
        if (x > 0 && x < Height / cells_distance && y > 0 && y < Width / cells_distance) {
            cell[x][y].Set_blue_color(true);
        }
    }
}

void Map::Rhompus_clean(int count) {
    int i = Height / pow(cells_distance, 2);
    int j = Width / pow(cells_distance, 2);
    double delta_r = sqrt(4 * diffusion_coef * dt * count) / dx;
    delta_r = round(delta_r);
    if (j - delta_r > 0) {
        cell[i][j - static_cast<int>(delta_r)].Set_blue_color(false);
    }
    if (j + delta_r < Width / cells_distance) {
        cell[i][j + static_cast<int>(delta_r)].Set_blue_color(false);
    }
    for (int y = j - static_cast<int>(delta_r) + 1; y < j + static_cast<int>(delta_r); y++) {
        int x = i + static_cast<int>(delta_r) - abs(j - y);
        if (x > 0 && x < Height / cells_distance && y > 0 && y < Width / cells_distance) {
            cell[x][y].Set_blue_color(false);
        }
        x = i - static_cast<int>(delta_r) + abs(j - y);
        if (x > 0 && x < Height / cells_distance && y > 0 && y < Width / cells_distance) {
            cell[x][y].Set_blue_color(false);
        }
    }
}