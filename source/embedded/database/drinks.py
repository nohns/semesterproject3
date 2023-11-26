import sqlite3
from domain.domain import Drink, Ingredient, Fluid, Image, json_to_dataclass


def get_drinks(connection: sqlite3.Connection) -> list[Drink]:
    cursor = connection.cursor()

    try:
        # Fetch drinks along with their images
        cursor.execute("SELECT * FROM Drinks")

        drinks = cursor.fetchall()

        resulting_drinks_array = []

        # Drinks is a list of lists with each list containing a drink
        for drink in drinks:
            drink_id = drink[0]
            drink_name = drink[1]
            drink_ingredients = drink[2]
            drink_image_id = drink[3]

            # Get the list of ingredient ids
            ingredient_ids = list(map(int, drink_ingredients.split(",")))

            ingredients = []

            for ingredient_id in ingredient_ids:
                cursor.execute("SELECT * FROM Ingredients WHERE id=?", (ingredient_id,))
                ingredient = cursor.fetchone()

                if ingredient:
                    fluid_id = ingredient[1]
                    cursor.execute("SELECT * FROM Fluids WHERE id=?", (fluid_id,))
                    fluid = cursor.fetchone()

                    if fluid:
                        fluid = Fluid(id=fluid[0], name=fluid[1])
                        ingredient = Ingredient(
                            id=ingredient_id, fluid=fluid, amountInCl=ingredient[2]
                        )
                        ingredients.append(ingredient)
                    else:
                        print(f"Fluid with ID: {fluid_id} not found")
                        return
                else:
                    print(f"Ingredient with ID: {ingredient_id} not found")
                    return

            cursor.execute("SELECT * FROM Images WHERE id=?", (drink_image_id,))
            image = cursor.fetchone()
            if image:
                image = Image(id=image[0], path=image[1])
            else:
                print(f"Image with ID: {drink_image_id} not found")
                return

            drink = Drink(
                name=drink_name, image=image, ingredients=ingredients, id=drink_id
            )

            resulting_drinks_array.append(drink)

        return resulting_drinks_array

    except sqlite3.Error as e:
        print(f"SQLite error: {e}")
        return None

    finally:
        cursor.close()


# def pour_drink(connection: sqlite3.Connection) -> None:
#     return 0


def create_drink(connection: sqlite3.Connection, drink: Drink) -> None:
    cursor = connection.cursor()
    try:
        print(f"Database: Attempting to create drink: {drink}")

        all_drinks = get_drinks(connection)
        print(all_drinks)

        if any(drink.name == existing_drink.name for existing_drink in all_drinks):
            print(f"Database: '{drink.name}' already exists")
            return

        # Convert ingredients to dataclass instance
        ingredients = [
            json_to_dataclass(ingredient, Ingredient)
            for ingredient in drink.ingredients
        ]

        # Convert fluid in each ingredient to dataclass instance
        for ingredient in ingredients:
            ingredient.fluid = json_to_dataclass(ingredient.fluid, Fluid)

        ingredient_ids = []
        for ingredient in ingredients:
            # Check if the ingredient already exists
            cursor.execute(
                "SELECT id FROM Ingredients WHERE fluid_id = ? AND amount_in_cl = ?",
                (ingredient.fluid.id, ingredient.amountInCl)
            )
            existing_ingredient = cursor.fetchone()

            if existing_ingredient:
                # If it exists, use the existing id
                ingredient_id = existing_ingredient[0]
            else:
                # If not, insert the new ingredient and use its new id
                cursor.execute(
                    "INSERT INTO Ingredients (fluid_id, amount_in_cl) VALUES (?, ?)",
                    (ingredient.fluid.id, ingredient.amountInCl)
                )
                ingredient_id = cursor.lastrowid  # This gets the new id

            ingredient_ids.append(ingredient_id)

        # Insert into Drinks table using the existing image_id since we can't directly insert the image object
        drink.image = json_to_dataclass(drink.image, Image)
        cursor.execute("INSERT INTO Images (path) VALUES (?)", (drink.image.path,))
        image_id = cursor.lastrowid  # This gets the new id for the image
        print("Database: Image has been added")

        # Convert the list of ingredient IDs to a string separated by commas
        ingredient_ids_str = ",".join(map(str, ingredient_ids))
        cursor.execute(
            "INSERT INTO Drinks (name, ingredients_ids, image_id) VALUES (?, ?, ?)",
            (drink.name, ingredient_ids_str, image_id),
        )
        print("Database: Drink has been added")

        connection.commit()
        print("Committed")

    except sqlite3.Error as e:
        print(f"An error occurred: {e}")
        connection.rollback()
        raise Exception("An error occurred while creating the drink.", e) from e

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
