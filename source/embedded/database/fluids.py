import sqlite3
from domain.domain import Fluid


def create_fluid(connection: sqlite3.Connection, name: str) -> None:
    cursor = connection.cursor()

    try:
        cursor.execute("INSERT INTO Fluids (name) VALUES (?)", (name,))

        fluid_id = cursor.lastrowid

        connection.commit()

        return fluid_id

    except sqlite3.Error as e:
        print(f"SQLite error: {e}")
        connection.rollback()
        return None

    finally:
        cursor.close()


def delete_fluid(connection: sqlite3.Connection, fluid_id: int) -> None:
    cursor = connection.cursor()

    try:
        cursor.execute("DELETE FROM Fluids WHERE id = ?", (fluid_id,))

        if cursor.rowcount > 0:
            connection.commit()
            return True
        else:
            return False

    except sqlite3.Error as e:
        print(f"SQLite error: {e}")
        connection.rollback()
        return False

    finally:
        cursor.close()


def get_fluids(connection: sqlite3.Connection) -> list[Fluid]:
    cursor = connection.cursor()

    try:
        # Query to fetch all records from the Fluids table
        cursor.execute("SELECT * FROM Fluids")
        fluids_data = cursor.fetchall()

        # Creating a list of dictionaries, each representing a fluid
        fluids = [{"id": fluid_id, "name": name} for (fluid_id, name) in fluids_data]

        return fluids  # Returning the list of fluids

    except sqlite3.Error as e:
        print(f"SQLite error: {e}")
        return None  # Return None in case of any error

    finally:
        cursor.close()  # Ensure the cursor is closed
