
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation, FFMpegWriter
from mpl_toolkits.mplot3d import Axes3D

# === PARAMETRI ===
filename = "out.dat"
n_particles = 10000
dt = 0.01
fps = 60
speed = 1.0
show_trail = False
trail_length = 100
point_size = 2
save_video = True
output_file = "animazione_1080p_zoom.mp4"
bitrate = 15000
dpi = 300

# Parametri telecamera
elev = 30              # elevazione in gradi
azim = -45          # azimut in gradi
zoom_factor = 1.0     # 1.0 = nessuno zoom, <1 = zoom in

# === CARICAMENTO DATI ===
df = pd.read_csv(filename, sep=r"\s+", engine="python")
t = df["t"].values.reshape(-1, n_particles)
x = df["x"].values.reshape(-1, n_particles)
y = df["y"].values.reshape(-1, n_particles)
z = df["z"].values.reshape(-1, n_particles)
n_frames = t.shape[0]

# === FIGURA ===
fig = plt.figure(figsize=(6.4, 3.6), dpi=dpi)  # 1920x1080
ax = fig.add_subplot(111, projection="3d")

# calcolo limiti centrati e zoomati
x_center, y_center, z_center = x.mean(), y.mean(), z.mean()
x_range, y_range, z_range = (x.max()-x.min())*zoom_factor/2, (y.max()-y.min())*zoom_factor/2, (z.max()-z.min())*zoom_factor/2

ax.set_xlim(x_center - x_range, x_center + x_range)
ax.set_ylim(y_center - y_range, y_center + y_range)
ax.set_zlim(z_center - z_range, z_center + z_range)

ax.set_xlabel("X [m]")
ax.set_ylabel("Y [m]")
ax.set_zlabel("Z [m]")
ax.view_init(elev=elev, azim=azim)

time_text = ax.text2D(0.05, 0.95, "", transform=ax.transAxes)

# scatter per i punti
scat = ax.scatter([], [], [], s=point_size)

# scie (se abilitate)
if show_trail:
    trails = [ax.plot([], [], [], "-", alpha=0.3, linewidth=0.5)[0] for _ in range(n_particles)]
else:
    trails = []

# === UPDATE FRAME ===
def update(frame):
    scat._offsets3d = (x[frame], y[frame], z[frame])
    if show_trail:
        for i, tr in enumerate(trails):
            start = max(0, frame - trail_length)
            tr.set_data(x[start:frame, i], y[start:frame, i])
            tr.set_3d_properties(z[start:frame, i])
    time_text.set_text(f"t = {t[frame,0]:.3f} s")
    return [scat] + trails + [time_text]

# === ANIMAZIONE ===
interval = 1000 * dt / speed
ani = FuncAnimation(fig, update, frames=n_frames, interval=interval, blit=False)

# === SALVATAGGIO O DISPLAY ===
if save_video:
    writer = FFMpegWriter(fps=fps, metadata=dict(artist="me"), bitrate=bitrate)
    ani.save(output_file, writer=writer, dpi=dpi)
    print(f"Animazione salvata in {output_file} con qualità 1080p e zoom={zoom_factor}")
else:
    plt.show()
