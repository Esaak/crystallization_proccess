//
// Created by п on 24.03.2022.
//

#include "Map.h"
#include <iomanip>
//default constructor
Map::Map() : Height(600), Width(800), number_of_Cells(1000) {
    cell.resize(1000);
}

//constructor
Map::Map(unsigned int H, unsigned int W, unsigned int N) : Height(H), Width(W), number_of_Cells(N) {
    cell.resize(N);
}

//copy constructor
Map::Map(const Map &map) : Height(map.Height), Width(map.Width), number_of_Cells(map.number_of_Cells) {
    cell.resize(map.number_of_Cells);
    for (int i = 0; i < map.number_of_Cells; i++) cell[i] = map.cell[i];
    //надо бы еще значения из вектора скопировать, но мне лень - готово
}

//operataor overload - присваивание одному мапу, другой
Map &Map::operator=(const Map &map) {
    if (this == &map) {
        return *this;
    }
    Height = map.Height;
    Width = map.Width;
    number_of_Cells = map.number_of_Cells;
    cell.resize(map.number_of_Cells);
    for (int i = 0; i < map.number_of_Cells; i++) cell[i] = map.cell[i];
    //надо бы еще значения скопировать, но мне лень - готово
    return *this;
}



void Map::Set_cell_origin() {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    //tot_solution = 0.0;
    std::random_device rd;
    std::mt19937 gen(seed);
    std::uniform_real_distribution<double> distrib(0, 1);
    for (unsigned i = 0; i < Height; i += 2) {
        for (unsigned j = 0; j < Width; j += 2) {
            if (i / 2 * Width / 2 + j / 2 < number_of_Cells) {
                Set_cell_coordinates(i / 2 * Width / 2 + j / 2, j, i);
                double rand_temp =  distrib(gen);
                cell[i / 2 * Width / 2 + j / 2].Set_solution(max_density *rand_temp);
                cell[i / 2 * Width / 2 + j / 2].Set_impurity(max_density - cell[i].Get_solution());
                cell[i / 2 * Width / 2 + j / 2].Set_next_step_solution(max_density *rand_temp);
                state = false;
            }
        }
    }
}

/*
void Map::Differential_equation_iteration1() {
    double total_solution = 0.0;
    //double total_impurity = 0.0;
    double x = 0, y = 0;
    for (int i = 0; i < number_of_Cells; i++) {
        total_solution = Get_cell_solution(i) * (1 - 4 * diffusion_coef * dt / (dx * dx));
        //total_impurity = Get_cell_impurity(i) * (1 - 4 * diffusion_coef) * dt / (dx * dx);
        x = Get_cell_coordinates(i).first;
        y = Get_cell_coordinates(i).second;
        if (x - 2 >= 0) {
            total_solution += Get_cell_solution(i - 1) * diffusion_coef * dt / (dx * dx);
            //total_impurity += Get_cell_impurity(i - 1) * diffusion_coef * dt / (dx * dx);
            //std::cout<< "L";
        }
        if (x + 2 <= Width - 2) {
            total_solution += Get_cell_solution(i + 1) * diffusion_coef * dt / (dx * dx);
            //total_impurity += Get_cell_impurity(i + 1) * diffusion_coef * dt / (dx * dx);
            //std::cout<< "R";
        }
        if (y - 2 >= 0) {
            total_solution += Get_cell_solution(i - Width / 2) * diffusion_coef * dt / (dx * dx);
            //total_impurity += Get_cell_impurity(i - Width / 2) * diffusion_coef * dt / (dx * dx);
        }
        if (y + 2 <= Height - 2) {
            total_solution += Get_cell_solution(i + Width / 2) * diffusion_coef * dt / (dx * dx);
            //total_impurity += Get_cell_impurity(i + Width / 2) * diffusion_coef * dt / (dx * dx);
        }
        Set_cell_solution(i, total_solution);
        //Set_impurity(total_impurity);
    }
    double tot_solution = 0.0;
    for(int i = 0; i < number_of_Cells; i ++)
    {
        std::cout << cell[i].Get_solution() << " ";
        //tot_solution += cell[i].Get_solution();
    }
    std::cout << "\n";
}*/

