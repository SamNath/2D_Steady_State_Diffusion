# Laplace Equation Numerical Solver 
This tool numerically solves the Laplace equation for 2D steady-state thermal diffusion. The Laplace equation is given by $$\frac{\partial^2 T}{\partial x^2} + \frac{\partial^2 T}{\partial y^2} =0 $$ 

The equation is numerically solved by implementing the central finite difference scheme on a discretized 2D domain, subjected to a given set of Dirchlet boundary conditions. 
The following diagram shows a schematic of the discretized domain, the co-ordinate system followed and boundary conditions applied. 
![Project Screenshot](image_2d_updated.png)

## Features
* The solver discretizes a 2D spatial domain, applies boundary conditions and solves the differential equation using the finite central difference numerical solution scheme.
* Inputs: the number of grids the domain is to be divided into and the four boundary conditions representing temperatures at the top, bottom, left and right walls, as shown in the above figure.
* Calculation is performed by C++ for speed. Data is visualized using a Python script that reads data from a csv file output by the C++ program and displays a contour plot.
* The batch file script named "auto_script.bat" can automate the implementation of the solver and the data-visualization script

## Assumptions 
* Steady-state heat diffusion
* No internal heat source or heat sink
* Boundary walls are maintained at a constant temperature
* The grid is uniform ($\Delta X = \Delta Y$)

## Running the tool 
* Step 1:
Before running the automation batch script, ensure that the C++ code is compiled in case you decide to make any changes to the code. If the main C++ solver code was not modified, proceed to step 2.   

`g++ 2D_Compute.cpp -o test_code.exe`
* Step 2: 
Double ouble-click the auto_script.bat file. You will be prompted to enter the number of divisions to divide the spatial domain into and the wall boudnary conditions to be applied. After computations are completed, the python script will be automatically executed, generating a contour plot.

