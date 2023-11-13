import sqlite3
from domain.domain import Drink

#Tvivler sgu på den her kommer til at virke
#At dette virker vil kræve vi får ingredient information



def get_drinks(connection: sqlite3.Connection) -> list[Drink]:
    cursor = connection.cursor()

    try:
        # Fetch drinks along with their images
        cursor.execute("""
            SELECT Drinks.id, Drinks.name, Drinks.amount_in_cl, Images.path
            FROM Drinks LEFT JOIN Images ON Drinks.image_id = Images.id
        """)
        drinks_data = cursor.fetchall()

        #create list of drinks class objects
        


        drinks = []
        for drink_data in drinks_data:
            drink_id, name, amount_in_cl, image_path = drink_data
            
            # Fetch ingredients associated with each drink
            cursor.execute("""
                SELECT Ingredients.amount_in_cl, Fluids.name
                FROM Ingredients JOIN Fluids ON Ingredients.fluid_id = Fluids.id
                WHERE Ingredients.drink_id = ?
            """, (drink_id,))
            ingredients_data = cursor.fetchall()

            ingredients = [{"amount_in_cl": amount, "name": name} for amount, name in ingredients_data]

            # Building the drink object
            drink = {
                "id": drink_id,
                "name": name,
                "amount_in_cl": amount_in_cl,
                "image_path": image_path,
                "ingredients": ingredients
            }
            drinks.append(drink)

        return drinks

    except sqlite3.Error as e:
        print(f"SQLite error: {e}")
        return None

    finally:
        cursor.close()

    
def pour_drink(connection: sqlite3.Connection)-> None:
    #TODO: Implement
    return 0