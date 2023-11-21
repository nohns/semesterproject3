from database.database import Database


def get_containers(database: Database) -> dict:
    try:
        containers = database.get_containers()
        return {
            "containers": containers
        }  # Wrap the list in a dictionary with the key 'containers'
    except Exception as e:
        print(f"error {e}, when trying to get containers from database to controller")
        raise Exception("Unable to get containers") from e


def change_containers(database: Database, container_id: int, new_fluid_id: int) -> bool:
    try:
        return database.change_containers(container_id, new_fluid_id)
    except Exception as e:
        print(f"error {e}, when trying to change containers via controller")
        raise
