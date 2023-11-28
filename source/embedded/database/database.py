import sqlite3

# using time module
import time
from database.update import update, set_status_to_true
from database.containers import (
    change_containers,
    get_containers,
    get_container_by_fluid_id,
)
from database.drinks import (
    create_drink,
    delete_drink,
    get_drinks,
    get_drink_by_id,
)  # , pour_drink
from database.fluids import get_fluids, create_fluid, delete_fluid
from database.images import get_images
from database.state import *

from domain.domain import Drink, Fluid, Image, Container


# Call database class
class Database:
    connection: sqlite3.Connection

    def __init__(self):
        print("Database initialized")
        self.connection = sqlite3.connect("database.db", check_same_thread=False)

        # Create the tables
        self.create_tables()

        # Seed the tables
        # self.seed_fluids()
        self.seed_state()
        self.seed_containers()

        self.print_all_tables()

        from sample_data import fluids, drinks

        print("Adding sample data to database")
        for fluid in fluids:
            create_fluid(self.connection, fluid)
        for drink in drinks:
            create_drink(self.connection, drink)

    def create_tables(self):
        # Create a boolean table for update
        cursor = self.connection.cursor()

        cursor.execute(
            """
    CREATE TABLE IF NOT EXISTS state 
    (
        key TEXT PRIMARY KEY,
        str_value TEXT,
        int_value INTEGER
    )
    """
        )

        # create a table for containers
        cursor.execute(
            """
    CREATE TABLE IF NOT EXISTS Containers 
    (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        fluid_amount_in_cl INTEGER NOT NULL,
        fluid_type_id INTEGER NOT NULL,
        FOREIGN KEY (fluid_type_id) REFERENCES Fluids(id)
    )
    """
        )
        # create a table for drinks
        cursor.execute(
            """
    CREATE TABLE IF NOT EXISTS Drinks 
    (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        name TEXT NOT NULL,
        ingredients_ids TEXT,
        image_id INTEGER,
        FOREIGN KEY (image_id) REFERENCES Images(id)
    )
    """
        )
        # create a table for fluids
        cursor.execute(
            """
    CREATE TABLE IF NOT EXISTS Fluids 
    (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        name TEXT NOT NULL
    )
    """
        )
        # create a table for images
        cursor.execute(
            """
    CREATE TABLE IF NOT EXISTS Images 
    (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        path TEXT NOT NULL
    )
    """
        )
        # create a table for ingredients
        cursor.execute(
            """
    
    CREATE TABLE IF NOT EXISTS Ingredients 
    (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        fluid_id INTEGER NOT NULL,
        amount_in_cl INTEGER NOT NULL,
        FOREIGN KEY (fluid_id) REFERENCES Fluids(id)
    )
    """
        )

    def seed_fluids(self):
        cursor = self.connection.cursor()
        try:
            # Check if fluids already seeded
            cursor.execute("SELECT COUNT(*) FROM Fluids")
            if cursor.fetchone()[0] == 0:  # If no fluids, then seed
                fluids = [
                    "Vodka",
                    "Orange Juice",
                    "Blue Booster",
                ]  # Example fluid names
                for fluid in fluids:
                    cursor.execute("INSERT INTO Fluids (name) VALUES (?)", (fluid,))
                self.connection.commit()
        except sqlite3.Error as e:
            print(f"SQLite error: {e}")
            self.connection.rollback()
        finally:
            cursor.close()

    def seed_containers(self):
        cursor = self.connection.cursor()
        try:
            # Check if containers already seeded
            cursor.execute("SELECT COUNT(*) FROM Containers")
            if cursor.fetchone()[0] == 0:  # If no containers, then seed
                fluid_ids = [1, 2, 3]  # Replace with actual fluid IDs if different
                for fluid_id in fluid_ids:
                    cursor.execute(
                        "INSERT INTO Containers (fluid_amount_in_cl, fluid_type_id) VALUES (?, ?)",
                        (100, fluid_id),
                    )
                self.connection.commit()
        except sqlite3.Error as e:
            print(f"SQLite error: {e}")
            self.connection.rollback()
        finally:
            cursor.close()

    def seed_state(self):
        print("Seeding state")
        cursor = self.connection.cursor()
        try:
            curr_time_ms = int(time.time() * 1000)
            print(f"curr time: {curr_time_ms} ms og type {type(curr_time_ms)}")
            # Check if fluids already seeded
            cursor.execute("SELECT COUNT(*) FROM State")
            
            count = cursor.fetchone()[0]
           
            if count == 0:  # If no state, then seed
                cursor.execute("INSERT INTO State (key, int_value) VALUES ('last_update', ?)", (curr_time_ms,))
                cursor.execute("INSERT INTO State (key, int_value) VALUES ('out_of_order', 0)")
                cursor.execute("INSERT INTO State (key, str_value) VALUES ('out_of_order_message', '')")
                cursor.execute("INSERT INTO State (key, int_value) VALUES ('out_of_order_reason', 0)")

                self.connection.commit()
        except sqlite3.Error as e:
            print(f"SQLite error: {e}")
            self.connection.rollback()
        finally:
            cursor.close()

    def print_all_tables(self):
        try:
            cursor = self.connection.cursor()

            # Get the list of tables in the database
            cursor.execute("SELECT name FROM sqlite_master WHERE type='table';")
            tables = cursor.fetchall()

            if tables:
                print("Tables in the database:")
                for table in tables:
                    table_name = table[0]
                    print(table_name)
            else:
                print("No tables found in the database.")

            # Close the cursor and connection
            cursor.close()

        except sqlite3.Error as e:
            print("SQLite error:", e)

    def change_containers(self, container_id: int, new_fluid_id: int) -> bool:
        return change_containers(self.connection, container_id, new_fluid_id)

    def get_containers(self) -> list[Container]:
        return get_containers(self.connection)

    def get_container_by_fluid_id(self, fluid_id: int) -> Container:
        return get_container_by_fluid_id(self.connection, fluid_id)

    def create_drink(self, drink: Drink) -> None:
        return create_drink(self.connection, drink)

    def delete_drink(self, drink_id: int) -> None:
        return delete_drink(self.connection, drink_id)

    def get_drinks(self) -> list[Drink]:
        return get_drinks(self.connection)

    def get_drink_by_id(self, drink_id: int) -> Drink:
        return get_drink_by_id(self.connection, drink_id)

    # def pour_drink(self, id: int) -> None:
    #     return pour_drink(self.connection, id)

    def get_fluids(self) -> list[Fluid]:
        return get_fluids(self.connection)

    def create_fluid(self, fluid: Fluid) -> None:
        return create_fluid(self.connection, fluid)

    def delete_fluid(self, fluid_id: int) -> bool:
        return delete_fluid(self.connection, fluid_id)

    def get_images(self) -> list[Image]:
        return get_images(self.connection)

    def update(self) -> bool:
        return update(self.connection)
    
    def get_state(self) -> dict:
        return get_state(self.connection)
    
    def set_state_out_of_order(self, message: str, reason: int) -> None:
        return set_state_out_of_order(self.connection, message, reason)
    
    def clear_state_out_of_order(self) -> None:
        return clear_state_out_of_order(self.connection)