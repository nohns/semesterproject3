from database.database import Database
from domain.domain import Fluid


def get_fluids(database: Database)->list[Fluid]:
    try:
        fluids=database.get_fluids()
        return fluids
    except Exception as e:
        print(f"error {e}, when trying to get fluids via controller")
        return None
       
    
def create_fluid(database: Database, name: str)->None:
    try:
        fluid_id=database.create_fluid(name)
        return fluid_id
    except Exception as e:
        print(f"error {e}, when trying to create fluid via controller")
        return None
    
def delete_fluid(database: Database, id: int)->None:
        return delete_fluid(database, id)