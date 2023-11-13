def create_drink(connection: sqlite3.Connection, drink: Drink)-> None:    
    cursor = connection.cursor()
    try:
        print("Trying to do the thing")

        #Create array to hold the result
        ingredient_array = []
        print("Printing drink object: ", drink)

        #append the ingredients to the array
        for ingredient in drink.ingredients:
            ingredient_array.append(ingredient["fluid"]["id"])

        print("Printing ingredient array: ", ingredient_array)
        #convert the array to a string seperated by commas
        result_string = ','.join(map(str, ingredient_array))
        print(result_string)

        
 
        # Associate ingredients with the new drink using their existing IDs, think we have to do this
        for ingredient in drink.ingredients:
            #I need to create a text string seperated by commas which is an array of the ingredients ids
            cursor.execute(
                "INSERT INTO Ingredients (amount_in_cl, fluid_id) VALUES (?, ?)",
                (ingredient["amountInCl"], ingredient["fluid"]["id"])
            )
        print("Added ingredients")
        
           # Insert into Drinks table using the existing image_id since we can't directly insert the image object
        print(drink.name)
        print(drink.image["id"])
        cursor.execute(
            "INSERT INTO Drinks (name, ingredients_ids, image_id) VALUES (?, ?, ?)",
            (drink.name, result_string, drink.image["id"])
        
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


    
def delete_drink(connection: sqlite3.Connection, drink_id: int)->None:
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


def create_fluid(connection: sqlite3.Connection, name: str)->None:
    cursor = connection.cursor()

    try:
        cursor.execute(
            "INSERT INTO Fluids (name) VALUES (?)",
            (name,)
        )
                
        connection.commit()
        
    except sqlite3.Error as e:
        print(f"SQLite error: {e}")
        connection.rollback()
        raise Exception("An error occurred while creating the fluid.", e)    

    finally:
        cursor.close()

    
def delete_fluid(connection: sqlite3.Connection, fluid_id: int)->None:
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

