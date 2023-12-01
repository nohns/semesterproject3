from database.database import Database
from domain.domain import Fluid, json_to_dataclass
from flask import Request


def get_fluids(database: Database) -> dict:
    try:
        print("Controller: Attempting to get fluids")
        fluids = database.get_fluids()
        return {"fluids": fluids}  # Wrap the list in a dictionary with the key 'fluids'
    except Exception as e:
        print(f"error {e}, when trying to get fluids via controller")
        raise Exception("Unable to get fluids", e) from e


def create_fluid(database: Database, data: Request) -> None:
    try:
        print(f"Controller: Attempting to create fluid with json data: {data}")
        fluid = json_to_dataclass(data, Fluid)
        print(fluid)
        database.create_fluid(fluid)
        database.trigger_state_update()
    except Exception as e:
        print(f"error {e}, when trying to create fluid via controller")
        raise Exception("Unable to create fluid", e) from e


def delete_fluid(database: Database, fluid_id: int) -> bool:
    try:
        print(f"Controller: Attempting to delete fluid with fluid id: {fluid_id}")
        database.delete_fluid(fluid_id)
        database.trigger_state_update()
    except Exception as e:
        print(f"error {e}, when trying to delete fluid via controller")
        raise Exception("Unable to delete fluid", e) from e
