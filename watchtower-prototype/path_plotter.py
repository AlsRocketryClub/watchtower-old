# -----------------------------------
#
# VTK Plotter for visualizing the trajectory 
# 
# Contributors: Arturo, Arkadiusz, Kyril, Hans
# The Als Rocketry Club
# Sonderborg, Denmark
# 
# -----------------------------------

import plotly.graph_objects as go
import numpy as np

# Generate random data
N = 1000
random_x = np.random.randn(N)
random_y = np.random.randn(N)
random_z = np.random.randn(N)

# Create a 3D scatter plot
fig = go.Figure(data=[go.Scatter3d(
    x=random_x,
    y=random_y,
    z=random_z,
    mode='markers',
    marker=dict(
        size=6,
        color=random_z,  # set color to z values
        colorscale='Viridis',  # choose a colorscale
        opacity=0.8
    )
)])

# Set the title and axis labels
fig.update_layout(
    scene=dict(
        xaxis_title='X',
        yaxis_title='Y',
        zaxis_title='Z'
    ),
    title="3D Scatter Plot"
)

fig.show()
