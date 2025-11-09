import subprocess
from rich.columns import Columns
from rich.console import Console
from rich.panel import Panel
from rich.prompt import Prompt
from rich.table import Table


def load_rules(_file_path):
    rules = []
    with open(_file_path, "r", encoding="utf-8") as file:
        for line in file:
            if line.strip():
                condition, result = line.strip().split(" ТО ")
                conditions = condition.replace("ЕСЛИ ", "").split(" И ")
                result_obj, result_val = result.split("=")
                rules.append((conditions, (result_obj.strip(), result_val.strip())))
    return rules


def load_start_values(_file_path):
    facts = {}
    with open(_file_path, "r", encoding="utf-8") as file:
        for line in file:
            key, value = line.strip().split("=")
            facts[key] = value
    return facts


def reverse_inference(_rules, _trg, _facts):
    checked_trgs = set()
    applied_rules = []

    def prove(trg_obj, trg_val):
        if (trg_obj, trg_val) in checked_trgs:
            return False

        if _facts.get(trg_obj, "").lower() == trg_val.lower():
            return True

        for ifs, (res_obj, res_val) in _rules:
            if res_obj == trg_obj and res_val.lower() == trg_val.lower():
                all_conditions_met = True
                for condition in ifs:
                    cond_obj, cond_val = condition.split("=")
                    if not prove(cond_obj.strip(), cond_val.strip()):
                        all_conditions_met = False
                        break
                if all_conditions_met:
                    _facts[trg_obj] = trg_val
                    nice_rule = f"ЕСЛИ {' И '.join(ifs)} ТО {res_obj}={res_val}"
                    applied_rules.append(nice_rule)

                    return True

        checked_trgs.add((trg_obj, trg_val))
        return False

    return prove(_trg[0], _trg[1]), applied_rules


def reverse_inference_console(_console, _rules, _trg, _facts):
    print(f"--------------LOGGER---------------")
    checked_trgs = set()
    applied_rules = []

    def prove(trg_obj, trg_val):
        _console.print(
            f"[LOG] Searching for Target object [{trg_obj}] and Target value [{trg_val}]"
        )
        if (trg_obj, trg_val) in checked_trgs:
            _console.print(
                f"[LOG] Target object [{trg_obj}] and Target value [{trg_val}] are already in checked_trgs... returning false",
                style="red",
            )
            return False

        if _facts.get(trg_obj, "").lower() == trg_val.lower():
            _console.print(
                f"[LOG] Facts's found! -> {_facts.get(trg_obj, "").lower()} is the same as {trg_val}, returning true",
                style="yellow",
            )
            return True

        for ifs, (res_obj, res_val) in _rules:
            if res_obj == trg_obj and res_val.lower() == trg_val.lower():
                _console.print(
                    f"[LOG] {res_obj} == {trg_obj} and {res_val.lower()} == {trg_val.lower()}"
                )
                all_conditions_met = True
                for condition in ifs:
                    cond_obj, cond_val = condition.split("=")
                    _console.print(
                        f"[LOG] We looking at condition: {cond_obj}={cond_val}"
                    )
                    if not prove(cond_obj.strip(), cond_val.strip()):
                        _console.print(
                            f"[LOG] {cond_obj} not proved {cond_val}", style="red"
                        )
                        all_conditions_met = False
                        break
                if all_conditions_met:
                    _console.print(f"[LOG] all coditions are met!", style="green")
                    _facts[trg_obj] = trg_val
                    nice_rule = f"ЕСЛИ {' И '.join(ifs)} ТО {res_obj}={res_val}"
                    applied_rules.append(nice_rule)
                    _console.print(f"[LOG] New applied rule: {nice_rule}\n")

                    return True

        _console.print(f"[LOG] Added new checked_trgs: {trg_obj}={trg_val}\n")
        checked_trgs.add((trg_obj, trg_val))
        return False

    return prove(_trg[0], _trg[1]), applied_rules


def display_facts(_facts):
    table = Table(title="Facts")
    table.add_column("Object", justify="left")
    table.add_column("Value", justify="left")
    for obj, val in _facts.items():
        table.add_row(obj, val)
    return table


def display_target(_target):
    table = Table(title="Target")
    table.add_column("Object", justify="left")
    table.add_column("Value", justify="left")
    table.add_row(_target[0], _target[1])
    return table


def display_applied_rules(_applied_rules):
    table = Table(title="Applied Rules")
    table.add_column("Rule", justify="center")
    for rule in _applied_rules:
        table.add_row(rule)
    return table


def display_iteration_logs(_iteration_logs):
    table = Table(title="Iteration Logs")
    table.add_column("Log Entry", justify="left")
    for log in _iteration_logs:
        table.add_row(log)
    return table


def display_help():
    help_table = Table(title="Help Instructions")
    help_table.add_column("Action", justify="left")
    help_table.add_column("Description", justify="left")
    help_table.add_row("1", "Run Inference")
    help_table.add_row("2", "Add Fact")
    help_table.add_row("3", "Edit Fact")
    help_table.add_row("4", "Remove Fact")
    help_table.add_row("5", "Clear Facts")
    help_table.add_row("6", "Open Rules Editor")
    help_table.add_row("7", "Edit Target")
    help_table.add_row("8", "Exit")
    return help_table


def run():
    console = Console()
    rules_file = "bz.txt"
    target = ("бумага", "текст")

    rules = load_rules(rules_file)
    facts = load_start_values("start_val.txt")

    while True:
        console.clear()
        console.print(Panel("Expert System TUI"), justify="center")

        facts_table = display_facts(facts)
        target_table = display_target(target)
        help_table = display_help()

        columns = Columns([facts_table, target_table, help_table])
        console.print(columns)

        action = Prompt.ask(
            "Choose an action ",
            choices=["1", "2", "3", "4", "5", "6", "7", "8"],
        )

        if action == "1":
            applicable, applied_rules = reverse_inference(rules, target, facts)
            if not applicable:
                console.print(
                    "No applicable rules. Please add new facts.", style="bold red"
                )
            else:
                console.print(
                    f"'{target[0]} = {target[1]}' achieved!", style="bold green"
                )
                print("\nApplied facts:")
                console.print(display_facts(facts))

                print("\nWe pass the following rules:")
                rule_count = 0
                for rule in applied_rules:
                    rule_count += 1
                    print(f"{rule_count}. {rule}")
                    input("Press Enter to continue...")

        elif action == "2":
            obj = Prompt.ask("Enter fact name")
            val = Prompt.ask("Enter fact value")
            if obj and val:
                facts[obj] = val
            else:
                console.print(
                    "Error: Both object and value must be provided.", style="bold red"
                )

        elif action == "3":
            obj = Prompt.ask("Enter fact name to edit")
            if obj in facts:
                val = Prompt.ask("Enter new fact value")
                facts[obj] = val
            else:
                console.print("Error: Fact not found.", style="bold red")

        elif action == "4":
            obj = Prompt.ask("Enter fact name to remove")
            if obj in facts:
                del facts[obj]
            else:
                console.print("Error: Fact not found.", style="bold red")

        elif action == "5":
            facts.clear()

        elif action == "6":
            try:
                subprocess.call(["kitty -e nvim bz.txt"], shell=True)
            except FileNotFoundError:
                console.print("Error: rules.py file not found.", style="bold red")

        elif action == "7":
            obj = Prompt.ask("Enter target object", default=target[0])
            val = Prompt.ask("Enter new target value", default=target[1])
            target = (obj, val)

        elif action == "8":
            break


if __name__ == "__main__":
    run()
