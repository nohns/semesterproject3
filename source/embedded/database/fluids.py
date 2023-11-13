import sqlite3
from domain.domain import Fluid

    
def get_fluids(connection: sqlite3.Connection)-> list[Fluid] :
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
