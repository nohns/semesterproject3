from database.database import Database

def get_state(database: Database) -> dict:
    try:
        print("Attempting to get state from database")
        state = database.get_state()
        state["out_of_order"] = state["out_of_order"] == 1
        return state

    except Exception as e:
        print("Failed to get state from database", e)
        raise Exception("Failed to get state from database", e) from e


def set_state_out_of_order(database: Database, message: str, reason: int) -> None:
    try:
        print(f"Controller: Attempting to set state out of order with msg: {message}")
        database.set_state_out_of_order(message, reason)
        return None

    except Exception as e:
        print(f"error {e}, when trying to set state out of order via controller")
        raise Exception("fix the issue", e) from e
    
def clear_state_out_of_order(database: Database) -> None:
    try:
        print(f"Controller: Attempting to clear state out of order")
        database.clear_state_out_of_order()
        return None

    except Exception as e:
        print(f"error {e}, when trying to clear state out of order via controller")
        raise Exception("fix the issue", e) from e