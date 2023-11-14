from dataclasses import dataclass
from typing import Optional
import dataclasses

import json


# Define a function to convert a JSON object to a data class instance
def json_to_dataclass(json_data, dataclass_type):
    try:
        # Get the dataclass fields and their default values
        defaults = {
            f.name: f.default
            for f in dataclass_type.__dataclass_fields__.values()
            if f.default is not dataclasses._MISSING_TYPE
        }
        # Update the defaults with the actual json data
        defaults.update(json_data)
        # Create the dataclass instance
        return dataclass_type(**defaults)
    except Exception as e:
        print(e)
        raise ValueError(f"Error converting JSON to dataclass: {str(e)}")


# Domain classes
@dataclass
class Fluid:
    name: str
    id: int = None


@dataclass
class Ingredient:
    amountInCl: int
    fluid: Fluid
    id: int = None


@dataclass
class Image:
    path: str
    id: int = None


@dataclass
class Drink:
    name: str
    image: Image
    ingredients: list[Ingredient]
    id: int = None


@dataclass
class FluidContainer:
    fluid_amount_in_cl: int
    fluid: Fluid
    container_id: int = None


# @dataclass
# class Statistics:
#    amount_poured: int
#    pour_duration: int
#    error: str
#    timestamp: str """