//Тут чуть подправил, идея в чем:
//Завели новую поле со значением следущего шага
//И присваиваем значение для следущего шага
void Map::Differential_equation_iteration2() {
    double total_solution = 0.0;
    std::pair<double, double> coordinates_temp;
    for (int i = 0; i < number_of_Cells; i++) {
        total_solution = 0.0;
        Set_cell_solution(i, Get_cell_next_step_solution(i));
        total_solution = Get_cell_next_step_solution(i)* (1 - 4 * diffusion_coef * dt / (dx * dx));
        coordinates_temp.first = Get_cell_coordinates(i).first;
        coordinates_temp.second = Get_cell_coordinates(i).second;
        if (coordinates_temp.first - 2 >= 0) {
            total_solution += Get_cell_solution(i - 1) * diffusion_coef * dt / (dx * dx);
        }
        if (coordinates_temp.first + 2 <= Width - 2) {
            total_solution += Get_cell_next_step_solution(i + 1) * diffusion_coef * dt / (dx * dx);
        }
        if (coordinates_temp.second - 2 >= 0) {
            total_solution += Get_cell_solution(i - Width / 2) * diffusion_coef * dt / (dx * dx);
        }
        if (coordinates_temp.second + 2 <= Height - 2) {
            total_solution += Get_cell_next_step_solution(i + Width / 2) * diffusion_coef * dt / (dx * dx);
        }
        Set_cell_next_step_solution(i, total_solution);
    }
}
/*
void Map::Crystallization_dissolution_check() {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);

    std::random_device rd;
    std::mt19937 gen(seed);
    std::uniform_real_distribution<double> distrib(0, 1);

    for (int i = 0; i < number_of_Cells; i++) {
        cell[i].Set_crys_rate_prob();
        cell[i].Set_dis_rate_prob();
        Is_cells_cristallization(i);
        double prob = distrib(gen);
        if (prob <= dis_prob) state = false;
        if (prob > dis_prob && prob <= dis_prob + crys_prob) {
            state = true;
            // тут можно процесс кристализации вынести в отдельную функцию, но мне лень
            double total_solution = 0; // итоговая концентрация, которую собираем с соседних ячеек
            int j = 1; // номер группы ячеек, в цикле они возрастают
            while (total_solution < cell[i].Get_impurity()) {

            }

        }
    }
};*/
void Map:: Set_cells_dis_rate_prob(){
    for(auto & it: cell){
        it.Set_dis_rate_prob();
    }
}
void Map::Set_cells_crys_rate_prob() {
    for(auto &it: cell){
        it.Set_crys_rate_prob();
    }
}
void Map:: Is_cells_cristallization(){
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std:: default_random_engine e(seed);
    for(std::size_t i=0; i<number_of_Cells; i++){
        std::uniform_real_distribution<double> distrib(0, Get_cell_i(i).Get_crys_rate()+Get_cell_i(i).Get_dis_rate());
        distrib(e)>dis_rate ? Get_cell_i(i).Set_state(true)  : Get_cell_i(i).Set_state(false);
    }
}
void Map::Crystallization_process() {
    Differential_equation_iteration2();
    Set_cells_crys_rate_prob();
    Set_cells_dis_rate_prob();
    Is_cells_cristallization();
    for(int i=0; i<Height; i+=2){
        for(int j=0; j<Width; j+=2){
            if(cell[j/2 + Width/2* i/2].Get_state()){
                double delta =max_density -  cell[i/2 + Width/2* j/2].Get_solution();
                double temp_summ=0;
                int r=1;
                std::vector<Cells*>answ;
                while(delta>0){
                    temp_summ=0;
                    for(int iter =0; iter<r; iter++){
                        int i1 = (i/2 - r + iter)*static_cast<int>(Width) /2;
                        int j1 = j/2 + iter;
                        if(j1<0 || i1<0) continue;
                        if(!cell[i1+j1].Get_state()) {
                            temp_summ += cell[i1 + j1].Get_solution();
                            answ.push_back(&cell[i1 + j1]);
                        }
                    }
                    for(int iter =0; iter<r; iter++){
                        int i1 = (i/2  + iter)*static_cast<int>(Width) /2;
                        int j1 = j/2 + r - iter;
                        if(j1<0 || i1<0) continue;
                        if(!cell[i1+j1].Get_state()) {
                            temp_summ += cell[i1 + j1].Get_solution();
                            answ.push_back(&cell[i1 + j1]);
                        }
                    }
                    for(int iter =0; iter<r; iter++){
                        int i1 = (i/2 + r - iter)*static_cast<int>(Width) /2;
                        int j1 = j/2 - iter;
                        if(j1<0 || i1<0) continue;
                        if(!cell[i1+j1].Get_state()) {
                            temp_summ += cell[i1 + j1].Get_solution();
                            answ.push_back(&cell[i1 + j1]);
                        }
                    }
                    for(int iter =0; iter<r; iter++){
                        int i1 = (i/2 - iter)*static_cast<int>(Width) /2;
                        int j1 = j/2 - r + iter;
                        if(j1<0 || i1<0) continue;
                        if(!cell[i1+j1].Get_state()) {
                            temp_summ += cell[i1 + j1].Get_solution();
                            answ.push_back(&cell[i1 + j1]);
                        }
                    }
                    for(int i1 =Width/2* i/2 -r*Width/2;i1< Width/2* i/2 -Width/2; i1+=Width/2){
                        for(int j1 = j/2; i1+j1-i/2 - j/2==r; j1++){
                            if(j1<0 || i1<0) continue;
                            if(!cell[i1+j1].Get_state()) {
                                temp_summ += cell[i1 + j1].Get_solution();
                                answ.push_back(&cell[i1 + j1]);
                            }
                        }
                    }
                    for(int i1 = Width/2 * i/2; i1<Width/2 * (i/2+r); i1+=Width/2){
                        for(int j1 = j/2+r; i1+j1-i/2 - j/2==r; j1--){
                            if(j1<0 || i1<0) continue;
                            if(!cell[i1+j1].Get_state()) {
                                temp_summ += cell[i1 + j1].Get_solution();
                                answ.push_back(&cell[i1 + j1]);
                            }
                        }
                    }
                    for(int i1= Width/2 + r*Width/2; i1>Width/2 * i/2; i1-=Width/2){
                        for(int j1 = j/2; i1+j1-i/2-j/2==r; j1--){
                            if(j1<0 || i1<0) continue;
                            if(!cell[i1+j1].Get_state()) {
                                temp_summ += cell[i1 + j1].Get_solution();
                                answ.push_back(&cell[i1+j1]);
                            }
                        }
                    }
                    for(int i1= Width/2 * i/2; i1>Width/2* i/2-Width/2*r; i1-=Width/2){
                        for(int j1 = j/2 -r;j1+i1-i/2-j/2==r; j1++){
                            if(j1<0 || i1<0) continue;
                            if(!cell[i1+j1].Get_state()){
                                temp_summ+=cell[i1+j1].Get_solution();
                                answ.push_back(&cell[i1+j1]);
                            }
                        }
                    }
                    if(temp_summ>=delta){
                        for(auto& it: answ){
                            it->Set_solution(it->Get_solution()-it->Get_solution()*delta/temp_summ);
                        }
                        delta=0;
                        continue;
                    }
                    if(temp_summ<delta){
                        for(auto& it:answ){
                            it->Set_solution(0);
                        }
                        delta-=temp_summ;
                    }
                    r++;
                }
            }
        }
    }

}
