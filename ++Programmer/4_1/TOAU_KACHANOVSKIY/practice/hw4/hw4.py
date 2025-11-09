import math
from collections import defaultdict


class Activity:
    def __init__(self, name, predecessors, a, m, b):
        self.name = name
        self.predecessors = predecessors.split(",") if predecessors else []
        self.a = a
        self.m = m
        self.b = b
        self.te = (a + 4 * m + b) / 6
        self.variance = ((b - a) / 6) ** 2


class Project:
    def __init__(self):
        self.activities = {}
        self.graph = defaultdict(list)

    def add_activity(self, name, predecessors, a, m, b):
        activity = Activity(name, predecessors, a, m, b)
        self.activities[name] = activity
        if predecessors:
            for pred in activity.predecessors:
                self.graph[pred].append(name)
        else:
            self.graph[name] = []

    def find_all_paths(self, start, end, path=[]):
        path = path + [start]
        if start == end:
            return [path]
        if start not in self.graph:
            return []
        paths = []
        for node in self.graph[start]:
            if node not in path:
                new_paths = self.find_all_paths(node, end, path)
                for new_path in new_paths:
                    paths.append(new_path)

        return paths

    def find_critical_path(self, all_paths):
        max_time = 0
        critical_path = []
        for path in all_paths:
            path_time = sum(self.activities[activity].te for activity in path)
            if path_time > max_time:
                max_time = path_time
                critical_path = path
        return critical_path, max_time

    def print_expected_times_and_variances(self):
        print("Ожидаемые сроки выполнения операций и дисперсии:")
        print("Операция\tT_ож\tДисперсия")
        for activity in self.activities.values():
            print(f"{activity.name}\t\t{activity.te:.2f}\t{activity.variance:.2f}")

    def calculate_event_times(self):
        earliest_start = {name: 0 for name in self.activities}
        earliest_finish = {name: 0 for name in self.activities}

        # Forward pass
        for activity in self.activities.values():
            for pred in activity.predecessors:
                earliest_start[activity.name] = max(
                    earliest_start[activity.name], earliest_finish[pred]
                )
            earliest_finish[activity.name] = earliest_start[activity.name] + activity.te

        # Backward pass
        latest_finish = {name: earliest_finish[name] for name in self.activities}
        latest_start = {name: earliest_finish[name] for name in self.activities}

        for activity in reversed(list(self.activities.values())):
            for succ in self.graph[activity.name]:
                latest_finish[activity.name] = min(
                    latest_finish[activity.name], latest_start[succ]
                )
            latest_start[activity.name] = latest_finish[activity.name] - activity.te

        print("\nОжидаемые сроки событий:")
        print("Событие\tT_P_ож\tT_n_ож\tP\tДисперсия")
        for activity in self.activities.values():
            print(
                f"{activity.name}\t{earliest_start[activity.name]:.2f}\t{latest_start[activity.name]:.2f}\t{latest_start[activity.name] - earliest_start[activity.name]:.2f}\t{activity.variance:.2f}"
            )

    def calculate_critical_delta(self, critical_path, activities):
        critical_delta = math.sqrt(
            sum(activities[activity].variance for activity in critical_path)
        )
        return critical_delta

    def print_all_paths(self, all_paths):
        print("\nВсе возможные пути:")
        for path in all_paths:
            print(" -> ".join(path))


# Создаем проект и добавляем задачи
project = Project()
project.add_activity("A", "", 1.5, 2, 2.5)
project.add_activity("B", "A", 2, 2.5, 6)
project.add_activity("C", "", 1, 2, 3)
project.add_activity("D", "C", 1.5, 2, 2.5)
project.add_activity("E", "B,D", 0.5, 1, 1.5)
project.add_activity("F", "E", 1, 2, 3)
project.add_activity("G", "B,D", 3, 3.5, 7)
project.add_activity("H", "G", 3, 4, 5)
project.add_activity("I", "F,H", 1.5, 2, 2.5)

# Находим все возможные пути
all_paths = project.find_all_paths("A", "I") + project.find_all_paths("C", "I")
project.print_all_paths(all_paths)
project.print_expected_times_and_variances()
# Находим критический путь
critical_path, critical_time = project.find_critical_path(all_paths)

# Преобразуем критический путь в строки, если это необходимо
critical_path = [str(activity) for activity in critical_path]

# Рассчитываем критическую дельту
critical_delta = project.calculate_critical_delta(critical_path, project.activities)
print(f"Критическая дельта (крит. пути {critical_path}): {critical_delta:.4f}")
