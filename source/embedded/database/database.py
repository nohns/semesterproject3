import sqlite3

from database.update import update, set_status_to_true
from database.containers import change_containers, get_containers
from database.drinks import create_drink, delete_drink, get_drinks, pour_drink
from database.fluids import get_fluids, create_fluid, delete_fluid
from database.images import get_images

 #Call database class
class Database:
    connnection: sqlite3.Connection

    def __init__(self):
        print("Database initialized")
        self.connection = sqlite3.connect('database.db', check_same_thread=False)

        #Create the tables
        self.create_tables()

        self.print_all_tables()

    def create_tables(self):
        #create a boolean table for update
        cursor = self.connection.cursor()
     
        cursor.execute(
         """
    CREATE TABLE IF NOT EXISTS updates 
    (
        status BOOLEAN NOT NULL
    )
    """
                    )
        #create a table for containers
        cursor.execute("")

        #create a table for drinks
        cursor.execute("")
        #create a table for fluids
        cursor.execute("")
        #create a table for images
        cursor.execute("")

        #Close the cursor again
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

    def change_containers(self, id: int):
        return change_containers(id, self.connection)
    
    def get_containers(self):
        return get_containers(self.connection)
    
    def create_drink(self):
        return create_drink(self.connection)
    
    def delete_drink(self):
        return delete_drink(self.connection)
    
    def get_drinks(self):
        return get_drinks(self.connection)
    
    def pour_drink(self):
        return pour_drink(self.connection)
    
    def get_fluids(self):
        return get_fluids(self.connection)
    
    def create_fluid(self):
        return create_fluid(self.connection)
    
    def delete_fluid(self):
        return delete_fluid(self.connection)
    
    def get_images(self):
        return get_images(self.connection)
       
    def update(self):
        return update(self.connection)

    def set_status_to_true(self):
        return set_status_to_true(self.connection)