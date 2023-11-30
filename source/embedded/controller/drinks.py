from database.database import Database
from netlink.publisher import NetlinkPublisher
from domain.domain import Drink, json_to_dataclass
from flask import Request
from netlink.publisher import NetlinkPublisher


def get_drinks(database: Database) -> dict:
    try:
        drinks = database.get_drinks()
        return {"drinks": drinks}  # Wrap the list in a dictionary
    except Exception as e:
        print(f"error {e}, when requesting drinks from database to controller")
        raise Exception("Unable to get drinks") from e


def get_drink_for_netlink(database: Database, drink_id: int) -> dict:
    try:
        drink = database.get_drink(drink_id)
        return {"drink": drink}
    except Exception as e:
        print(f"error {e}, when requesting drink from database to controller")
        raise Exception("Unable to get drink") from e


def pour_drink(database: Database, hardware: NetlinkPublisher, drink_id: int):
    try:
        print(f"Controller: Attempting to pour drink with drink id: {drink_id}")
        drink = database.get_drink_by_id(drink_id)
        for ingredient in drink.ingredients:
            container = database.get_container_by_fluid_id(ingredient.fluid.id)
            hardware.pour_fluid(container.container_id, ingredient.amountInCl)

        return None
    except Exception as e:
        print(f"error {e}, when trying to pour drink via controller")
        raise Exception("fix the issue", e) from e


def create_drink(database: Database, data: Request) -> None:
    try:
        drink = json_to_dataclass(data, Drink)
        database.create_drink(drink)
        database.trigger_state_update()
    except Exception as e:
        print(f"error {e}, when trying to create drink via controller")


def delete_drink(database: Database, drink_id: int) -> bool:
    try:
        database.delete_drink(drink_id)
        database.trigger_state_update()
        return 1
    except Exception as e:
        print(f"error {e}, when trying to delete drink via controller")
        raise Exception("fix the issue", e) from e
