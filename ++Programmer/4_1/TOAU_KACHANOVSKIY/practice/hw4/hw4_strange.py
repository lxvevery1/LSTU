# Input data for operations
import math

# Define the operations data
operations = {
    "A": {"predecessors": [], "optimistic": 1.5, "most_likely": 2, "pessimistic": 2.5},
    "B": {"predecessors": ["A"], "optimistic": 2, "most_likely": 2.5, "pessimistic": 6},
    "C": {"predecessors": [], "optimistic": 1, "most_likely": 2, "pessimistic": 3},
    "D": {
        "predecessors": ["C"],
        "optimistic": 1.5,
        "most_likely": 2,
        "pessimistic": 2.5,
    },
    "E": {
        "predecessors": ["B", "D"],
        "optimistic": 0.5,
        "most_likely": 1,
        "pessimistic": 1.5,
    },
    "F": {"predecessors": ["E"], "optimistic": 1, "most_likely": 2, "pessimistic": 3},
    "G": {
        "predecessors": ["B", "D"],
        "optimistic": 3,
        "most_likely": 3.5,
        "pessimistic": 7,
    },
    "H": {"predecessors": ["G"], "optimistic": 3, "most_likely": 4, "pessimistic": 5},
    "I": {
        "predecessors": ["F", "H"],
        "optimistic": 1.5,
        "most_likely": 2,
        "pessimistic": 2.5,
    },
}

# Initialize results
event_early_times = {"start": 0}  # Early times for each event
event_variance = {"start": 0}  # Variance for each event
activity_data = {}  # Store calculated activity data


# Function to calculate mean and variance for an activity
def calculate_activity_data(optimistic, most_likely, pessimistic):
    mean_time = (optimistic + 4 * most_likely + pessimistic) / 6
    variance = ((pessimistic - optimistic) / 6) ** 2
    return mean_time, variance


# Perform forward pass to calculate early times
for operation, data in operations.items():
    mean_time, variance = calculate_activity_data(
        data["optimistic"], data["most_likely"], data["pessimistic"]
    )
    activity_data[operation] = {"mean_time": mean_time, "variance": variance}
    if data["predecessors"]:
        earliest_start = max(
            event_early_times[predecessor] for predecessor in data["predecessors"]
        )
    else:
        earliest_start = 0
    event_early_times[operation] = earliest_start + mean_time
    event_variance[operation] = (
        sum(event_variance[predecessor] for predecessor in data["predecessors"])
        + variance
    )

# Format the result as a table
results = [
    {
        "Event": operation,
        "T_early": round(event_early_times[operation], 2),
        "Variance": round(event_variance[operation], 4),
    }
    for operation in event_early_times
]

# Perform backward pass to calculate late times

project_duration = max(
    event_early_times.values()
)  # Maximum early time as project duration

event_late_times = {
    event: project_duration for event in event_early_times
}  # Initialize with project duration


# Calculate late times by traversing in reverse order

for operation in reversed(list(event_early_times.keys())):

    if operation not in operations:

        continue

    successors = [
        successor
        for successor, data in operations.items()
        if operation in data["predecessors"]
    ]

    if successors:

        event_late_times[operation] = min(
            event_late_times[successor] - activity_data[successor]["mean_time"]
            for successor in successors
        )


# Update results to include late times

for result in results:

    event = result["Event"]

    result["T_late"] = round(event_late_times.get(event, 0), 2)

print(results)


# Identify the critical path by tracking predecessors and using T_early values
critical_path = []
current_event = max(
    event_early_times, key=event_early_times.get
)  # Event with max T_early
while current_event != "start":
    critical_path.append(current_event)
    predecessors = [
        predecessor
        for predecessor in operations[current_event]["predecessors"]
        if event_early_times[current_event] - event_early_times[predecessor]
        == activity_data[current_event]["mean_time"]
    ]
    if predecessors:
        current_event = predecessors[0]
    else:
        break
critical_path.append("start")
critical_path.reverse()

# Recalculate variances and probabilities for the critical path
critical_path_variance = sum(
    activity_data[event]["variance"]
    for event in critical_path
    if event in activity_data
)
std_dev = math.sqrt(critical_path_variance)  # Standard deviation

# Format results with newlines for better readability

formatted_results = "\n".join(
    f"Event: {result['Event']}, T_early: {result['T_early']}, T_late: {result['T_late']}, Variance: {result['Variance']}"
    for result in results
)

print(formatted_results)
