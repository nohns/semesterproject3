import sqlite3
from domain.domain import Drink


# Tvivler sgu på den her kommer til at virke
# At dette virker vil kræve vi får ingredient information
def create_drink(connection: sqlite3.Connection, drink: Drink) -> int:
    cursor = connection.cursor()
    print(drink)

    try:
        # Don't know if this should be here, trying to calculate the amount of fluid in the drink from the ingredients
        drink.amount_in_cl = sum(
            [ingredient["amount_in_cl"] for ingredient in drink.ingredients]
        )

        # Insert into Drinks table using the existing image_id since we can't directly insert the image object
        cursor.execute(
            "INSERT INTO Drinks (name, amount_in_cl, image_id) VALUES (?, ?, ?)",
            (drink.name, drink.amount_in_cl, drink.image.id),
        )
        drink_id = cursor.lastrowid

        print("test")

        # Associate ingredients with the new drink using their existing IDs, think we have to do this
        for ingredient in drink.ingredients:
            cursor.execute(
                "INSERT INTO Ingredients (id, amount_in_cl, fluid_id, drink_id) VALUES (?, ?, ?, ?)",
                (
                    ingredient["id"],
                    ingredient["amount_in_cl"],
                    ingredient["fluid"],
                    drink_id,
                ),
            )

        connection.commit()

    except sqlite3.Error as e:
        print(f"An error occurred: {e}")
        connection.rollback()

    finally:
        cursor.close()

    return drink_id


def delete_drink(connection: sqlite3.Connection, drink_id: int) -> None:
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
