from database.database import Database
from domain.domain import Container


def get_containers(database: Database) -> list[Container]:
    try:
        containers = database.get_containers()
        return containers
    except Exception as e:
        print(f"error {e}, when trying to get containers from database to controller")
        return []


def change_containers(database: Database, container_id: int, new_fluid_id: int) -> bool:
    try:
        return database.change_containers(container_id, new_fluid_id)
    except Exception as e:
        print(f"error {e}, when trying to change containers via controller")
        raise

