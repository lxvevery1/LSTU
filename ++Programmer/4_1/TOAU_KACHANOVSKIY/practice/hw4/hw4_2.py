import numpy as np

tasks = {
    1: {"O": 1, "P": 3, "M": 2},
    2: {"O": 3, "P": 5, "M": 3.5},
    3: {"O": 5, "P": 7, "M": 5.5},
}


for task_id, task in tasks.items():
    O = task["O"]
    P = task["P"]
    M = task["M"]

    T_e = (O + 4 * M + P) / 6

    V = ((P - O) / 6) ** 2

    task["T_e"] = T_e
    task["V"] = V


total_time = sum(task["T_e"] for task in tasks.values())
total_variance = sum(task["V"] for task in tasks.values())


std_dev = np.sqrt(total_variance)


Z = 1.645
time_95 = total_time + Z * std_dev


print("Задачи и их данные:")
for task_id, task in tasks.items():
    print(f"Задача {task_id}: T_e = {task['T_e']:.2f}, V = {task['V']:.2f}")

print(f"\nОбщее среднее время проекта: {total_time:.2f}")
print(f"Общая дисперсия: {total_variance:.2f}")
print(f"Стандартное отклонение: {std_dev:.2f}")
print(f"Время завершения проекта с вероятностью 0.95: {time_95:.2f}")
