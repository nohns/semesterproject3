import sqlite3
from domain.domain import Container

def get_containers(connection: sqlite3.Connection)-> list[Container]:
    cursor = connection.cursor()

    try:
        cursor.execute("""
            SELECT Containers.id, Containers.fluid_amount_in_cl, 
                   Fluids.name as fluid_name
            FROM Containers
            LEFT JOIN Fluids ON Containers.fluid_type_id = Fluids.id
        """)
        containers_data = cursor.fetchall()

        # Format the data into a list of dictionaries
        containers = [{
            "container_id": c_id,
            "fluid_amount_in_cl": f_amount,
            "fluid_name": f_name
        } for (c_id, f_amount, f_name) in containers_data]

        return containers

    except sqlite3.Error as e:
        print(f"SQLite error: {e}")
        return None

    finally:
        cursor.close()


    
def change_containers(connection: sqlite3.Connection, container_id: int, new_fluid_id: int) -> bool:
    cursor = connection.cursor()

    try:
        # Update the container with the new fluid type id
        cursor.execute("""
            UPDATE Containers 
            SET fluid_type_id = ?
            WHERE id = ?
        """, (new_fluid_id, container_id))

        connection.commit()

        # Check if the update was successful
        return cursor.rowcount > 0

    except sqlite3.Error as e:
        print(f"SQLite error: {e}")
        connection.rollback()
        return False

    finally:
        cursor.close()

