import sqlite3
from domain.domain import Fluid


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


def create_fluid(connection: sqlite3.Connection, fluid: Fluid) -> None:
    cursor = connection.cursor()

    try:
        print(f"Database: Attempting to create fluid: {fluid}")
        # Check if a fluid with identical name already exists
        all_fluids = get_fluids(connection)

        if any(fluid.name == existing_fluid["name"] for existing_fluid in all_fluids):
            print(f"Database: '{fluid.name}' already exists")
            return

        cursor.execute("INSERT INTO Fluids (name) VALUES (?)", (fluid.name,))

        connection.commit()

    except sqlite3.Error as e:
        print(f"SQLite error: {e}")
        connection.rollback()
        raise Exception("An error occurred while creating the fluid.", e) from e

    finally:
        cursor.close()


def delete_fluid(connection: sqlite3.Connection, fluid_id: int) -> bool:
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
