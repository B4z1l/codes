
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

# === Lettura dati ===
df = pd.read_csv("out.dat", sep=r"\s+", header=None, names=["t", "x", "y"], low_memory = False)
df = df.apply(pd.to_numeric, errors="coerce").dropna()

# Numero di particelle
n_particles = 30

# Ricostruisco in matrici (n_steps, n_particles)
n_steps = len(df) // n_particles
t = df["t"].values.reshape(n_steps, n_particles)[:, 0]
x = df["x"].values.reshape(n_steps, n_particles)
y = df["y"].values.reshape(n_steps, n_particles)

# === Setup figura ===
fig, ax = plt.subplots()
ax.set_xlim(x.min() - 1, x.max() + 1)
ax.set_ylim(y.min() - 1, y.max() + 1)
ax.set_xlabel("X")
ax.set_ylabel("Y")
ax.set_title("Animazione particelle (scalata nel tempo)")

# Testo del tempo
time_text = ax.text(0.02, 0.95, '', transform=ax.transAxes)

# Colori e artisti
colors = plt.cm.tab10(np.linspace(0, 1, n_particles))
points = [ax.plot([], [], 'o', color=colors[i], markersize=6)[0] for i in range(n_particles)]
trails = [ax.plot([], [], '-', color=colors[i], linewidth=1, alpha=0.7)[0] for i in range(n_particles)]

# === Controlli temporali ===
dt = 0.001          # tuo passo simulazione (s) -> metti quello reale
target_fps = 60    # fps del video/animazione
real_time_factor = 1.0  # 1 s reale mostra 5 s di simulazione (aumenta per accelerare)

# ogni frame deve coprire questa quantità di tempo di simulazione:
sim_time_per_frame = real_time_factor / target_fps
# quanti passi di simulazione saltare tra frame mostrati:
step = max(1, int(round(sim_time_per_frame / dt)))
# intervallo reale tra frame (ms)
interval = 1000 / target_fps

# indici dei frame che mostreremo
frames_idx = list(range(0, n_steps, step))

# Lunghezza scia in secondi (invece che in passi, così resta coerente con la fisica)
trail_seconds = 0.5                      # scia di 0.5 s di simulazione
trail_len_steps = max(1, int(round(trail_seconds / dt)))

def init():
    for p, tr in zip(points, trails):
        p.set_data([], [])
        tr.set_data([], [])
    time_text.set_text('')
    return points + trails + [time_text]

def update(frame_idx):
    start = max(0, frame_idx - trail_len_steps)
    for i, (p, tr) in enumerate(zip(points, trails)):
        # punto attuale (liste di lunghezza 1!)
        p.set_data([x[frame_idx, i]], [y[frame_idx, i]])
        # scia (ultimi trail_len_steps passi reali, non solo frame mostrati)
        tr.set_data(x[start:frame_idx+1, i], y[start:frame_idx+1, i])
    time_text.set_text(f"t = {t[frame_idx]:.3f} s")
    return points + trails + [time_text]

ani = animation.FuncAnimation(
    fig, update, frames=frames_idx, init_func=init, blit=True, interval=interval
)

plt.show()
