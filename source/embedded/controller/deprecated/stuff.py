def create_drink(database: Database, drink: Drink)->None:
    try:
        database.create_drink(drink)
        
    except Exception as e:
        print(f"error {e}, when trying to create drink via controller")

        raise Exception("Something went to shit fix this error mesg if you find it", e)
        
    
def delete_drink(id: int, database: Database)->None:
    try:
        database.delete_drink(id)
        return 1
    except Exception as e:
        print(f"error {e}, when trying to delete drink via controller")
        raise Exception("fix the issue",e)
    
def create_fluid(database: Database, name: str)->None:
    try:
        database.create_fluid(name)
        
    except Exception as e:
        print(f"error {e}, when trying to create fluid via controller")
        raise Exception("Unable to create fluid", e)
    
def delete_fluid(database: Database, id: int)->None:
    try:
        database.delete_fluid(id)
        return None
    except Exception as e:
        print(f"error {e}, when trying to delete fluid via controller")
        raise Exception("fix the issue",e)
