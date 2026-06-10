import numpy as np
import matplotlib.pyplot as plt 
 

# Load the CSV file
sol_mat = np.genfromtxt('solution_grid.csv',delimiter = ',')
sol_mat = sol_mat[:, :-1] # Dropping the last colummn because it contains the null/newline character printed by the c++ engine
# print(sol_mat.shape)
# print(sol_mat)

n = sol_mat.shape
num_rows = n[0];
num_col = n[0];
x = np.linspace(0,1,num_rows)
y = np.linspace(0,1,num_rows)
xv,yv = np.meshgrid(x,y)
contour_plot = plt.contourf(xv,yv,sol_mat,cmap = 'coolwarm',levels = 10)
plt.colorbar(contour_plot)
plt.gca().invert_yaxis()
plt.xlabel("X Co-ordinate")
plt.ylabel("Y Co-ordinate")
plt.show()