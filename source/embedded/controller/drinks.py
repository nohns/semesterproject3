from database.database import Database
from domain.domain import Drink


def create_drink(
    database: Database, image_path: str, name: str, ingredients: list
) -> int:
    drink = Drink(
        image=image_path, name=name, ingredients=ingredients, amount_in_cl=0, id=None
    )
    return database.create_drink(drink)


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
