def load_rules(file_path):
    rules = []
    with open(file_path, "r", encoding="utf-8") as file:
        for line in file:
            if line.strip():
                condition, result = line.strip().split(" ТО ")
                conditions = condition.replace("ЕСЛИ ", "").split(" И ")
                result_obj, result_val = result.split("=")
                rules.append((conditions, (result_obj.strip(), result_val.strip())))
    return rules


def backward_inference_engine(rules, goal, facts):
    checked_goals = set()
    applied_rules = []

    def prove(goal_obj, goal_val):
        if (goal_obj, goal_val) in checked_goals:
            return False

        if facts.get(goal_obj, "").lower() == goal_val.lower():
            return True

        for conditions, (result_obj, result_val) in rules:
            if result_obj == goal_obj and result_val.lower() == goal_val.lower():
                all_conditions_met = True
                for condition in conditions:
                    cond_obj, cond_val = condition.split("=")
                    if not prove(cond_obj.strip(), cond_val.strip()):
                        all_conditions_met = False
                        break
                if all_conditions_met:
                    facts[goal_obj] = goal_val
                    applied_rules.append(
                        f"ЕСЛИ {' И '.join(conditions)} ТО {result_obj} = {result_val}"
                    )
                    return True

        checked_goals.add((goal_obj, goal_val))
        return False

    success = prove(goal[0], goal[1])
    return success, applied_rules


def load_start_values(file_path):
    facts = {}
    with open(file_path, "r", encoding="utf-8") as file:
        for line in file:
            key, value = line.strip().split("=")
            facts[key] = value
    return facts


def main():
    rules_file = "bz.txt"
    rules = load_rules(rules_file)

    facts = load_start_values("start_val.txt")
    goal = ("бумага", "текст")

    print(rules)
    print("\n")
    print(facts)
    print("\n")
    print(goal)

    success, applied_rules = backward_inference_engine(rules, goal, facts)

    if success:
        print(f"Goal '{goal[0]} = {goal[1]}' achieved!")
        print("\nUsed facts:")
        for obj, val in facts.items():
            print(f"{obj} = {val}")

        print("\nWe pass the following rules:")
        rule_count = 0
        for rule in applied_rules:
            rule_count += 1
            print(f"{rule_count}. {rule}")
    else:
        print(f"Goal '{goal[0]} = {goal[1]}' cannot be achieved.")


if __name__ == "__main__":
    main()
