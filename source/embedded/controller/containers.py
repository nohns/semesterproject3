from database.database import Database
from domain.domain import FluidContainer


def get_containers(database: Database) -> list[FluidContainer]:
    try:
        containers = database.get_containers()
        return containers
    except Exception as e:
        print(f"error {e}, when trying to get containers from database to controller")
        return None


def change_containers(database: Database, id: int) -> None:
    try:
        # database.change_containers(id)
        return None
    except Exception as e:
        print(f"error {e}, when trying to change containers via controller")
        raise Exception("fix the issue", e)
