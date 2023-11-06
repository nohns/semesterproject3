from database.database import Database
from domain.domain import Fluid


def create_fluid(database: Database, name: str) -> int:
    fluid = Fluid(name=name, id=None)
    return database.create_fluid(fluid)


def delete_fluid(database: Database, id: int) -> None:
    database.delete_fluid(id)


def get_fluids(database: Database) -> list[Fluid]:
    return database.get_fluids()
