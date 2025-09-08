import pandas as pd
import plotly.graph_objects as go


filename = "out.dat"
n_particles = 10000
point_size = 2
dt = 0.001



#--------------INPUT
df = pd.read_csv(filename, sep=r"\s+", engine="python")
x = df["x"].values.reshape(-1, n_particles)
y = df["y"].values.reshape(-1, n_particles)
z = df["z"].values.reshape(-1, n_particles)
t = df["t"].values.reshape(-1, n_particles)
n_frames = x.shape[0]




#-------------qua sono creati i frame ad ogni passo temporale
frames = [
    go.Frame(
        data=[go.Scatter3d(
            x=x[k],
            y=y[k],
            z=z[k],
            mode='markers',
            marker=dict(size=point_size, color='blue')
        )],
        name=f'frame{k}'
    )
    for k in range(n_frames)
]

#-----------------------genero la figura
fig = go.Figure(
    data=[go.Scatter3d(
        x=x[0],
        y=y[0],
        z=z[0],
        mode='markers',
        marker=dict(size=point_size, color='blue')
    )],
    frames=frames
)

#-------------------------genero il layout dell'html
fig.update_layout(
    width=1080,
    height=720,
    scene=dict(
        xaxis_title='X [m]',
        yaxis_title='Y [m]',
        zaxis_title='Z [m]'
    ),
    updatemenus=[dict(
        type="buttons",
        showactive=False,
        y=1,
        x=1.1,
        xanchor="right",
        yanchor="top",
        buttons=[
            dict(label="Play",
                 method="animate",
                 args=[None, {"frame": {"duration": dt*1000, "redraw": True},
                              "fromcurrent": True, "transition": {"duration": 0}}]),
            dict(label="Pause",
                 method="animate",
                 args=[[None], {"frame": {"duration": 0, "redraw": False},
                                "mode": "immediate",
                                "transition": {"duration": 0}}])
        ]
    )]
)


fig.show()
