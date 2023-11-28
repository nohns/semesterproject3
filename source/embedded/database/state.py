import sqlite3
import time

def trigger_state_update(connection: sqlite3.Connection) -> None:
    cursor = connection.cursor()

    try:
        print(f"Database: Attempting to trigger state update")
        curr_time_ms = int(round(time.time() * 1000))
        cursor.execute("UPDATE State SET int_value = 1 WHERE key = 'last_update'", (curr_time_ms))
        connection.commit()

    except sqlite3.Error as e:
        print(f"SQLite error: {e}")
        connection.rollback()
        raise Exception("An error occurred while triggering update.", e) from e

    finally:
        cursor.close()

def set_state_out_of_order(connection: sqlite3.Connection, message: str, reason: int) -> None:
    cursor = connection.cursor()

    try:
        print(f"Database: Attempting to update out of order state with msg: {message}")
        curr_time_ms = int(round(time.time() * 1000))

        # Update last update time + set out of order
        cursor.execute("UPDATE State SET int_value = ? WHERE key = 'last_update'", (curr_time_ms,))
        cursor.execute("UPDATE State SET int_value = 1 WHERE key = 'out_of_order'")
        cursor.execute("UPDATE State SET str_value = ? WHERE key = 'out_of_order_message'", (message,))
        cursor.execute("UPDATE State SET int_value = ? WHERE key = 'out_of_order_reason'", (reason,))
        connection.commit()

    except sqlite3.Error as e:
        print(f"SQLite error: {e}")
        connection.rollback()
        raise Exception("An error occurred while creating the fluid.", e) from e

    finally:
        cursor.close()

def clear_state_out_of_order(connection: sqlite3.Connection) -> None:
    cursor = connection.cursor()

    try:
        print(f"Database: Attempting to clear out of order state")
        curr_time_ms = int(round(time.time() * 1000))

         # Update last update time + clear out of order state
        cursor.execute("UPDATE State SET int_value = ? WHERE key = 'last_update'", (curr_time_ms,))
        cursor.execute("UPDATE State SET int_value = 0 WHERE key = 'out_of_order'")
        cursor.execute("UPDATE State SET str_value = '' WHERE key = 'out_of_order_message'")
        cursor.execute("UPDATE State SET int_value = 0 WHERE key = 'out_of_order_reason'")
        connection.commit()

    except sqlite3.Error as e:
        print(f"SQLite error: {e}")
        connection.rollback()
        raise Exception("An error occurred while creating the fluid.", e) from e

    finally:
        cursor.close()


def get_state(connection: sqlite3.Connection) -> dict:
    cursor = connection.cursor()

    try:
        print(f"Database: Attempting to read state")
        cursor.execute("SELECT * FROM State")
        state_data = cursor.fetchall()

        state = {}
        for (key, int_value, str_value) in state_data:
            state[key] = int_value if int_value != None else str_value

        print(f"Database: Read state: {state}")

        return state

    except sqlite3.Error as e:
        print(f"SQLite error: {e}")
        return None

    finally:
        cursor.close()
