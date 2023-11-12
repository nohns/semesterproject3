from database.database import Database
from domain.domain import Drink

def create_drink(database: Database, drink: Drink)->None:
    try:
        drink_id=database.create_drink(drink)
        return drink_id
    except Exception as e:
        print(f"error {e}, when trying to create drink via controller")

        raise Exception("Something went to shit fix this error mesg if you find it", e)
        
    
def delete_drink(id: int, database: Database)->None:
    try:
        database.delete_drink(id)
        return 1
    except Exception as e:
        print(f"error {e}, when trying to delete drink via controller")
        return None
    
def get_drinks(database: Database)-> list[Drink]:
    try:
        drinks=database.get_drinks()
        return drinks
    except Exception as e:
      print(f"error {e}, when requesting drinks from database to controller")
      return None
    
def pour_drink(database: Database):
    try:
        database.pour_drink()
        return None
    except Exception as e:
      print(f"error {e}, when trying to pour drink via controller")
      return None

    