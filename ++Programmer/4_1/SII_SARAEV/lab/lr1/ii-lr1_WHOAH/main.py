import subprocess

from rich.columns import Columns
from rich.console import Console
from rich.panel import Panel
from rich.prompt import Prompt
from rich.table import Table


# Functions for working with rules and facts
def load_rules(file_path):
    rules = []
    with open(file_path, "r", encoding="utf-8") as file:
        for line in file:
            if line.strip():
                condition, result = line.strip().split(" ТО ")
                conditions = condition.replace("ЕСЛИ ", "").split(" И ")
                result_actions = result.split(" И ")
                rules.append((conditions, result_actions))
    return rules


def load_start_values(file_path):
    facts = {}
    with open(file_path, "r", encoding="utf-8") as file:
        for line in file:
            key, value = line.strip().split(": ")
            facts[key] = value
    return facts


def check_conditions(conditions, facts):
    for condition in conditions:
        obj, val = condition.split("=")
        if facts.get(obj, "").lower() != val.lower():
            return False
    return True


# Inference engine
def inference_engine(rules, facts):
    applied_rules = []
    applicable = False
    for conditions, result_actions in rules:
        if check_conditions(conditions, facts):
            for action in result_actions:
                if action.startswith("удалить="):
                    obj_to_remove = action.split("=")[1]
                    if obj_to_remove in facts:
                        del facts[obj_to_remove]
                        applied_rules.append(f"{conditions} -> удалить={obj_to_remove}")
                else:
                    result_obj, result_val = action.split("=")
                    if facts.get(result_obj) != result_val:
                        facts[result_obj] = result_val
                        applied_rules.append(
                            f"{conditions} -> {result_obj} = {result_val}"
                        )
            applicable = True
            break  # Execute only one condition at a time
    return facts, applied_rules, applicable


# Display facts table
def display_facts(console, facts):
    table = Table(title="Facts")
    table.add_column("Object", justify="left")
    table.add_column("Value", justify="left")
    for obj, val in facts.items():
        table.add_row(obj, val)
    return table


# Display rules
def display_rules(console, applied_rules):
    table = Table(title="Applied Rules")
    table.add_column("Rule", justify="center")
    for rule in applied_rules:
        table.add_row(rule)
    return table


# Display help instructions
def display_help(console):
    help_table = Table(title="Help Instructions")
    help_table.add_column("Action", justify="left")
    help_table.add_column("Description", justify="left")
    help_table.add_row("1", "Run Inference")
    help_table.add_row("2", "Add Fact")
    help_table.add_row("3", "Edit Fact")
    help_table.add_row("4", "Remove Fact")
    help_table.add_row("5", "Clear Facts")
    help_table.add_row("6", "Open Rules Editor")
    help_table.add_row("7", "Exit")
    return help_table


# Clear facts and rules
def clear_facts(facts):
    facts.clear()


# TUI interface
def run():
    console = Console()
    rules_file = "bz.txt"
    rules = load_rules(rules_file)
    facts = load_start_values("start_val.txt")

    while True:
        console.clear()
        console.print(Panel("Expert System TUI"), justify="center")

        facts_table = display_facts(console, facts)
        help_table = display_help(console)

        columns = Columns([facts_table, help_table])
        console.print(columns)

        action = Prompt.ask(
            "Choose an action ",
            choices=["1", "2", "3", "4", "5", "6", "7", "8"],
        )

        if action == "1":
            facts, applied_rules, applicable = inference_engine(rules, facts)
            console.print(facts_table)
            console.print(display_rules(console, applied_rules))
            if not applicable:
                console.print(
                    "No applicable rules. Please add new facts.", style="bold red"
                )

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
            clear_facts(facts)

        elif action == "6":
            try:
                subprocess.call(["kitty -e nvim bz.txt"], shell=True)
            except FileNotFoundError:
                console.print("Error: rules.py file not found.", style="bold red")

        elif action == "7":
            break


if __name__ == "__main__":
    run()
