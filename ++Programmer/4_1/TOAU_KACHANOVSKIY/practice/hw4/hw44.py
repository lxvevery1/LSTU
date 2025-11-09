import networkx as nx
import pandas as pd

data = {
    "Проц": ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O"],
    "Пред. проц.": [
        None,
        "A",
        "A",
        "C",
        "C",
        "C",
        "D,E,F",
        "G",
        "H",
        "H",
        "I,J",
        "K",
        "L",
        "L",
        "B,M,N",
    ],
    "O": [9, 5, 10, 8, 9, 9, 10, 8, 9, 10, 9, 5, 7, 10, 8],
    "P": [13, 11, 17, 15, 16, 17, 17, 13, 17, 16, 18, 14, 17, 18, 13],
}


df = pd.DataFrame(data)


df["Te"] = (df["O"] + 4 * ((df["O"] + df["P"]) / 2) + df["P"]) / 6
df["V"] = ((df["P"] - df["O"]) / 6) ** 2
print("Промежуточные расчеты (Te и V):\n", df[["Проц", "Te", "V"]])


G = nx.DiGraph()


for _, row in df.iterrows():
    G.add_node(row["Проц"], Te=row["Te"], V=row["V"])


for _, row in df.iterrows():
    if row["Пред. проц."]:
        predecessors = row["Пред. проц."].split(",")
        for pred in predecessors:
            G.add_edge(pred.strip(), row["Проц"])


critical_path = nx.dag_longest_path(G, weight="Te")
critical_time = sum(G.nodes[node]["Te"] for node in critical_path)
critical_variance = sum(G.nodes[node]["V"] for node in critical_path)
critical_std_dev = critical_variance**0.5


Z = 2.05
time_98 = critical_time + Z * critical_std_dev


print("\nРезультаты:")
print(
    f"Критический путь: {critical_path}\n"
    f"Общее критическое время: {critical_time}\n"
    f"Суммарная дисперсия пути: {critical_variance}\n"
    f"Нормальное отклонение критического пути: {critical_std_dev}\n"
    f"Время завершения проекта с вероятностью 0.98: {time_98}"
)

import matplotlib.pyplot as plt

plt.figure(figsize=(12, 8))

pos = nx.spring_layout(G)

nx.draw_networkx_nodes(G, pos, node_size=700, node_color="lightblue")
nx.draw_networkx_labels(G, pos, font_size=10, font_color="black")

nx.draw_networkx_edges(
    G, pos, edgelist=G.edges(), arrowstyle="->", arrowsize=40, edge_color="gray"
)

plt.title("Граф", fontsize=14)
plt.axis("off")
plt.show()
