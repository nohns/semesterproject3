from dataclasses import dataclass
import dataclasses
from typing import Optional
from types import SimpleNamespace

import json

# Define a function to convert a JSON object to a data class instance
def json_to_dataclass(json_data, dataclass_type):
    # Get the dataclass fields and their default values
    defaults = {f.name: f.default for f in dataclass_type.__dataclass_fields__.values() if f.default is not dataclasses._MISSING_TYPE}
    # Update the defaults with the actual json data
    defaults.update(json_data)
    # Create the dataclass instance
    return dataclass_type(**defaults)

# Domain classes
@dataclass
class Fluid:
    id: int
    name: Optional[str]

@dataclass
class Ingredient:
    id: Optional[int]
    amount_in_cl: int
    fluid: Fluid

@dataclass
class Image:
    id: int
    path: str

@dataclass
class Drink:
    id: Optional[int]
    name: str
    image: Image
    ingredients: list[Ingredient]

@dataclass
class FluidContainer:
    container_id: int
    fluid_amount_in_cl: int
    fluid_type: Fluid


json_data = '''{
    "image": {
        "id": 1,
        "path": "https://i.imgur.com/5qkN7eN.png"
    },
    "name": "blå vand",
    "ingredients": [
      {
        "id": 1,
        "amountInCl": 10,
        "fluid": {
          "id": 1
        }
      },
      {
        "id": 2,
        "amountInCl": 25,
        "fluid": {
          "id": 2
        }
      }
    ]
}'''

# Parse the JSON data into a data class instance
drink = json_to_dataclass(json.loads(json_data), Drink)

# Printing the Drink object
print(drink)

""" @dataclass
class Statistics:
    amount_poured: int
    pour_duration: int
    error: str
    timestamp: str """