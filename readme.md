# Modeling of Dendritic Crystal Growth (crys_prob)

A project for simulating the growth processes of dendritic crystal structures based on the initial parameters of the system.

## Project Description

The program simulates the crystallization process of biological fluids (e.g., tears, saliva) during evaporation. The method is based on the comparison of reference and experimental structures, which has potential applications in medical diagnostics and forensics.

### Physical and Mathematical Model:
1.  **Diffusion:** Described by Partial Differential Equations (PDEs). A finite difference scheme is used for the numerical solution.
2.  **Probabilistic Nature:** Crystallization and dissolution probabilities are calculated for each elementary volume (cell) based on the local concentration of the substance.
3.  **Mass Conservation:** When a cell transitions into a crystalline state, it "draws" the required amount of substance from neighboring layers of the solution.

## Key Features
*   **Real-time Visualization:** Dendritic growth is visualized using the **SFML** library.
*   **Multithreading:** Computational parallelization is implemented (supporting 2, 4, or all available cores) to accelerate the calculation of diffusion processes.
*   **Adjustable Parameters:** Fine-tune physical constants such as the diffusion coefficient, equilibrium concentration, growth rate, and more.

## Tech Stack
*   **Language:** C++ (C++20 standard)
*   *Graphics:** SFML 2.5.x
*   **Build System:** CMake

## Build and Run

### Dependencies
Ensure that the SFML library is installed on your system. The paths for Windows are specified in `CMakeLists.txt` (currently `D:/informatika/SFML`); you must update these to match your local library location.

### Instructions
1. Clone the repository:
   ```bash
   git clone https://github.com/Esaak/crystallization_proccess.git
   cd crystallization_proccess
   ```
2. Configure the SFML paths in `CMakeLists.txt`.
3. Build the project:
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```
4. Run the executable.

## Configuration
Key physical constants are located in `main.cpp`. You can modify them to achieve different types of structures:

*   `diffusion_coef` — Diffusion coefficient (affects the "branchiness" of the structure).
*   `equilibrium_concentration` — Equilibrium concentration point.
*   `basic_rate` — Basic growth/dissolution rate.
*   `max_density` — Density of the crystallized substance.

## Code Structure
*   `Cells.h/cpp` — Logic for an individual cell: concentration storage, probability calculation.
*   `Map.h/cpp` — Cell grid implementation, diffusion algorithm, and multithreading logic.
*   `Map_Draw.h/cpp` — Main rendering loop and iteration management.
*   `Cells_Draw.h/cpp` — Visual representation of a cell (color depends on concentration or state).

## Results
The model clearly demonstrates the formation of fractal (dendritic) structures. Experiments revealed that under certain boundary conditions, the substance may "flow" toward the center due to the specifics of the approximate solution to the diffusion equations.

## 👥 Authors
*   Mikhail Derevyanchenko
*   Ilya Gerasimov

---
*MIPT (National Research University), Dolgoprudny, 2022*
