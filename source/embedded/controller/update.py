from database.database import Database


def update(database: Database) -> bool:
    try:
        print("Attempting to get update from database")
        boolio = database.update()
        print("Update from database: ", boolio)
        return boolio

    except Exception as e:
        print("Failed to get update from database", e)
        raise Exception("Failed to get update from database", e) from e
