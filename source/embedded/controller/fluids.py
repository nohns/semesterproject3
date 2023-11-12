from database.database import Database
from domain.domain import Fluid


def get_fluids(database: Database)->list[Fluid]:
    try:
        fluids=database.get_fluids()
        return fluids
    except Exception as e:
        print(f"error {e}, when trying to get fluids via controller")
        raise Exception("fix the issue",e)
       
    
def create_fluid(database: Database, name: str)->None:
    try:
        fluid_id=database.create_fluid(name)
        return fluid_id
    except Exception as e:
        print(f"error {e}, when trying to create fluid via controller")
        raise Exception("fix the issue",e)
    
def delete_fluid(database: Database, id: int)->None:
    try:
        database.delete_fluid(id)
        return None
    except Exception as e:
        print(f"error {e}, when trying to delete fluid via controller")
        raise Exception("fix the issue",e)