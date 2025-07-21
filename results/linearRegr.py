import matplotlib.pyplot as plt
import numpy as np
from sklearn.linear_model import LinearRegression

# Dane wejściowe
sizes = np.array([10, 50, 100, 200, 500]).reshape(-1, 1)
dijkstra_times = np.array([6.144e-06, 6.6062e-05, 0.000213656, 0.000712742, 0.00377046])
b_f_times = np.array([6.8923e-05, 0.00622094, 0.0434353, 0.31587, 4.49871])
dfs_times = np.array([4.034e-06, 5.2915e-05, 0.000207634, 0.000744125, 0.00417333])

sizes_flat = sizes.flatten()

# Dijkstra: regresja po x*log(x)
xlogx = (sizes_flat * np.log(sizes_flat)).reshape(-1, 1)
reg_dijk = LinearRegression().fit(xlogx, dijkstra_times)
pred_dijk = reg_dijk.predict(xlogx)

# Bellman-Ford: regresja wykładnicza
log_bf = np.log(b_f_times)
reg_bf_exp = LinearRegression().fit(sizes, log_bf)
exp_pred_bf = np.exp(reg_bf_exp.predict(sizes))

# DFS: klasyczna regresja liniowa
reg_dfs = LinearRegression().fit(sizes, dfs_times)
pred_dfs = reg_dfs.predict(sizes)

# Wykresy
def plot_fit(x, y, y_pred, title, label, color):
    plt.figure(figsize=(8, 5))
    plt.scatter(x, y, color=color, label=f'Czas ({label})')
    plt.plot(x, y_pred, 'k--', label='Dopasowanie')
    plt.title(title)
    plt.xlabel('Rozmiar struktury danych')
    plt.ylabel('Czas [s]')
    plt.grid(True, linestyle='--', alpha=0.6)
    plt.legend()
    plt.tight_layout()
    plt.show()

plot_fit(sizes_flat, dijkstra_times, pred_dijk, 'Dijkstra: regresja x·log(x)', 'Dijkstra', 'blue')
plot_fit(sizes_flat, b_f_times, exp_pred_bf, 'Bellman-Ford: regresja wykładnicza', 'Bellman-Ford', 'green')
plot_fit(sizes_flat, dfs_times, pred_dfs, 'DFS: regresja liniowa', 'DFS', 'red')

# Wypisanie współczynników
print("Dijkstra (x·log(x)):")
print(f"  a = {reg_dijk.coef_[0]:.6e}, b = {reg_dijk.intercept_:.6e}")
print("Bellman-Ford (y = exp(ax + b)):")
print(f"  a = {reg_bf_exp.coef_[0]:.6f}, b = {reg_bf_exp.intercept_:.6f}")
print("DFS (liniowa):")
print(f"  a = {reg_dfs.coef_[0]:.6e}, b = {reg_dfs.intercept_:.6e}")
