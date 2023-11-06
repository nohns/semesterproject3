from database.database import Database
from domain.domain import Drink


def create_drink(database: Database) -> None:
    return 0


def delete_drink(id: int, database: Database) -> None:
    try:
        database.delete_drink(id)
        return 1
    except Exception as e:
        print(f"error {e}, when trying to delete drink via controller")
        return None


def get_drinks(database: Database) -> list[Drink]:
    try:
        drinks = database.get_drinks()
        return drinks
    except Exception as e:
        print(f"error {e}, when requesting drinks from database to controller")
        return None


def pour_drink(database: Database):
    return 0
