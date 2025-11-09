import time

import matplotlib.pyplot as plt
import numpy as np

data_points = np.array(
    [
        (3, 1),
        (18, 16),
        (19, 15),
        (-12, 8),
        (1, 2),
        (4, -10),
        (17, 14),
        (-1, 3),
        (-13, 10),
        (-12, 11),
        (5, -8),
        (3, -11),
        (-11, 12),
        (5, -7),
        (3, -8),
        (5, -8),
        (5, -8),
        (-1, -1),
    ]
)

plt.figure(figsize=(7, 7))
plt.scatter(
    data_points[:, 0],
    data_points[:, 1],
    color="#9467bd",
    label="Объекты",
    s=100,
    edgecolor="black",
)
plt.axhline(0, color="black", linewidth=0.5)
plt.axvline(0, color="black", linewidth=0.5)
plt.grid(True)
plt.gca().set_facecolor("#f0f0f0")
plt.legend()
plt.title("Исходные данные", fontsize=16)
plt.tight_layout()
plt.show()


num_clusters = int(input("Введите количество кластеров: "))


neuron_weights = np.random.uniform(-1, 1, (num_clusters, 2))
neuron_weights /= np.linalg.norm(neuron_weights, axis=1, keepdims=True)


def find_winner_index(point, weights):
    distances = np.linalg.norm(weights - point, axis=1)
    return np.argmin(distances)


def train_kohonen(points, weights, iterations=100, learning_rate=0.5):
    for current_iteration in range(iterations):
        lr = learning_rate * (1 - current_iteration / iterations)
        for point in points:
            winner_index = find_winner_index(point, weights)
            weights[winner_index] += lr * (point - weights[winner_index])
    return weights


start_time = time.time()
classic_weights = train_kohonen(
    data_points, neuron_weights.copy(), iterations=100, learning_rate=0.5
)
print(
    "Время обучения алгоритмом 'победитель забирает всё': ",
    time.time() - start_time,
)


fatigue_array = np.zeros(num_clusters)


def train_kohonen_with_fatigue(points, weights, iterations=100, learning_rate=0.3):
    fatigue_array = np.zeros(weights.shape[0])
    for current_iteration in range(iterations):
        lr = learning_rate * (1 - current_iteration / iterations)
        for point in points:
            distances = np.linalg.norm(weights - point, axis=1) + fatigue_array
            winner_index = np.argmin(distances)
            weights[winner_index] += lr * (point - weights[winner_index])
            fatigue_array[winner_index] += 0.5
    return weights


def train_kohonen_with_fatigue2(
    points, weights, iterations=100, learning_rate=0.3, convergence_threshold=0.01
):
    num_neurons = weights.shape[0]
    fatigue = np.zeros(num_neurons)

    for iteration in range(iterations):
        old_weights = weights.copy()
        point = points[np.random.randint(points.shape[0])]
        distances = np.linalg.norm(weights - point, axis=1)
        winner = np.argmin(distances)
        fatigue[winner] += 1
        weights[winner] += learning_rate * (point - weights[winner])
        fatigue *= 0.9

        weight_change = np.max(np.abs(weights - old_weights))
        if weight_change < convergence_threshold:
            break
    return weights


start_time = time.time()
fatigue_weights = train_kohonen_with_fatigue2(
    data_points, neuron_weights.copy(), iterations=100, learning_rate=0.5
)
print(
    "Время обучения алгоритмом с применением механизма утомляемости нейронов: ",
    time.time() - start_time,
)


plt.figure(figsize=(7, 7))
plt.scatter(
    data_points[:, 0],
    data_points[:, 1],
    color="#9467bd",
    label="Объекты",
    s=100,
    edgecolor="black",
)
plt.scatter(
    classic_weights[:, 0],
    classic_weights[:, 1],
    color="#9467bd",
    label="Классические веса",
    marker="P",
    s=200,
)
plt.scatter(
    fatigue_weights[:, 0],
    fatigue_weights[:, 1],
    color="#ffff00",
    label="Веса с утомляемостью",
    s=200,
    marker="D",
)
plt.axhline(0, color="black", linewidth=0.5)
plt.axvline(0, color="black", linewidth=0.5)
plt.grid(True)
plt.gca().set_facecolor("#f0f0f0")
plt.legend()
plt.title("Сравнение весов нейронов", fontsize=16)
plt.tight_layout()
plt.show()


scale_factor = 1
scaled_weights = fatigue_weights * scale_factor
scaled_classic_weights = classic_weights * scale_factor


plt.figure(figsize=(7, 7))
plt.scatter(
    data_points[:, 0],
    data_points[:, 1],
    color="#9467bd",
    label="Объекты",
    s=100,
    edgecolor="black",
)
plt.quiver(
    [0] * num_clusters,
    [0] * num_clusters,
    scaled_weights[:, 0],
    scaled_weights[:, 1],
    angles="xy",
    scale_units="xy",
    scale=1,
    color="#9467bd",
    label="Масштабированные веса",
    linewidth=2,
)
plt.axhline(0, color="black", linewidth=0.5)
plt.axvline(0, color="black", linewidth=0.5)
plt.grid(True)
plt.gca().set_facecolor("#f0f0f0")
plt.legend()
plt.title("Масштабированные вектора весов с утомляемостью", fontsize=16)
plt.tight_layout()
plt.show()


plt.figure(figsize=(7, 7))
plt.scatter(
    data_points[:, 0],
    data_points[:, 1],
    color="#9467bd",
    label="Объекты",
    s=100,
    edgecolor="black",
)
plt.quiver(
    [0] * num_clusters,
    [0] * num_clusters,
    scaled_classic_weights[:, 0],
    scaled_classic_weights[:, 1],
    angles="xy",
    scale_units="xy",
    scale=1,
    color="#9467bd",
    label="Масштабированные веса",
    linewidth=2,
)
plt.axhline(0, color="black", linewidth=0.5)
plt.axvline(0, color="black", linewidth=0.5)
plt.grid(True)
plt.gca().set_facecolor("#f0f0f0")
plt.legend()
plt.title("Масштабированные вектора весов без утомляемости", fontsize=16)
plt.tight_layout()
plt.show()
