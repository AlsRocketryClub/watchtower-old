# plot.py
import my_module
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Function to plot the data
def plot_data(data):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.scatter(data[:,0], data[:,1], data[:,2])
    plt.show()

# Call C++ function and plot
data = my_module.generate_data()
plot_data(data)
