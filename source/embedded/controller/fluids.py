from database.database import Database
from domain.domain import Fluid


def get_fluids(database: Database)->list[Fluid]:
    try:
        fluids=database.get_fluids()
        return fluids
    except Exception as e:
        print(f"error {e}, when trying to get fluids via controller")
        raise Exception("fix the issue",e)
       
