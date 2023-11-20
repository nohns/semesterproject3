import json
from domain.domain import json_to_dataclass


def load_json_file(file_path, dataclass_type):
    with open(file_path, "r", encoding="utf-8") as file:
        json_data = json.load(file)

    instances = []
    for item in json_data:
        instances.append(json_to_dataclass(item, dataclass_type))

    return instances

