import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import FuncAnimation

# Parameters
T = 100 # Total number of time steps
dt = 0.1 # Time step (seconds)
freq = 1.0 # Frequency of the sine wave (Hz)

# Initilaize figure and axes
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Create time array
t = np.arange(0 , T*dt, dt)

# Initialize empty arrays for coordinates
x_coords = np.zeros(T)
y_coords = np.zeros(T)
z_coords = np.zeros(T)

# Update function
def update(i):
    # Calculate new coordinates
    x_coords[i] = np.sin(2*np.pi*freq*t[i])
    y_coords[i] = np.cos(2*np.pi*freq*t[i])
    z_coords[i] = t[i]

    # Update scatter plot
    ax.clear()
    ax.plot(x_coords, y_coords, z_coords, 'r-')
    ax.set_xlim(-1, 1)
    ax.set_ylim(-1, 1)
    ax.set_zlim(0, T*dt)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    ax.set_title('3D Sine Wave')
    return ax

# Show the plot
plt.show()

# Create animation
#ani = FuncAnimation(fig, update, frames=range(T), interval = 100) # interval in milliseconds


