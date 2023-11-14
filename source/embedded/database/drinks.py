import sqlite3
from domain.domain import Drink

# Tvivler sgu på den her kommer til at virke
# At dette virker vil kræve vi får ingredient information


def get_drinks(connection: sqlite3.Connection) -> list[Drink]:
    cursor = connection.cursor()

    try:
        # Fetch drinks along with their images
        cursor.execute(
            """
            SELECT Drinks.id, Drinks.name, Drinks.amount_in_cl, Images.path
            FROM Drinks LEFT JOIN Images ON Drinks.image_id = Images.id
        """
        )
        drinks_data = cursor.fetchall()

        # create list of drinks class objects

        drinks = []
        for drink_data in drinks_data:
            drink_id, name, amount_in_cl, image_path = drink_data

            # Fetch ingredients associated with each drink
            cursor.execute(
                """
                SELECT Ingredients.amount_in_cl, Fluids.name
                FROM Ingredients JOIN Fluids ON Ingredients.fluid_id = Fluids.id
                WHERE Ingredients.drink_id = ?
            """,
                (drink_id,),
            )
            ingredients_data = cursor.fetchall()

            ingredients = [
                {"amount_in_cl": amount, "name": name}
                for amount, name in ingredients_data
            ]

            # Building the drink object
            drink = {
                "id": drink_id,
                "name": name,
                "amount_in_cl": amount_in_cl,
                "image_path": image_path,
                "ingredients": ingredients,
            }
            drinks.append(drink)

        return drinks

    except sqlite3.Error as e:
        print(f"SQLite error: {e}")
        return None

    finally:
        cursor.close()


def pour_drink(connection: sqlite3.Connection) -> None:
    # TODO: Implement
    return 0


def create_drink(connection: sqlite3.Connection, drink: Drink) -> None:
    cursor = connection.cursor()
    try:
        print("Trying to do the thing")

        # Create array to hold the result
        ingredient_array = []
        print("Printing drink object: ", drink)

        # append the ingredients to the array
        for ingredient in drink.ingredients:
            ingredient_array.append(ingredient["fluid"]["id"])

        print("Printing ingredient array: ", ingredient_array)
        # convert the array to a string seperated by commas
        result_string = ",".join(map(str, ingredient_array))
        print(result_string)

        # Associate ingredients with the new drink using their existing IDs, think we have to do this
        for ingredient in drink.ingredients:
            # I need to create a text string seperated by commas which is an array of the ingredients ids
            cursor.execute(
                "INSERT INTO Ingredients (amount_in_cl, fluid_id) VALUES (?, ?)",
                (ingredient["amountInCl"], ingredient["fluid"]["id"]),
            )
        print("Added ingredients")

        # Insert into Drinks table using the existing image_id since we can't directly insert the image object
        print(drink.name)
        print(drink.image["id"])
        cursor.execute(
            "INSERT INTO Drinks (name, ingredients_ids, image_id) VALUES (?, ?, ?)",
            (drink.name, result_string, drink.image["id"]),
        )
        print("Added drink")

        connection.commit()
        print("Committed")

    except sqlite3.Error as e:
        print(f"An error occurred: {e}")
        connection.rollback()
        raise Exception("An error occurred while creating the drink.", e)

    finally:
        cursor.close()


def delete_drink(connection: sqlite3.Connection, drink_id: int) -> bool:
    cursor = connection.cursor()

    try:
        cursor.execute("DELETE FROM Ingredients WHERE drink_id = ?", (drink_id,))
        cursor.execute("DELETE FROM Drinks WHERE id = ?", (drink_id,))

        connection.commit()

    except sqlite3.Error as e:
        print(f"An error occurred: {e}")
        connection.rollback()

    finally:
        cursor.close()
