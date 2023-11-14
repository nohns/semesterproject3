from database.database import Database
from domain.domain import Drink


def get_drinks(database: Database) -> list[Drink]:
    try:
        drinks = database.get_drinks()
        return drinks
    except Exception as e:
        print(f"error {e}, when requesting drinks from database to controller")
        raise Exception("fix the issue", e)


def pour_drink(database: Database):
    try:
        database.pour_drink()
        return None
    except Exception as e:
        print(f"error {e}, when trying to pour drink via controller")
        raise Exception("fix the issue", e)


def create_drink(database: Database, drink: Drink) -> None:
    try:
        database.create_drink(drink)
    except Exception as e:
        print(f"error {e}, when trying to create drink via controller")

        raise Exception("Something went to shit fix this error mesg if you find it", e)


def delete_drink(id: int, database: Database) -> bool:
    try:
        database.delete_drink(id)
        return 1
    except Exception as e:
        print(f"error {e}, when trying to delete drink via controller")
        raise Exception("fix the issue", e)
