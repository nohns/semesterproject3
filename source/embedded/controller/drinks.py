from database.database import Database
from  netlink.publisher import NetlinkPublisher
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


def pour_drink(database: Database, hardware: NetlinkPublisher, drink_id: int):
    try:
        #database.pour_drink()
        hardware.pour_fluid(1, 5)

        return None
    except Exception as e:
        print(f"error {e}, when trying to pour drink via controller")
        raise Exception("fix the issue", e) from e


def create_drink(database: Database, data: Request) -> None:
    try:
        drink = json_to_dataclass(data, Drink)
        database.create_drink(drink)
    except Exception as e:
        print(f"error {e}, when trying to create drink via controller")


def delete_drink(database: Database, drink_id: int) -> bool:
    try:
        database.delete_drink(drink_id)
        return 1
    except Exception as e:
        print(f"error {e}, when trying to delete drink via controller")
        raise Exception("fix the issue", e) from e
