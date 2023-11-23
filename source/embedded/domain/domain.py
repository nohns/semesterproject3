from dataclasses import dataclass, fields, is_dataclass, MISSING


# Define a function to convert a JSON object to a data class instance
def json_to_dataclass(json_data, dataclass_type):
    try:
        # Check if the provided type is indeed a dataclass
        if not is_dataclass(dataclass_type):
            raise TypeError("Provided type is not a dataclass.")

        # Get the dataclass fields and their default values
        defaults = {
            field.name: field.default
            for field in fields(dataclass_type)
            if field.default is not MISSING
        }

        # Update the defaults with the actual json data
        defaults.update(json_data)

        # Create the dataclass instance
        return dataclass_type(**defaults)
    except Exception as e:
        print(e)
        raise ValueError(f"Error converting JSON to dataclass: {str(e)}") from e


# Domain classes
@dataclass
class Fluid:
    name: str
    id: int = None


@dataclass
class Ingredient:
    fluid: Fluid
    amountInCl: int
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
class Container:
    fluid_amount_in_cl: int
    fluid: Fluid
    container_id: int = None


# @dataclass
# class Statistics:
#    amount_poured: int
#    pour_duration: int
#    error: str
#    timestamp: str """
