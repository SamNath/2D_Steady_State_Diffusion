#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

int print_matrix(std::vector<std::vector<double>>& arr_2d){
    size_t sz = arr_2d.size(); 
    if (sz>10){
        std::cout<<"Array too big to display. Computations will proceed normally"<<std::endl;
        return 1;    
        
    }
    for (size_t i = 0;i<arr_2d.size();i++) {

        for (size_t j = 0; j < arr_2d[i].size();j++) {

            std::cout<<arr_2d[i][j]<<" "; //space after each element is printed
        }
    std::cout << "\n"; //Print new line after each row is completely printed 
    }
std::cout<<std::endl;
return 0;    
}

void apply_bc(std::vector<std::vector<double>>& arr_2d,double left_bc, double right_bc, double top_bc, double bottom_bc){
    size_t sz = arr_2d[0].size();
    // Loop to apply top wall boundary condition
    for (int j = 0; j<sz; j++){
        arr_2d[0][j] = top_bc;
    }
    // Loop to apply left wall boundary condition 
    for (int i=1; i<(sz-1) ; i++){
        
        arr_2d[i][0] = left_bc;

        
    }
    // Loop to apply right wall boundary condition 
    for (int i = 1;i<(sz - 1);i++){
        
        arr_2d[i][sz-1] = right_bc;
        
        
        
    }
    // Loop to apply bottom wall boundary condition 
    for (int j = 0; j<sz; j++){
        
        arr_2d[sz-1][j] = bottom_bc;
        
        
    }
    
}

// Function to perform numerical computation 
void compute_2d(std::vector<std::vector<double>> arr_2d,std::vector<std::vector<double>>& arr_2d_new){
    size_t sz = arr_2d.size();
    for (int i = 1; i<(sz - 1); i++){
        for (int j = 1;j<(sz - 1); j++){
            arr_2d_new[i][j] = 0.25 * (arr_2d[i+1][j] + arr_2d[i-1][j] + arr_2d[i][j+1] + arr_2d[i][j-1]);
        }
        
    }

    
}

double error_calc_2d(std::vector<std::vector<double>> arr_2d,std::vector<std::vector<double>> arr_2d_new){
    
    double err_sum  = 0;
    double diff_temp;
    
    size_t sz_1 = arr_2d.size();
    size_t sz_2 = arr_2d_new.size();
    
    if (sz_1 != sz_2){
        
        std::cout<<"The array dimensions do not match. Please re-check dimensions"<<std::endl;
        return 0.0;
    }
    for (int i = 0;i<sz_1;i++){
        
        for (int j = 0; j<sz_1;j++){
            
            diff_temp = 0;
            diff_temp = std::abs(arr_2d[i][j] - arr_2d_new[i][j]);
            err_sum = err_sum + diff_temp;
            
        }
    }
    return err_sum;
    
    
}

// Function to write the solution matrix into a csv file 
void write_sol_csv(std::vector<std::vector<double>> arr_2d){

    std::ofstream file("solution_grid.csv");
    for (size_t i = 0; i<arr_2d.size(); i++){

        for (size_t j = 0; j<arr_2d[0].size(); j++){
            file << arr_2d[i][j];
            file << ",";
        }
    file << '\n';    
}
file.close();
}

// Start of main function 
int main(){

// Define domain size and number of divisions 
int dom_len = 1;
int num_div; 
std::cout<<"Enter number of divisions to divide the domain into"<<std::endl;
std::cin>>num_div;

// Define boundary conditions 
double top_wall_val;
double bottom_wall_val;
double left_wall_val;
double right_wall_val;

// Prompt user to enter boundary conditions 
std::cout<<"Enter the top wall temperature value: "<<std::endl; 
std::cin>>top_wall_val; 
std::cout<<"Enter the bottom wall temperature value: "<<std::endl; 
std::cin>>bottom_wall_val; 
std::cout<<"Enter the left wall temperature value: "<<std::endl; 
std::cin>>left_wall_val; 
std::cout<<"Enter the right wall temperature value: "<<std::endl; 
std::cin>>right_wall_val;
 
// Define error tolerance and maximum allowable iterations 
double err_tol = std::pow(10,-6);
int max_iter = 100000;
// Define and initialize a 2D array of size num_div X num_div . By default it initializes all elements with value 0
std::vector<std::vector<double>> T_sol(num_div,
    std::vector<double>(num_div)

);

// Initialize another 2D solution array to hold the computed results in 
std::vector<std::vector<double>> T_sol_new(num_div,
    std::vector<double>(num_div)

);

// Print the Initialized matrix
int err_code = print_matrix(T_sol);

// Apply boundary condition to the two soliution matrices  
apply_bc(T_sol,left_wall_val,right_wall_val,top_wall_val,bottom_wall_val);
apply_bc(T_sol_new,left_wall_val,right_wall_val,top_wall_val,bottom_wall_val);
std::cout<<std::endl;

// Print the initialized matrix with the applied boundary condtions 
if (err_code == 0){
std::cout<<"Initialized solution matrix after applying boundary conditions"<<std::endl;
print_matrix(T_sol);}

// Start solution computation 
double err_temp = 1;
int iter_count = 0;

while (err_temp > err_tol && iter_count<max_iter){
    compute_2d(T_sol,T_sol_new); // Note that this function actually modifies the T_sol_new array 
    iter_count = iter_count + 1;
    err_temp = error_calc_2d(T_sol,T_sol_new);
    T_sol = T_sol_new; 
    if (iter_count == max_iter && err_temp>err_tol){
        std::cout<<"The solution did not converge within the specified number of iterations"<<std::endl;
        return 0;
        
    }
    
    
}
if (err_code == 0){
std::cout<<"The solution matrix is shown below"<<std::endl;
print_matrix(T_sol_new);
}
std::cout<<"The solution converged after "<<iter_count<<" iterations"<<std::endl;
std::cout<<"Residual error is "<<err_temp<<std::endl; 

// Write the results to a csv file 
write_sol_csv(T_sol_new);
return 0;
}