import sqlite3

from database.update import update, set_status_to_true
from database.containers import change_containers, get_containers
from database.drinks import create_drink, delete_drink, get_drinks, pour_drink
from database.fluids import get_fluids, create_fluid, delete_fluid
from database.images import get_images

from domain.domain import Drink, Fluid, Image, FluidContainer


# Call database class
class Database:
    connection: sqlite3.Connection

    def __init__(self):
        print("Database initialized")
        self.connection = sqlite3.connect("database.db", check_same_thread=False)

        # Create the tables
        self.create_tables()

        self.print_all_tables()

    def create_tables(self):
        # create a boolean table for update
        cursor = self.connection.cursor()

        cursor.execute(
            """
    CREATE TABLE IF NOT EXISTS updates 
    (
        status BOOLEAN NOT NULL
    )
    """
        )
        # create a table for containers
        cursor.execute(
            """
    CREATE TABLE IF NOT EXISTS FluidContainers 
    (
        container_id INTEGER PRIMARY KEY,
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
        id INTEGER PRIMARY KEY,
        name TEXT NOT NULL,
        amount_in_cl INTEGER CHECK(amount_in_cl BETWEEN 0 AND 100) NOT NULL,
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
        id INTEGER PRIMARY KEY,
        name TEXT NOT NULL
    )
    """
        )
        # create a table for images
        cursor.execute(
            """
    CREATE TABLE IF NOT EXISTS Images 
    (
        id INTEGER PRIMARY KEY,
        path TEXT NOT NULL
    )
    """
        )
        # create a table for ingredients
        cursor.execute(
            """
    
    CREATE TABLE IF NOT EXISTS Ingredients 
    (
        id INTEGER PRIMARY KEY,
        amount_in_cl INTEGER NOT NULL,
        fluid_id INTEGER NOT NULL,
        drink_id INTEGER NOT NULL, 
        FOREIGN KEY (fluid_id) REFERENCES Fluids(id)
        FOREIGN KEY (drink_id) REFERENCES Drinks(id)
    )
    """
        )

        # Close the cursor again
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

    def change_containers(
        self, container_id: int, fluid_type_id: int, fluid_amount: int
    ):
        return change_containers(self.connection, id)

    def get_containers(self) -> FluidContainer:
        return get_containers(self.connection)

    def create_drink(self, drink: Drink) -> None:
        return create_drink(self.connection, drink)

    def delete_drink(self, id: int) -> None:
        return delete_drink(self.connection)

    def get_drinks(self) -> list[Drink]:
        return get_drinks(self.connection)

    def pour_drink(self, id: int) -> None:
        return pour_drink(self.connection, id)

    def get_fluids(self) -> list[Fluid]:
        return get_fluids(self.connection)

    def create_fluid(self, fluid: Fluid) -> None:
        return create_fluid(self.connection, fluid)

    def delete_fluid(self, id: int) -> None:
        return delete_fluid(self.connection, id)

    def get_images(self) -> list[Image]:
        return get_images(self.connection)

    def update(self) -> bool:
        return update(self.connection)

    # This function is just there for now I think it has some purpose
    def set_status_to_true(self):
        return set_status_to_true(self.connection)
