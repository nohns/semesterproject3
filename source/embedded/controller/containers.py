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


def get_container_by_fluid_id(database: Database, fluid_id: int) -> dict:
    try:
        container = database.get_container_by_fluid_id(fluid_id)
        return {"container": container}
    except Exception as e:
        print(f"error {e}, when requesting container from database to controller")
        raise Exception("Unable to get container") from e


def update_container_fluid_amount(
    database: Database, container_id: int, fluid_amount_in_cl: float
) -> bool:
    try:
        database.update_container_fluid_amount(container_id, fluid_amount_in_cl)
        return True
    except Exception as e:
        print(f"error {e}, when updating fluid amount in the database")
        raise Exception("Unable to update fluid amount") from e


def change_containers(database: Database, container_id: int, new_fluid_id: int) -> bool:
    try:
        return database.change_containers(container_id, new_fluid_id)
    except Exception as e:
        print(f"error {e}, when trying to change containers via controller")
        raise
